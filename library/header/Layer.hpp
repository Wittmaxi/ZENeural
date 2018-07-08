#pragma once
#include <vector>
#include <functional>
#include <memory>
#include "debugMachine.h"

namespace ZNN
{
struct Neuron
{
	std::vector<double> weights;
	Neuron(size_t llsize, double initVal) : weights(llsize, initVal) {}
};

class Layer
{
  public:
	std::vector<double> inputs;
	std::vector<double> outputs;
	std::function<double(double)> normalisation;
	std::vector<Neuron> neurons;
	double learnRate = 0.25;
	size_t isize;
	size_t size;

	Layer(size_t layerSize, size_t llsize, double initWeightVal, std::function<double(double)> norm);
	~Layer();
	void calculate(std::vector<double> &llout);
	void train(std::vector<double> derivatives);
};
} // namespace ZNN