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
	void setInputLayerSize(unsigned int size)
	{
		assert(inputLayerSize != 0, "You cannot set the size of the Input layer twice");
		assert(size == 0, "You cannot set an input layer's size to a smaller value than zero");

		inputLayerSize = size;
		reconstructOutputLayer();
	}
	void setOutputLayerSize(unsigned int size)
	{
		assert(outputLayerSize != 0, "You cannot set the size of the Output layer twice");
		assert(size == 0, "You cannot set an output layer's size to a smaller value than zero");

		outputLayerSize = size;
		reconstructOutputLayer();
	}
	void addHiddenLayer(unsigned int layerSize)
	{
		layers.push_back(HiddenLayer<floatType>(layerSize, getLastLayersSizeWithBias()));
		reconstructOutputLayer();
	}

	std::vector<floatType> guess(std::vector<floatType> input)
	{
		assert(input.size() != inputLayerSize, "Wrong number of elements in the Input vector!");

		std::vector<floatType> results = input;
		for (auto &i : layers)
			results = i.calculate(results);
		return outputLayer.calculate(results);
	}

	floatType train(std::vector<floatType> input, std::vector<floatType> target)
	{
		guess(input);
		outputLayer.train(target);
		std::vector<floatType> lastLayersDerivative = outputLayer.derivatives;
		for (auto &i : layers)
		{
			i.train(lastLayersDerivative);
			lastLayersDerivative = i.derivatives;
		}
		return calculateTotalError();
	}

	void setLearningRate(floatType learningRate)
	{
		for (auto &i : layers)
			i.learningRate = learningRate;
		outputLayer.learningRate = learningRate;
	}

	void setNormalization(Normalization<floatType> normalizationObject)
	{
		for (auto &i : layers)
		{
			i.normalization = normalizationObject;
		}
		outputLayer.normalization = normalizationObject;
	}

	std::string saveToString(); //TODO
	void loadFromString(std::string objectString);

  protected:
	unsigned int trainingIterations = 0;
	unsigned int inputLayerSize = 0;
	unsigned int outputLayerSize = 0;
	std::vector<HiddenLayer<floatType>> layers;
	OutputLayer<floatType> outputLayer;

	unsigned int getLastLayersSize()
	{
		unsigned int lastLayersSize = inputLayerSize;
		if (layers.size() > 0)
			lastLayersSize = layers.back().size;
		return lastLayersSize;
	}

	unsigned int getLastLayersSizeWithBias()
	{
		return getLastLayersSize() + 1;
	}

	double calculateTotalError()
	{
		double temporaryError;
		for (auto i : outputLayer.errors)
			temporaryError += std::pow(i, 2);
		return 1 / 2 * temporaryError;
	}

	void reconstructOutputLayer()
	{
		outputLayer = OutputLayer<floatType>(outputLayerSize, getLastLayersSizeWithBias());
	}
};
} // namespace ZNN