#include "header/NeuralNetwork.hpp"
#include "header/exceptions.h"
#include <iterator>

namespace ZNN
{
NeuralNetwork::NeuralNetwork()
{
	setNormalization(Fermi());
}

NeuralNetwork::~NeuralNetwork()
{
}

void NeuralNetwork::addLayer(size_t size, double stdWeightVal)
{
	if (size == 0)
	{
		throw LAYERSIZEZERO();
	}
	if (layers.size() == 0)
	{ //inputLayer
		layers.push_back(Layer(size, 0, stdWeightVal, norm.normalization));
	}
	else
	{
		layers.push_back(Layer(size, layers.back().size + 1, stdWeightVal, norm.normalization));
	}
}

std::vector<double> NeuralNetwork::guess(std::vector<double> &inputs)
{
	layers.front().outputs = inputs;
	for (size_t i = 1; i < layers.size(); i++)
	{
		layers[i].calculate(layers[i - 1].outputs);
	}
	return layers[layers.size() - 1].outputs;
}

double NeuralNetwork::train(std::vector<double> &input, std::vector<double> &expected)
{
	target = expected;
	guess(input);
	for (size_t i = layers.size() - 1; i > 0; i--)
	{
		auto m = calculateDerivatives(i);
		layers[i].train(m);
	}
}

void NeuralNetwork::setLearnRate(double lr)
{
	if (lr == 0)
	{
		throw LEARNRATEZERO();
	}
	for (size_t i = 0; i < layers.size(); i++)
	{
		layers[i].learnRate = lr;
	}
}

void NeuralNetwork::setNormalization(Normalization new_normalization)
{
	norm = new_normalization;
	for (size_t i = 0; i < layers.size(); i++)
	{
		layers[i].normalisation = new_normalization.normalization;
	}
}

const std::vector<Layer> NeuralNetwork::getRawLayers()
{
	return layers;
}

std::vector<double> NeuralNetwork::calculateLastLayerDerivatives(int index)
{
	std::vector<double> derivatives;
	for (size_t i = 0; i < layers[index].size; i++)
	{
		// δE/wjk=(ok−sk)⋅φ'(netk) * oj
		derivatives.push_back((layers.at(index).outputs.at(i) - target.at(i)) * norm.derivative(layers.at(index).outputs[i])); //calculate *that* derivative
	}
	lastLayerDerivative = derivatives;
	return lastLayerDerivative;
}

std::vector<double> NeuralNetwork::calculateDerivatives(int index)
{
	if (index == layers.size() - 1)
	{
		calculateLastLayerDerivatives(index);
		return lastLayerDerivative;
	} //outter layers get a different derivative
	std::vector<double> derivatives;
	for (size_t i = 0; i < layers[index].size + 1; i++)
	{
		double sum = 0;
		for (int j = 0; j < layers[index + 1].size; j++)
		{
			sum += lastLayerDerivative[j] * layers[index + 1].neurons[j].weights[i];
		}
		derivatives.push_back(norm.derivative(layers[index].outputs[i]) * sum * std::pow(100, layers.size() - (index + 1)));
	}
	lastLayerDerivative = derivatives;
	return derivatives;
}
} // namespace ZNN