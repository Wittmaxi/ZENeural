#pragma once
#include <vector>
#include <functional>
#include "Layer.hpp"
#include "debugMachine.h"

namespace ZNN {
	class NeuralNetwork {
		std::vector<Layer> layers;
		std::vector<double> target;
		std::vector<double> llder; //derivative of the last layer
		std::vector<double> calculate_ll_derivatives(int index); //last layer
		std::vector<double> calculate_derivatives(int index); //calculate the derivatives
	public:
		__debugMachine d;
		NeuralNetwork();
		~NeuralNetwork();
		void addLayer (size_t number, double stdWeightVal = 0.1f);
		std::vector<double> guess (std::vector<double>& inputs);
		double train (std::vector<double>& input, std::vector<double>& expected);
		void setLearnRate (double learnRate);
		void setNormalisation (std::function<double(double)> func);
		const std::vector<Layer> getRawLayers();
	};
}