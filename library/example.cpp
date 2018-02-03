#include "Zeneural.h"
#include <iostream>
#include "debugMachine.h"

int main () {
	d.write = true;
	d.info ("STARTING NEURAL NETWORK");
	ML::NeuralNetwork nn (true);
	nn.addLayer(1);
	nn.addLayer(11);
	nn.addLayer(111);
//	nn.addLayer(11111);
	nn.addLayer(1);
	d.info ("FORWARDING SUMS HOPEFULLY");
	std::vector<double> testVec {1.0};
	std::vector<double> resVec {0.2};
	d.out (std::to_string(nn.guess (testVec)[0]));
	d.info ("QUIT NN");
}
