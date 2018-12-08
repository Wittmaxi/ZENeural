/*
2018 Maximilian Wittmer
wittmaxi@linux.pizza

https://github.com/Wittmaxi/ZENeural/blob/master/LICENSE

*/

#pragma once
#include "includes.h"
#include "util/assert.hpp"
#include "normalization.hpp"
#include "Neuron.hpp"
#include "util/ThreadScheduler.hpp"

namespace ZNN
{

template <class floatType>
class Layer
{
  public:
	Layer() {}
	Layer(unsigned int _size, unsigned int _inputSize);

	const std::vector<floatType> &calculate(const std::vector<floatType> &inputs);
	std::vector<floatType> weightedSum(const std::vector<floatType> &inputs);

	std::string getAsString() const;
	void loadFromString(std::string string);

	void changeWeights();

	unsigned int size;
	unsigned int inputSize;
	unsigned int threadHint = 2;
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

	void train(const std::vector<floatType> &lastLayersDerivatives, const std::vector<Neuron<floatType>> &nextLayersNeurons);
	void calculateDerivatives(const std::vector<floatType> &nextLayersDerivatives, const std::vector<Neuron<floatType>> &nextLayersNeurons);
};

template <class floatType>
class OutputLayer : public Layer<floatType>
{
  public:
	std::vector<floatType> errors;
	OutputLayer(){};
	OutputLayer(unsigned int _size, unsigned int _inputSize);

	void train(const std::vector<floatType> &newTargets);
	void calculateDerivatives();
	void calculateErrors(std::vector<floatType> newTargets);
};

//

template <class floatType>
Layer<floatType>::Layer(unsigned int _size, unsigned int _inputSize)
	: size(_size), inputSize(_inputSize), normalization(Identity<floatType>()), neurons(_size, Neuron<floatType>(_inputSize))
{
}

template <class floatType>
std::string Layer<floatType>::getAsString() const
{
	std::string temp;
	for (const auto &i : neurons)
		temp += i.getAsString() + "]";
	return temp;
}

template <class floatType>
void Layer<floatType>::loadFromString(std::string string)
{
	std::string temp;
	neurons.resize(0);
	for (const auto i : string)
		if (i == ']')
		{
			ZNN::Neuron<floatType> n;
			n.loadFromString(temp);
			neurons.push_back(n);
			temp = "";
		}
		else
			temp += i;
	size = neurons.size();
	inputSize = neurons[0].weights.size();
}

template <class floatType>
const std::vector<floatType> &Layer<floatType>::calculate(const std::vector<floatType> &inputs)
{
	layerInputValues = inputs;
	layerInputValues.push_back(1.0);
	layerOutputValues = weightedSum(layerInputValues);
	return layerOutputValues;
}

template <class floatType>
std::vector<floatType> Layer<floatType>::weightedSum(const std::vector<floatType> &inputs)
{
	std::vector<floatType> temporaryResults{};
	temporaryResults.resize(neurons.size());
	UTIL::ThreadScheduler ts{threadHint};

	auto calculateNth = [&](unsigned int startingPoint, unsigned int series) noexcept
	{
		for (unsigned int i = startingPoint; i < neurons.size(); i += series)
			temporaryResults[i] = (normalization.normalization(neurons[i].weightedSum(inputs)));
	};
	
	for (unsigned int i = 0; i < threadHint; i++)
		ts.runFunction(calculateNth, i, threadHint);
	ts.waitUntilAllStopped();
	if (temporaryResults.size() != neurons.size())
		std::cout << "PROBLEM\n";
	return temporaryResults;
}

template <class floatType>
void Layer<floatType>::changeWeights()
{
	for (size_t i = 0; i < this->size; i++)
		for (size_t j = 0; j < this->inputSize; j++)
			this->neurons[i].weights[j] -= this->learningRate * this->layerInputValues[j] * this->derivatives[i];
}

//

template <class floatType>
OutputLayer<floatType>::OutputLayer(unsigned int _size, unsigned int _inputSize)
{
	this->size = _size;
	this->inputSize = _inputSize;
	this->neurons = std::vector<Neuron<floatType>>(_size, Neuron<floatType>(_inputSize));
	this->normalization = Identity<floatType>();
}

template <class floatType>
void OutputLayer<floatType>::train(const std::vector<floatType> &newTargets)
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
		errorsTemp.push_back(newTargets[i] - this->layerOutputValues[i]);

	errors = errorsTemp;
}

//

template <class floatType>
HiddenLayer<floatType>::HiddenLayer(unsigned int _size, unsigned int _inputSize)
{
	this->size = _size;
	this->inputSize = _inputSize;
	this->neurons = std::vector<Neuron<floatType>>(_size, Neuron<floatType>(_inputSize));
	this->normalization = Identity<floatType>();
}

template <class floatType>
void HiddenLayer<floatType>::calculateDerivatives(const std::vector<floatType> &nextLayersDerivatives, const std::vector<Neuron<floatType>> &nextLayersNeurons)
{
	std::vector<floatType> temporaryDerivatives;
	for (unsigned int i = 0; i < this->size; i++)
	{
		floatType accumulator = 0;
		for (size_t j = 0; j < nextLayersDerivatives.size(); j++)
			accumulator += nextLayersDerivatives[j] * nextLayersNeurons[j].weights[i];
		temporaryDerivatives.push_back(this->normalization.derivative(this->layerOutputValues[i]) * accumulator);
	}
	this->derivatives = temporaryDerivatives;
}

template <class floatType>
void HiddenLayer<floatType>::train(const std::vector<floatType> &lastLayersDerivatives, const std::vector<Neuron<floatType>> &nextLayersNeurons)
{
	calculateDerivatives(lastLayersDerivatives, nextLayersNeurons);
	this->changeWeights();
}

} // namespace ZNN