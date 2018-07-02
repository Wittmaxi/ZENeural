#include "header/Perceptron.hpp"
#include "header/normalisation.h"
#include "header/exceptions.h"

namespace ZNN
{
Perceptron::Perceptron(size_t number_inputs, bool a)
{
	for (int i = 0; i < number_inputs; i++)
	{
		weights.push_back(0.1f);
	}
	learnRate = 0.3;
	norm = Fermi();
	weights.push_back(0.1f);
}

double Perceptron::realGuess(std::vector<double> input)
{
	if (input.size() != weights.size() - 1)
	{
		throw NUMBERINPUTMISMATCH();
	}
	double value = 0;
	input.push_back(1.0f);
	for (size_t i = 0; i < weights.size(); i++)
	{
		value += (input[i] * weights[i]);
	}
	return value;
}

double Perceptron::guess(std::vector<double> input)
{
	return norm.normalization(realGuess(input));
}

double Perceptron::train(std::vector<double> input, double exp)
{
	double outp = guess(input);
	double err = outp - exp;
	for (int i = 0; i < weights.size(); i++)
	{
		weights[i] -= (learnRate * err);
	}
	return err;
}

void Perceptron::setNormalization(Normalization _norm)
{
	norm = _norm;
}

void Perceptron::setLearnRate(double lr)
{
	if (lr == 0)
	{
		throw LEARNRATEZERO();
	}
	learnRate = lr;
}
} // namespace ZNN