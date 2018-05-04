#pragma once
#include <vector>
#include <functional>
#include <memory>
#include "debugMachine.h"

namespace ZNN {
	struct Neuron {
		std::vector<double> weights;
		Neuron (size_t llsize, double initVal) {
			for (size_t i = 0; i < llsize; i++) {
				weights.push_back (initVal);
			}
		}
	};

	class Layer{
		__debugMachine d;
	public:
		std::vector<double> inputs;
		std::vector<double> outputs;
		std::function<double(double)> normalisation;
		std::vector<Neuron> neurons;
		double learnRate;
		size_t isize;
		size_t size;

		Layer (size_t layerSize, size_t llsize, double initVal = 0.0f);
		~Layer ();
		std::vector<double> calculate (std::vector<double>& llout);
		void train (double derivative);
	};
}