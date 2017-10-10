#ifndef NODE_H
#define NODE_H


//define needed constants too long to paste in code
#define CONST_PI 3.14159265358979323846264338327950288419716939937510582097494459230781640628620899862803482534211706798214808651328230664709384460955058223172535940812848111745028410270193852110555964462294895493038196442881097566593344612847564823378678316527120190914564856692346034861045432664821339360726024914127324587006606315588174881520920962829254091715364367892590360011330530548820466521384146951941511609
#define CONST_E 2.718281828459

#include <vector>
#include <string>
#include <iostream>
#include <stdexcept>
#include <cmath>


#define act_sigmoid 1
#define act_threshact 2
#define act_gauss 3
#define act_ramp 7
#define act_binarystep 8
#define act_identity 9

class Node { //each perceptron
public: 
	Node (std::vector <Node*> _lastLayer) {
		currentSum = 0;
		this->lastLayer = _lastLayer;
		if (_lastLayer.size() == 0) {
			this-> weights.push_back (1.0); //initialize weights as something
			return;
		}

		for (int i = 0; i < lastLayer.size(); i++) {
			this-> weights.push_back (1.0); //initialize weights as something
		}
	}

	void sumUpLastLayer () {
		std::cout << this->weights.size() << "  " << this->lastLayer.size() << std::endl;
		for (int i = 0; i < lastLayer.size(); i++) {
			double weight = 0;
			if (i < weights.size()) {
				weight = weights [i];
			}
			std::cout << "last layer" << lastLayer[i]->getSum() << std::endl;
			currentSum += lastLayer[i]->getSum() * weight;
			std::cout << "Sum: " << currentSum << std::endl;
		}
	}

		//gods of coding, im  EXTREMELY sorry for this function. Please forgive me. 
	double activation (const int function_id, const bool writeToOwnVal = true) { //calculates an activation function to its own sum
		if (function_id > 9 || function_id < 1) {throw std::invalid_argument ("Activation-function not known!");} //if the activation function doesnt exist
		
		int output = 0;
		
		if (function_id == act_identity) {output = currentSum;} //the identity function
		
		if (function_id == act_threshact) { //the threshold-activation function
			if (currentSum < 0) {
				output = -1;
			} else {
				output = 1;
			}
		}
		
		if (function_id == act_ramp) { //the ramp function
			output = 0;
			if (currentSum > 0) {
				output = currentSum;
			}
		}
		
		if (function_id == act_binarystep) { //everything below 0 is 0, else its a normal identity
			output = 0;
			if (currentSum > 0) {
				output = 1;
			}				
		}
		
		if (function_id == act_gauss) {
			output = 1/sqrt(2*CONST_PI) * pow(CONST_E, - 1 / 2 * pow (currentSum, 2));
		}
		
		if (function_id == act_sigmoid) {
			output = 1 / 1 + pow (CONST_E, - currentSum); 
		}
		

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

    double adjustWeights (double result, double expected) {
    	for (int i = 0; i < weights.size(); i++) {
    		weights [i] += ( expected - result ) * 0.25;
    	}
    }

	private: 
		float currentSum;
		std::vector <Node*> lastLayer;
		std::vector <double> weights;
};

#endif