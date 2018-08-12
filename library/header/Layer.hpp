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
		: weights(inputSize, 0.1f)
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
		: size(_size), inputSize(_inputSize), neurons(_size, Neuron<floatType>(_inputSize))
	{
		normalization = Fermi<floatType>();
	}

	std::vector<floatType> calculate(std::vector<floatType> inputs)
	{
		layerInputValues = inputs;
		layerInputValues.push_back(1);
		layerOutputValues = weightedSum(inputs);
		return layerOutputValues;
	}

	std::vector<floatType> weightedSum(std::vector<floatType> inputs)
	{
		std::vector<floatType> temporaryResults;

		for (size_t i = 0; i < neurons.size(); i++)
			temporaryResults.push_back(normalization.normalization(neurons.at(i).weightedSum(inputs)));

		return temporaryResults;
	}

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
	using Layer<floatType>::Layer;

	std::vector<floatType> calculateDerivatives();
	void changeWeights(std::vector<floatType> derivatives){};
	void train(std::vector<floatType> lastLayersDerivatives){};
};

template <class floatType>
class OutputLayer : public Layer<floatType>
{
  public:
	std::vector<floatType> errors;
	std::vector<floatType> targets;

	using Layer<floatType>::Layer;

	std::vector<floatType> calculateDerivatives()
	{
		std::vector<floatType> temporaryDerivatives;
		for (auto i : errors)
		{
			std::cout << i << " err\n";
		}
		for (auto i : this->layerInputValues)
		{
			std::cout << "layerinput val " << i;
		}
		std::cout << "\n";
		std::cout << this->normalization.derivative(this->layerInputValues[0]) << "lol" << this->layerInputValues[0] << "\n";
		for (size_t i = 0; i < this->size; i++)
			temporaryDerivatives.push_back(errors[i] * -1 * this->normalization.derivative(this->layerOutputValues[i]));

		return temporaryDerivatives;
	}

	void changeWeights(std::vector<floatType> newDerivatives)
	{
		for (size_t i = 0; i < this->size; i++)
			for (size_t j = 0; j < this->inputSize; j++)
			{
				this->neurons[i].weights[j] -= this->learningRate * this->layerInputValues[j] * newDerivatives[i];
				std::cout << "in der " << newDerivatives[i] << " lr " << this->learningRate << " inval " << this->layerInputValues[i] << "\n";
			}
	}

	std::vector<floatType>
	calculateErrors(std::vector<floatType> newTargets)
	{
		std::vector<floatType> errorsTemp;
		for (size_t i = 0; i < newTargets.size(); i++)
			errorsTemp.push_back(newTargets[i] - this->layerOutputValues.at(i));

		errors = errorsTemp;
		return errorsTemp;
	}

	void train(std::vector<floatType> newTargets)
	{
		calculateErrors(newTargets);
		std::vector<floatType> generatedDerivatives = calculateDerivatives();
		changeWeights(generatedDerivatives);
		for (auto i : generatedDerivatives)
		{
			std::cout << i << " DERIV\n";
		}
		for (auto i : newTargets)
		{
			std::cout << i << " TARG\n";
		}
		for (auto i : errors)
		{
			std::cout << i << " ERR\n";
		}
		for (auto i : this->neurons)
		{
			for (auto j : i.weights)
			{
				std::cout << j << " weight ";
			}
			std::cout << "\n";
		}
		std::cout << "\n";
	}
}; // namespace ZNN

} // namespace ZNN