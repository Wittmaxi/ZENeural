#ifndef NN_H
#define NN_H

#include <vector>
#include <string>
#include <iostream>
#include <stdexcept>
#include <cmath>

#include "node.h"

//creating states as in a state maching

#define state_learn 1
#define state_calc_only 2

//define needed constants too long to paste in code
#define CONST_PI 3.141592653589
#define CONST_E 2.718281828459

#define act_sigmoid 1
#define act_threshact 2
#define act_gauss 3
#define act_ramp 4
#define act_binarystep 5
#define act_identity 6

namespace ML {
	class Neural {
	public:
		Neural (bool debug = false) { //initialize everything
			debugMode = debug;
			d ("NN INITIALIZED");
		}

		void createInputLayer (unsigned int numberNodes = 1, unsigned int activation = act_identity) {
			if (inputLayer.size() != 0) {throw std::invalid_argument("THERE IS ALREADY AN INPUT LAYER");} //if an input layer was already created
			if (hiddenLayers.size() != 0) {throw std::invalid_argument("YOU HAVE TO FIRST CREATE THE INPUT LAYER; THEN THE HIDDEN ONES!");}

			for (int i = 0; i < numberNodes; i++) {
				inputLayer.push_back (new Node(*new std::vector<Node*>())); //since theres no last layer
			}
			inputLayer.push_back(new Node(*new std::vector<Node*>()));
			inputLayer[inputLayer.size()-1]->setSum(1);
			activations.push_back(activation);
			d ("Input layer created!");
		}

		void addHiddenLayer (unsigned int numberNodes = 1, unsigned int activation = act_identity) {
			std::vector < Node* > temp;
			std::vector < Node* > lastLayer;

			if (outputLayer.size() != 0 || inputLayer.size() == 0) {throw std::invalid_argument("LAYERING PROBLEM!");}

			if (hiddenLayers.size() == 0) {
				lastLayer = inputLayer;
			} else {
				lastLayer = this->hiddenLayers.at (this->hiddenLayers.size() - 1);
			}

			activations.push_back(activation);

			for (int i = 0; i < numberNodes; i++) {
				temp.push_back (new Node(lastLayer));
			}
			temp.push_back (new Node (lastLayer));
			temp[temp.size()-1]->setSum (1.0);

			hiddenLayers.push_back(temp);

			d("Added a new hidden layer!");
		}

		void createOutputLayer (unsigned int numberNodes = 1, unsigned int activation = act_identity) {
			if (outputLayer.size() != 0) {throw std::invalid_argument("THERE IS ALREADY AN OUTPUT LAYER");} //if an input layer was already created

			if (hiddenLayers.size() == 0) {throw std::invalid_argument("You havent created any hidden layers!");}

			std::vector < Node* > lastLayer = hiddenLayers [hiddenLayers.size() -1];

			for (int i = 0; i < numberNodes; i++) {
				outputLayer.push_back (new Node(lastLayer)); //since theres no last layer
			}
			activations.push_back (activation);
			d ("Output layer created!");
		}

		void getNotif () { //if the user wants to get notified by the engine. Might be unused
			d ("PINGPONG");
		}

		void setState (int _state = state_learn) {
			state = _state;
		}

		std::vector <double> guess (std::vector<double> input) {
			d ("Neural Network is currently calculating a guess!");

			if (!input.size() == inputLayer.size()) {throw std::invalid_argument("MISMATCH IN NUMBER OF INPUT DATA");}
			int index = 0;
			for (int i = 0; i < inputLayer.size(); i++) {
				inputLayer[i]->setSum (input [i]);
				inputLayer[i]->nodeActivation(activations[index]);
			}
			index++;

			std::vector <double> output;

			for (auto layer : hiddenLayers) {
				for (auto item : layer) {
					item->sumUpLastLayer();
					item->nodeActivation(activations[index]);
				}
				index++;
			}

			for (auto item : outputLayer) {
				item->sumUpLastLayer();
				item->nodeActivation(activations[index]);
				output.push_back(item->getSum());
			}
			d("calculated the output!");
			return output;
		}

		void train (std::vector <double> input, std::vector<double> expected) { //adjusts the weights
			if (expected.size() != outputLayer.size()) {throw std::invalid_argument("WRONG NUMBER OF EXCPECTED VALUES!");}
		
			std::vector < double > output = guess(input);

			d("guessed something");

			for (int i = 0; i < output.size(); i++) {
				outputLayer[i]->setError(expected[i] - output[i]);
			}
			d("assigned errors");

			d("all went well!");
			for (auto i : outputLayer) {
				i->adjustWeights();
			}
			for (int i = hiddenLayers.size() -1; i > 0; i--) {
				for (auto j: hiddenLayers [i]) {
					j->adjustWeights();
				}
			}
			for (auto i : inputLayer) {
				i->adjustWeights();
			}
		}

		void setLearningRate (double lr) {

			for (auto i : inputLayer) {
				i->setLearningRate (lr);
			}
			
			int totalRate = lr;


			for (auto i : hiddenLayers) {
				totalRate *= lr / 2;
				for (auto j : i) {
					j->setLearningRate (totalRate);
				}
			}

			for (auto i : outputLayer) {
				i->setLearningRate (totalRate);
			}

		}

	private:

		void d (std::string log) { //output Log-messages. Only works in debug-mode
			if (debugMode) {
				std::cout << log << std::endl;
			}
		} 

		bool debugMode;
		int state; //keeps the state of the Net
		std::vector < Node* > inputLayer;
		std::vector < std::vector < Node* > > hiddenLayers;
		std::vector < Node* > outputLayer;
		std::vector < int > activations;
	};
}

#endif
