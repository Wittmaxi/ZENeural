#include "header/Layer.hpp"
#include "header/exceptions.h"

namespace ZNN {
	Layer::Layer (size_t layerSize, size_t llsize, double initVal) 
	: neurons (layerSize, Neuron (llsize, initVal)) {
		isize = llsize;
		size = layerSize;
	}
	
	Layer::~Layer () {

	}
	
	std::vector<double> Layer::calculate (std::vector<double>& llout) {
		std::vector<double> out;
		for (size_t i = 0; i < size; i++) {
			double val;
			for (int j = 0; j < isize; j++) {
				val += llout[j] * neurons[i].weights[j];
			}
			out.push_back (val);
		}
		return out;
	}

	void Layer::train (double derivative) {

	}
}