#include <iostream>
#include <vector>
#include <stdlib.h>
#include <time.h>

#include "../../library/integral.h"

std::vector < std::vector < double > > input {{1.0, 0.0}, {0.0, 0.0}, {1.0, 1.0}, {1.0, 1.0}};
std::vector < double > output;
std::vector < std::vector < double > > expected {{0},{0}, {1}, {0}};

int main () {
	ML::Neural andNN(false);
	std::cout << "created NN" << std::endl;
	andNN.addLayer(2); //input
	andNN.addLayer (1);
	andNN.addLayer (1); //output
	andNN.setLearningRate (0.1);
	
	std::cout << "created layers" << std::endl;

	for (int i = 0; i < 10000; i ++) {
		srand(time(NULL) * 2);
		int rndIndex = rand () % 4 +1;
		andNN.train (input[rndIndex], expected[rndIndex]);
		std::cout << "training now" << std::endl;
	}

	std::vector < double > newInput {0.0,0.0};

	for (int i = 0; i < 5; i++) {
		std::cin >> newInput[0];
		std::cin >> newInput[1];
		output = andNN.guess(newInput);
		for (auto i : output) {
			std::cout << i << std::endl;
		}
	}
}