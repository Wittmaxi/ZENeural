#pragma once
#include <vector>
#include "debugMachine.h"
#include <functional>

namespace ZNN {
	class Perceptron {
		__debugMachine out;
		std::vector <double> weights;
		double value;
	public:
		Perceptron (size_t number_inputs, bool debug = false); 
		double guess (std::vector <double> input);
		double train (std::vector <double> input, double exp);
		void setNormalisation (std::function<double (double)> norm);
	};
}