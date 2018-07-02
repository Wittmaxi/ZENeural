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
		layers.push_back(Layer(size, norm.normalization, 0, stdWeightVal));
	}
	else
	{
		layers.push_back(Layer(size, norm.normalization, layers.back().size + 1, stdWeightVal));
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
		layers[i].train(calculate_derivatives(i));
	}
}

void NeuralNetwork::setLearnRate(double lr)
{
	for (size_t i = 0; i < layers.size(); i++)
	{
		layers[i].learnRate = lr;
	}
}

void NeuralNetwork::setNormalization(Normalization nnorm)
{
	norm = nnorm;
	for (size_t i = 0; i < layers.size(); i++)
	{
		layers[i].normalisation = nnorm.normalization;
	}
}

const std::vector<Layer> NeuralNetwork::getRawLayers()
{
	return layers;
}

std::vector<double> NeuralNetwork::calculate_ll_derivatives(int index)
{
	std::vector<double> derivatives;
	for (size_t i = 0; i < layers[index].size; i++)
	{
		// δE/wjk=(ok−sk)⋅φ'(netk) * oj
		derivatives.push_back((layers.at(index).outputs.at(i) - target.at(i)) * norm.derivative(layers.at(index).outputs[i])); //calculate *that* derivative
	}
	llder = derivatives;
	return llder;
}

std::vector<double> NeuralNetwork::calculate_derivatives(int index)
{
	if (index == layers.size() - 1)
	{
		calculate_ll_derivatives(index);
		return llder;
	} //outter layers get a different derivative
	std::vector<double> derivatives;
	for (size_t i = 0; i < layers[index].size + 1; i++)
	{
		double sum = 0;
		for (int j = 0; j < layers[index + 1].size; j++)
		{
			sum += llder[j] * layers[index + 1].neurons[j].weights[i];
		}
		derivatives.push_back(norm.derivative(layers[index].outputs[i]) * sum);
	}
	llder = derivatives;
	return derivatives;
}
} // namespace ZNN