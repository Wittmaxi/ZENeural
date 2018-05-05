#pragma once
#include <vector>
#include <functional>
#include <memory>
#include "debugMachine.h"

namespace ZNN
{
class Neuron
{
	__debugMachine d{true};

  public:
	std::vector<double> weights;
	Neuron(size_t llsize, double initVal)
	{
		for (size_t i = 0; i < llsize; i++)
		{
			weights.push_back(initVal);
		}
	}
	void improve_weights(size_t w, double derivative)
	{
		weights[w] += -0.25 * derivative;
	}
};

class Layer
{
  public:
	std::vector<double> inputs;
	std::vector<double> outputs;
	std::function<double(double)> normalisation;
	std::vector<Neuron> neurons;
	double learnRate;
	size_t isize;
	size_t size;

	Layer(size_t layerSize, size_t llsize, double initVal = 0.0f);
	~Layer();
	void calculate(std::vector<double> &llout);
	void train(std::vector<double> derivatives);
};
}