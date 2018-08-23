/*
2018 Maximilian Wittmer
wittmaxi@linux.pizza

https://github.com/Wittmaxi/ZENeural/blob/master/LICENSE

*/

#pragma once
#include <vector>
#include <string>
#include <math.h>
#include "Layer.hpp"
#include "normalization.h"
#include "util/assert.h"
#include <iostream>

namespace ZNN
{
template <class floatType = double>
class NeuralNetwork
{
  public:
	using vectorType = std::vector<floatType>;
	using vectorReferenceType = const vectorType &;

	void setInputLayerSize(unsigned int size);
	void setOutputLayerSize(unsigned int size);
	void addHiddenLayer(unsigned int layerSize);

	vectorType guess(vectorReferenceType input);
	floatType train(vectorReferenceType input, vectorReferenceType target);

	void setLearningRate(floatType learningRate);
	void setNormalization(Normalization<floatType> normalizationObject);

	std::string saveToString();					   //TODO
	void loadFromString(std::string objectString); //TODO

  protected:
	unsigned int trainingIterations = 0;
	unsigned int inputLayerSize = 0;
	unsigned int outputLayerSize = 0;
	std::vector<HiddenLayer<floatType>> layers;
	OutputLayer<floatType> outputLayer;

	void trainLayers(vectorReferenceType target);

	unsigned int getLastLayersSize();
	unsigned int getLastLayersSizeWithBias();

	floatType calculateTotalError();
	void constructOutputLayer();
	void checkCompleteSetup();
};

template <class floatType>
void NeuralNetwork<floatType>::setInputLayerSize(unsigned int size)
{
	assert(inputLayerSize != 0, "You cannot set the size of the Input layer twice");
	assert(size == 0, "You cannot set an input layer's size to a value smaler than 1");

	inputLayerSize = size;
}

template <class floatType>
void NeuralNetwork<floatType>::setOutputLayerSize(unsigned int size)
{
	assert(outputLayerSize != 0, "You cannot set the size of the Output layer twice");
	assert(size == 0, "You cannot set an output layer's size to a value smaller than 1");
	assert(inputLayerSize == 0, "You have to create atleast an input layer before creating an Output layer");

	outputLayerSize = size;
	constructOutputLayer();
}

template <class floatType>
void NeuralNetwork<floatType>::addHiddenLayer(unsigned int size)
{
	assert(inputLayerSize == 0, "You have to create atleast an input layer before creating an Output layer");
	assert(size == 0, "You cannot set an hidden layer's size to a value smaller than 1");
	assert(outputLayerSize != 0, "You cannot create hidden Layers behind of the Output Layer");

	layers.push_back(HiddenLayer<floatType>(size, getLastLayersSizeWithBias()));
}

template <class floatType>
typename NeuralNetwork<floatType>::vectorType NeuralNetwork<floatType>::guess(vectorReferenceType input)
{
	assert(input.size() != inputLayerSize, "Wrong number of elements in the Input vector!");
	checkCompleteSetup();

	vectorType results = input;
	for (auto &i : layers)
		results = i.calculate(results);
	return std::move(outputLayer.calculate(results));
}

template <class floatType>
floatType NeuralNetwork<floatType>::train(vectorReferenceType input, vectorReferenceType target)
{
	guess(input);
	trainLayers(target);
	return calculateTotalError();
}

template <class floatType>
void NeuralNetwork<floatType>::setLearningRate(floatType learningRate)
{
	for (auto &i : layers)
		i.learningRate = learningRate;
	outputLayer.learningRate = learningRate;
}

template <class floatType>
void NeuralNetwork<floatType>::setNormalization(Normalization<floatType> normalizationObject)
{
	for (auto &i : layers)
		i.normalization = normalizationObject;
	outputLayer.normalization = normalizationObject;
}

template <class floatType>
unsigned int NeuralNetwork<floatType>::getLastLayersSizeWithBias()
{
	return getLastLayersSize() + 1;
}

template <class floatType>
unsigned int NeuralNetwork<floatType>::getLastLayersSize()
{
	unsigned int lastLayersSize = inputLayerSize;
	if (layers.size() > 0)
		lastLayersSize = layers.back().size;
	return lastLayersSize;
}

template <class floatType>
floatType NeuralNetwork<floatType>::calculateTotalError()
{
	floatType temporaryError = 0;
	for (auto i : outputLayer.errors)
		temporaryError += i * i;
	return temporaryError / 2;
}

template <class floatType>
void NeuralNetwork<floatType>::constructOutputLayer()
{
	outputLayer = OutputLayer<floatType>(outputLayerSize, getLastLayersSizeWithBias());
}

template <class floatType>
void NeuralNetwork<floatType>::checkCompleteSetup()
{
	assert(outputLayerSize == 0, "You have not created an output Layer!");
	assert(inputLayerSize == 0, "You have not created an input Layer!");
}

template <class floatType>
void NeuralNetwork<floatType>::trainLayers(vectorReferenceType target)
{
	outputLayer.train(target);
	vectorType lastLayersDerivative = outputLayer.derivatives;
	std::vector<Neuron<floatType>> lastLayersNeurons = outputLayer.neurons;
	for (auto &i : layers)
	{
		i.train(lastLayersDerivative, lastLayersNeurons);
		lastLayersDerivative = i.derivatives;
		lastLayersNeurons = i.neurons;
	}
}
} // namespace ZNN