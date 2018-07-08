#include "header/Layer.hpp"
#include "header/exceptions.h"
#include "header/normalisation.h"

namespace ZNN
{
Layer::Layer(size_t layerSize, size_t llsize, double initWeightVal, std::function<double(double)> norm)
	: neurons(layerSize, Neuron(llsize, initWeightVal))
{
	isize = llsize;
	size = layerSize;
	normalisation = norm;
}

Layer::~Layer()
{
}

void Layer::calculate(std::vector<double> &llout)
{
	inputs = llout;
	inputs.push_back(1);
	outputs.clear();
	for (size_t i = 0; i < size; i++)
	{
		double val = 0;
		for (int j = 0; j < isize; j++)
		{
			val += inputs[j] * neurons[i].weights[j];
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
			neurons[i].weights[j] += -learnRate * derivatives[i] * inputs[j];
		}
	}
}
} // namespace ZNN