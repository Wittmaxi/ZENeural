#ifndef NODE_H
#define NODE_H


//define needed constants too long to paste in code
#define CONST_PI 3.141592653589
#define CONST_E 2.718281828459

#include <vector>
#include <string>
#include <iostream>
#include <stdexcept>
#include <cmath>

#include "activation.h"

#define act_sigmoid 1
#define act_threshact 2
#define act_gauss 3
#define act_ramp 7
#define act_binarystep 8
#define act_identity 9

namespace ML {
class Node { //each perceptron
public: 
	Node (std::vector <Node*> _lastLayer) {
		currentSum = 0;
		learningRate = 0.25;
		this->lastLayer = _lastLayer;
		if (_lastLayer.size() == 0) {
			this-> weights.push_back (0.0); //initialize weights as something
			return;
		}

		for (int i = 0; i < lastLayer.size(); i++) {
			this-> weights.push_back (0.0); //initialize weights as something
		}
	}

	void sumUpLastLayer () {
		for (int i = 0; i < lastLayer.size(); i++) {
			double weight = 0;
			if (i < weights.size()) {
				weight = weights [i];
			}
			currentSum += lastLayer[i]->getSum() * weight;
		}
	}

	void setLearningRate (double lr) {
		learningRate = lr;
	}

		//gods of coding, im  EXTREMELY sorry for this function. Please forgive me. 
	double nodeActivation (const int function_id, const bool writeToOwnVal = true) { //calculates an activation function to its own sum
		double output = activation (currentSum, function_id);

		if (writeToOwnVal) { //if needed, write to its own value
			currentSum = output;
		}
		return output;
	}

	void setSum (double val) {
		currentSum = val;
	}

	double getSum () {
		return currentSum;
	}

    void adjustWeights (double error) {
    	for (int i = 0; i < weights.size(); i++) {
    		weights [i] += error * learningRate;
    		std::cout << weights [i] << std::endl;
    	}
    }

	private: 
		double learningRate;
		double currentSum;
		std::vector <Node*> lastLayer;
		std::vector <double> weights;
};
}
#endif