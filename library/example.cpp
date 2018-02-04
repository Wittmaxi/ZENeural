#include "Zeneural.h"
#include <iostream>
#include "debugMachine.h"

int main () {
	d.write = true;
	d.info ("STARTING NEURAL NETWORK");
	ML::NeuralNetwork nn (false);
	nn.addLayer(2);
	nn.addLayer(1);
	d.info ("FORWARDING SUMS HOPEFULLY");
	std::vector<double> testVec {1.0f, 1.0f};
	std::vector<double> testVec2 {1.0f, 0.0f};
	std::vector<double> testVec3 {0.0f, 1.0f};
	std::vector<double> testVec4 {0.0f, 0.0f};
	std::vector<double> resVec {1.0f};
	std::vector<double> resVec2 {0.0f};
	d.out (std::to_string(nn.guess (testVec)[0]));
	for (int i = 0; i < 10000; i++) {
		nn.train (testVec, resVec);
		nn.train (testVec2, resVec2);
		nn.train (testVec3, resVec2);
		nn.train (testVec4, resVec2);
	}
	std::cout << std::to_string(nn.guess (testVec)[0]);
	std::cout << "FINISHED" << std::endl;
}
