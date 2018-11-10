/*
2018 Maximilian Wittmer
wittmaxi@linux.pizza

https://github.com/Wittmaxi/ZENeural/blob/master/LICENSE

*/

#pragma once
#include "NeuralNetwork.hpp"

namespace ZNN {
template<class floatType>
class VanillaRecurrentNeuralNetwork : public FeedForwardNeuralNetwork<floatType> {
public: 
    void addHiddenLayer (unsigned int layerSize);
    void clearStates ();
	std::vector<floatType> guess(const std::vector<floatType>& input);
protected:
    std::vector<floatType> appendStatesToInputs (std::vector<floatType> inputs, Layer<floatType>& layer);
};

template<class floatType>
void VanillaRecurrentNeuralNetwork<floatType>::addHiddenLayer(unsigned layerSize) {
    UTIL::assert(this->inputLayerSize == 0, "You have to create atleast an input layer before creating an Output layer");
	UTIL::assert(layerSize == 0, "You cannot set an hidden layer's size to a value smaller than 1");
	UTIL::assert(this->outputLayerSize != 0, "You cannot create hidden Layers behind of the Output Layer");

	this->layers.push_back(HiddenLayer<floatType>(layerSize, this->getLastLayersSizeWithBias() + layerSize));
}

template<class floatType>
void VanillaRecurrentNeuralNetwork<floatType>::clearStates () {
    for (auto &layer : this->layers)
        for (auto &outputValue : layer.layerOutputValues)
            outputValue = 0;
}

template<class floatType>
std::vector<floatType> VanillaRecurrentNeuralNetwork<floatType>::guess (const std::vector<floatType>& input) {
	UTIL::assert(input.size() != this->inputLayerSize, "Wrong number of elements in the Input vector!");
	this->checkCompleteSetup();

    std::vector<floatType> results = input;
	for (auto &i : this->layers) {
		results = i.calculate(appendStatesToInputs (results, i));
    }
	return this->outputLayer.calculate(results);
}

template<class floatType>
std::vector<floatType> VanillaRecurrentNeuralNetwork<floatType>::appendStatesToInputs (std::vector<floatType> inputs, Layer<floatType>& layer) {
    inputs.insert(inputs.end(), layer.layerOutputValues.begin(), layer.layerOutputValues.end());
    return inputs;
}
}