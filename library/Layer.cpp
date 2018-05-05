#include "header/Layer.hpp"
#include "header/exceptions.h"
#include "header/normalisation.h"

namespace ZNN
{
Layer::Layer(size_t layerSize, size_t llsize, double initVal)
	: neurons(layerSize, Neuron(llsize, initVal))
{
	isize = llsize;
	size = layerSize;
	normalisation = fermi;
}

Layer::~Layer()
{
}

void Layer::calculate(std::vector<double> &llout)
{
	inputs = llout;
	outputs.clear();
	for (size_t i = 0; i < size; i++)
	{
		double val = 0;
		for (int j = 0; j < isize; j++)
		{
			val += llout[j] * neurons[i].weights[j];
		}
		outputs.push_back(normalisation(val));
	}
}

void Layer::train(std::vector<double> derivatives)
{
	for (size_t i = 0; i < neurons.size(); i++)
	{
		for (int j = 0; j < isize; j++)
		{
			neurons[i].improve_weights(j, derivatives[i] * inputs[j]);
		}
	}
}
}