#pragma once
#include <vector>
#include "debugMachine.h"
#include <functional>

namespace ZNN {
	class Perceptron {
		__debugMachine out;
		std::vector <double> weights;
		std::function <double(double)> normalisation;
		double learnRate;
	public:
		Perceptron (size_t number_inputs, bool debug = false); //constructot
		double guess (std::vector <double> input); //make a weighted sum of the inputs, then normalize it
		double realGuess (std::vector <double> input); //make a weighted sum of the inputs
		double train (std::vector <double> input, double exp); //adjust the weights, returns the total error
		void setNormalisation (std::function<double (double)> norm); //set a normalisation function.
		void setLearnRate (double lr); //set learning rate
	};
}