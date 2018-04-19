#include "Perceptron.hpp"

namespace ZNN {
	Perceptron::Perceptron (size_t number_inputs, bool a) {
		for (int i = 0; i < number_inputs; i++) {
			weights.push_back (0.1f);
		}
		weights.push_back (0.1f);
		out.write = a;
		out.out ("Set up Perceptron");
	}
	double Perceptron::guess (std::vector<double> input) {
		value = 0;
		input.push_back (1.0f);
		for (size_t i = 0; i < weights.size(); i++) {
			value += (input[i] * weights[i]);
		}
		return value;
	}
	double Perceptron::train (std::vector<double> input, double exp) {
		double outp = guess (input);
		double err = outp - exp;
		for (int i = 0; i < weights.size(); i++) {
			weights [i] -= 0.3 * err;
		}
		return err;
	}
}