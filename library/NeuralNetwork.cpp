#include "header/NeuralNetwork.hpp"
#include "header/exceptions.h"
#include <iterator>

namespace ZNN {
	__debugMachine d{true};
	NeuralNetwork::NeuralNetwork () {

	}

	NeuralNetwork::~NeuralNetwork () {

	}

	void NeuralNetwork::addLayer (size_t size, double stdWeightVal) {
		if (size == 0) {
			throw LAYERSIZEZERO();
		}
		if (layers.size() == 0) { //inputLayer 
			layers.push_back (Layer (size, 0, stdWeightVal));
		} else {
			layers.push_back (Layer (size, layers.back().size, stdWeightVal));
		}
	}

	std::vector<double> NeuralNetwork::guess (std::vector<double>& inputs) {
		layers.front().outputs = inputs;
		for (size_t i = 1; i < layers.size(); i++) {
			layers[i].calculate (layers[i-1].outputs);
		}
		return layers.back().outputs;
	}

	double NeuralNetwork::train (std::vector<double>& input, std::vector<double>& expected) {
		
	}

	void NeuralNetwork::setLearnRate (double lr) {
		for (int i = 0; i < layers.size(); i++) {
			layers[i].learnRate = lr;
		}
	}

	void NeuralNetwork::setNormalisation (std::function<double(double)> func) {
		for (int i = 0; i < layers.size(); i++) {
			layers[i].normalisation = func;
		}
	}

	const std::vector<Layer> NeuralNetwork::getRawLayers() {
		return layers;
	}

	std::vector<double> NeuralNetwork::calculate_ll_derivatives (int index) {
		std::vector<double> derivatives;
		for (size_t i = 0; i < layers[index].size; i++) {
			// δE/wjk=(ok−sk)⋅φ'(netk) * oj
			derivatives.push_back ((layers[index].outputs[i] - target [i]) * (1 - layers[index].outputs[i] ) * layers[index].outputs[i]); //calculate *that* derivative
		}	
		llder = derivatives;
		return llder;
	}

	std::vector<double> NeuralNetwork::calculate_derivatives (int index) {
		if (index == layers.size()) {
			calculate_ll_derivatives (index);
			return llder;
		} //outter layers get a different derivative
		std::vector<double> derivatives;
		for (size_t i = 0; i < layers[index].size; i++) {
			float sum = 0;
			for (int j = 0; j < layers[index+1].size; j++) {
				sum += llder[j] * layers[index+1].neurons[j].weights[i]; 
			}
			derivatives.push_back ( ( 1 - layers[index].outputs[i]) * sum);
		}
		return derivatives;
	}

}