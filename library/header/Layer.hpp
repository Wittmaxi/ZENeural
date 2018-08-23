/*
2018 Maximilian Wittmer
wittmaxi@linux.pizza

https://github.com/Wittmaxi/ZENeural/blob/master/LICENSE

*/

#pragma once
#include <vector>
#include <functional>
#include <memory>
#include "util/assert.h"
#include "normalization.h"
#include <iostream>

namespace ZNN
{
template <class floatType>
class Neuron
{
  public:
	using vectorType = std::vector<floatType>;
	using vectorReferenceType = const vectorType &;

	Neuron() {}
	Neuron(unsigned int inputSize);
	floatType weightedSum(vectorType inputs);

	vectorType weights;
};

template <class floatType>
class Layer
{
  public:
	Layer() {}
	Layer(unsigned int _size, unsigned int _inputSize);

	const std::vector<floatType> &calculate(std::vector<floatType> inputs);
	std::vector<floatType> weightedSum(std::vector<floatType> inputs);

	void changeWeights();

	unsigned int size;
	unsigned int inputSize;
	floatType learningRate = 0.2;
	Normalization<floatType> normalization;

	std::vector<Neuron<floatType>> neurons;
	std::vector<floatType> derivatives;
	std::vector<floatType> layerInputValues;
	std::vector<floatType> layerOutputValues;
};

template <class floatType> //TODO
class HiddenLayer : public Layer<floatType>
{
  public:
	HiddenLayer(){};
	HiddenLayer(unsigned int _size, unsigned int _inputSize);

	void train(std::vector<floatType> lastLayersDerivatives, std::vector<Neuron<floatType>> nextLayersNeurons);
	void calculateDerivatives(std::vector<floatType> nextLayersDerivatives, std::vector<Neuron<floatType>> nextLayersNeurons);
};

template <class floatType>
class OutputLayer : public Layer<floatType>
{
  public:
	std::vector<floatType> errors;
	std::vector<floatType> targets;

	OutputLayer(){};
	OutputLayer(unsigned int _size, unsigned int _inputSize);

	void train(std::vector<floatType> newTargets);
	void calculateDerivatives();
	void calculateErrors(std::vector<floatType> newTargets);
};

template <class floatType>
Neuron<floatType>::Neuron(unsigned int inputSize)
	: weights(inputSize, 0.1f)
{
}

template <class floatType>
floatType Neuron<floatType>::weightedSum(std::vector<floatType> inputs)
{
	floatType temporaryResult = 0.0;
	for (size_t j = 0; j < weights.size(); j++)
		temporaryResult += inputs[j] * weights[j];
	return temporaryResult;
}

template <class floatType>
Layer<floatType>::Layer(unsigned int _size, unsigned int _inputSize)
	: size(_size), inputSize(_inputSize), neurons(_size, Neuron<floatType>(_inputSize))
{
	normalization = Identity<floatType>();
}

template <class floatType>
const std::vector<floatType> &Layer<floatType>::calculate(std::vector<floatType> inputs)
{
	layerInputValues = inputs;
	layerInputValues.push_back(1.0);
	layerOutputValues = weightedSum(layerInputValues);
	return layerOutputValues;
}

template <class floatType>
std::vector<floatType> Layer<floatType>::weightedSum(std::vector<floatType> inputs)
{
	std::vector<floatType> temporaryResults;

	for (size_t i = 0; i < neurons.size(); i++)
		temporaryResults.push_back(normalization.normalization(neurons[i].weightedSum(inputs)));

	return std::move(temporaryResults);
}

template <class floatType>
void Layer<floatType>::changeWeights()
{
	for (size_t i = 0; i < this->size; i++)
		for (size_t j = 0; j < this->inputSize; j++)
			this->neurons[i].weights[j] -= this->learningRate * this->layerInputValues[j] * this->derivatives[i];
}

template <class floatType>
OutputLayer<floatType>::OutputLayer(unsigned int _size, unsigned int _inputSize)
{
	this->size = _size;
	this->inputSize = _inputSize;
	this->neurons = std::vector<Neuron<floatType>>(_size, Neuron<floatType>(_inputSize));
	this->normalization = Identity<floatType>();
}

template <class floatType>
void OutputLayer<floatType>::train(std::vector<floatType> newTargets)
{
	calculateErrors(newTargets);
	calculateDerivatives();
	this->changeWeights();
}

template <class floatType>
void OutputLayer<floatType>::calculateDerivatives()
{
	std::vector<floatType> temporaryDerivatives;
	for (size_t i = 0; i < this->size; i++)
		temporaryDerivatives.push_back(errors[i] * -1 * this->normalization.derivative(this->layerOutputValues[i]));

	this->derivatives = temporaryDerivatives;
}

template <class floatType>
void OutputLayer<floatType>::calculateErrors(std::vector<floatType> newTargets)
{
	std::vector<floatType> errorsTemp;
	for (size_t i = 0; i < newTargets.size(); i++)
		errorsTemp.push_back(newTargets[i] - this->layerOutputValues.at(i));

	errors = errorsTemp;
}

template <class floatType>
HiddenLayer<floatType>::HiddenLayer(unsigned int _size, unsigned int _inputSize)
{
	this->size = _size;
	this->inputSize = _inputSize;
	this->neurons = std::vector<Neuron<floatType>>(_size, Neuron<floatType>(_inputSize));
	this->normalization = Identity<floatType>();
}

template <class floatType>
void HiddenLayer<floatType>::calculateDerivatives(std::vector<floatType> nextLayersDerivatives, std::vector<Neuron<floatType>> nextLayersNeurons)
{
	std::vector<floatType> temporaryDerivatives;
	for (unsigned int i = 0; i < this->size; i++)
	{
		floatType accumulator;
		for (size_t j = 0; j < nextLayersDerivatives.size(); j++)
			accumulator += this->normalization.derivative(this->layerOutputValues[i]) * nextLayersDerivatives[j] * nextLayersNeurons[j].weights[i];
		temporaryDerivatives.push_back(accumulator);
	}
	this->derivatives = temporaryDerivatives;
}

template <class floatType>
void HiddenLayer<floatType>::train(std::vector<floatType> lastLayersDerivatives, std::vector<Neuron<floatType>> nextLayersNeurons)
{
	calculateDerivatives(lastLayersDerivatives, nextLayersNeurons);
	this->changeWeights();
}

} // namespace ZNN