#include <iostream>
#include <vector>
#include <stdlib.h>
#include <time.h>

#include "Neural.h"


int main () {
	std::vector < std::vector < double > > input {{1.0, 0.0}, {0.0, 0.0}, {1.0, 1.0}, {1.0, 1.0}};
	std::vector < double > output;
	std::vector < std::vector < double > > expected {{0},{0}, {1}, {0}};

	ML::CNeural andNN{}; //using {} instead of () in order to bypass the most vexing parse problem
	std::cout << "created NN" << std::endl;
	andNN.addLayer(2); //input
	std::cout << "first layer" << std::endl;
	andNN.addLayer (1);
	andNN.addLayer (1); //output
	
	std::cout << "created layers" << std::endl;

	for (int i = 0; i < 1; i ++) {
		srand(time(NULL) * 2);
		int rndIndex = rand () % 4 +1;
		std::cout << "training" << std::endl;
		std::vector<double>*  in =new std::vector<double>(input[rndIndex]);
		std::vector<double>*  ex=new std::vector<double>(expected[rndIndex]);
		andNN.adjust (*in, *ex);
		delete in;
		delete ex;
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