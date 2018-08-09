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
	Neuron(unsigned int inputSize)
		: weights(inputSize, 0.0f)
	{
	}

	double weightedSum(std::vector<floatType> inputs)
	{
		double temporaryResult;
		for (size_t j = 0; j < weights.size(); j++)
		{
			temporaryResult += inputs[j] * weights[j];
		}
		return temporaryResult;
	}

	std::vector<floatType> weights;
};

template <class floatType>
class Layer
{
  public:
	Layer(){};

	Layer(unsigned int _size, unsigned int _inputSize)
		: neurons(_size, Neuron<floatType>(_inputSize)), size(_size), inputSize(_inputSize)
	{
		normalization = Fermi<floatType>();
	}

	std::vector<floatType> calculate(std::vector<floatType> inputs)
	{
		assert(neurons.size() == 0, "is zero in calc");
		layerInputValues = inputs;
		layerOutputValues = weightedSum(inputs);
		return layerOutputValues;
	}

	std::vector<floatType> weightedSum(std::vector<floatType> inputs)
	{
		assert(neurons.size() == 0, "is zero in ws");
		std::vector<floatType> temporaryResults;

		for (size_t i = 0; i < neurons.size(); i++)
			temporaryResults.push_back(normalization.normalization(neurons.at(i).weightedSum(inputs)));

		return temporaryResults;
	}

	unsigned int size;
	unsigned int inputSize;
	floatType learningRate = 0.1;
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
	std::vector<floatType> calculateDerivatives();
	void changeWeights(std::vector<floatType> derivatives){};
	void train(std::vector<floatType> lastLayersDerivatives){};
};

template <class floatType>
class OutputLayer : public virtual Layer<floatType>
{
  public:
	OutputLayer(unsigned int _size, unsigned int _inputSize)
	{
		this->neurons = std::vector<Neuron<floatType>>(_size, Neuron<floatType>(_inputSize));
		this->size = _size;
		this->inputSize = _inputSize;
		this->normalization = Fermi<floatType>();
		std::cout << "HI\n";
		std::cout << "size: " << this->neurons.size() << "\n";
	}

	std::vector<floatType> errors;
	std::vector<floatType> targets;

	OutputLayer(){};

	std::vector<floatType> calculateDerivatives()
	{
		assert(this->neurons.size() == 0, "is zero in calcder");
		std::vector<floatType> temporaryDerivatives;
		for (size_t i = 0; i < this->size; i++)
			temporaryDerivatives.push_back(errors[i] * -1 * this->normalization.derivative(this->layerInputValues[i]));

		return temporaryDerivatives;
	}

	void changeWeights(std::vector<floatType> derivatives)
	{
		assert(this->neurons.size() == 0, "is zero in changeweights");
		for (size_t i = 0; i < this->size; i++)
			for (size_t j = 0; j < this->inputSize; j++)
				this->neurons[i].weights[j] -= this->learningRate * this->layerInputValues[j] * derivatives[i];
	}

	std::vector<floatType>
	calculateErrors(std::vector<floatType> targets)
	{
		assert(this->neurons.size() == 0, "is zero in calcerr");
		std::cout << this->layerOutputValues.size() << "out size\n";
		std::cout << this->neurons.size() << "neur size\n";
		std::vector<floatType> errorsTemp;
		for (size_t i = 0; i < targets.size(); i++)
			errorsTemp.push_back(targets[i] - this->layerOutputValues.at(i));

		errors = errorsTemp;
		return errorsTemp;
	}

	void train(std::vector<floatType> targets)
	{
		assert(this->neurons.size() == 0, "is zero in train");
		calculateErrors(targets);
		std::vector<floatType> generatedDerivatives = calculateDerivatives();
		changeWeights(generatedDerivatives);
	}
}; // namespace ZNN

} // namespace ZNN