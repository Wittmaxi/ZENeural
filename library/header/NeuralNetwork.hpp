/*
2018 Maximilian Wittmer
wittmaxi@linux.pizza

https://github.com/Wittmaxi/ZENeural/blob/master/LICENSE

*/

#pragma once

#include "includes.h"
#include "Layer.hpp"
#include "normalization.hpp"
#include "util/assert.hpp"

namespace ZNN
{
template <class floatType = double>
class FeedForwardNeuralNetwork
{
  public:
	void setInputLayerSize(unsigned int size);
	void setOutputLayerSize(unsigned int size);
	void addHiddenLayer(unsigned int layerSize);

	std::vector<floatType> guess(const std::vector<floatType>& input);
	floatType train(std::vector<floatType>& input, std::vector<floatType>& target);

	void setLearningRate(floatType learningRate);
	void setNormalization(const Normalization<floatType> &normalizationObject);

	std::string saveToString();
	void loadFromString(std::string objectString); //TODO

  protected:
	unsigned int trainingIterations = 0;
	unsigned int inputLayerSize = 0;
	unsigned int outputLayerSize = 0;
	std::vector<HiddenLayer<floatType>> layers;
	OutputLayer<floatType> outputLayer;

	void trainLayers(std::vector<floatType>& target);

	unsigned int getLastLayersSize();
	unsigned int getLastLayersSizeWithBias();

	floatType calculateTotalError();
	void constructOutputLayer();
	void checkCompleteSetup();
};

template <class floatType>
void FeedForwardNeuralNetwork<floatType>::setInputLayerSize(unsigned int size)
{
	UTIL::assert(inputLayerSize != 0, "You cannot set the size of the Input layer twice");
	UTIL::assert(size == 0, "You cannot set an input layer's size to a value smaler than 1");

	inputLayerSize = size;
}

template <class floatType>
void FeedForwardNeuralNetwork<floatType>::setOutputLayerSize(unsigned int size)
{
	UTIL::assert(outputLayerSize != 0, "You cannot set the size of the Output layer twice");
	UTIL::assert(size == 0, "You cannot set an output layer's size to a value smaller than 1");
	UTIL::assert(inputLayerSize == 0, "You have to create atleast an input layer before creating an Output layer");

	outputLayerSize = size;
	constructOutputLayer();
}

template <class floatType>
void FeedForwardNeuralNetwork<floatType>::addHiddenLayer(unsigned int size)
{
	UTIL::assert(inputLayerSize == 0, "You have to create atleast an input layer before creating an Output layer");
	UTIL::assert(size == 0, "You cannot set an hidden layer's size to a value smaller than 1");
	UTIL::assert(outputLayerSize != 0, "You cannot create hidden Layers behind of the Output Layer");

	layers.push_back(HiddenLayer<floatType>(size, getLastLayersSizeWithBias()));
}

template <class floatType>
std::vector<floatType> FeedForwardNeuralNetwork<floatType>::guess(const std::vector<floatType>& input)
{
	UTIL::assert(input.size() != inputLayerSize, "Wrong number of elements in the Input vector!");
	checkCompleteSetup();

	std::vector<floatType> results = input;
	for (auto &i : layers)
		results = i.calculate(results);
	return outputLayer.calculate(results);
}

template <class floatType>
floatType FeedForwardNeuralNetwork<floatType>::train(std::vector<floatType>& input, std::vector<floatType>& target)
{
	guess(input);
	trainLayers(target);
	return calculateTotalError();
}

template <class floatType>
void FeedForwardNeuralNetwork<floatType>::setLearningRate(floatType learningRate)
{
	for (auto &i : layers)
		i.learningRate = learningRate;
	outputLayer.learningRate = learningRate;
}

template <class floatType>
void FeedForwardNeuralNetwork<floatType>::setNormalization(const Normalization<floatType> &normalizationObject)
{
	for (auto &i : layers)
		i.normalization = normalizationObject;
	outputLayer.normalization = normalizationObject;
}

template <class floatType>
unsigned int FeedForwardNeuralNetwork<floatType>::getLastLayersSizeWithBias()
{
	return getLastLayersSize() + 1;
}

template <class floatType>
unsigned int FeedForwardNeuralNetwork<floatType>::getLastLayersSize()
{
	unsigned int lastLayersSize = inputLayerSize;
	if (layers.size() > 0)
		lastLayersSize = layers.back().size;
	return lastLayersSize;
}

template <class floatType>
floatType FeedForwardNeuralNetwork<floatType>::calculateTotalError()
{
	floatType temporaryError = 0;
	for (auto i : outputLayer.errors)
		temporaryError += i * i;
	return temporaryError / 2;
}

template <class floatType>
void FeedForwardNeuralNetwork<floatType>::constructOutputLayer()
{
	outputLayer = OutputLayer<floatType>(outputLayerSize, getLastLayersSizeWithBias());
}

template <class floatType>
void FeedForwardNeuralNetwork<floatType>::checkCompleteSetup()
{
	UTIL::assert(outputLayerSize == 0, "You have not created an output Layer!");
	UTIL::assert(inputLayerSize == 0, "You have not created an input Layer!");
}

template <class floatType>
void FeedForwardNeuralNetwork<floatType>::trainLayers(std::vector<floatType>& target)
{
	outputLayer.train(target);
	std::vector<floatType> lastLayersDerivative = outputLayer.derivatives;
	std::vector<Neuron<floatType>> lastLayersNeurons = outputLayer.neurons;
	for (auto &i : layers)
	{
		i.train(lastLayersDerivative, lastLayersNeurons);
		lastLayersDerivative = i.derivatives;
		lastLayersNeurons = i.neurons;
	}
}
} // namespace ZNN