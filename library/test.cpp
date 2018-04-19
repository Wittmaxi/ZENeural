#include "debugMachine.h"
#include "Perceptron.hpp"
#include <cstdlib>
#include <random>

int main() {
	__tester t;
	std::mt19937 rng;
	rng.seed (std::random_device ()());
	std::uniform_int_distribution<std::mt19937::result_type> dist4 (0, 3);
	std::vector<std::vector<double>> examples {
		{0,0},  {0,1}, {1,1}, {1,0}
	};
	std::vector<double> out {
		-1, -1, 1, -1
	};
	ZNN::Perceptron a(2, false);
	std::srand (123123);
	int i = dist4(rng);
	std::cout << a.guess (examples[i]) << "\n";
	for (int j = 0; j < 100; j++) {
		i = dist4 (rng);
		a.train (examples[i], out[i]);
	}
	std::cout << examples[i][0] << " " << examples[i][1] << "\n";
	std::cout << a.guess (examples[i]) << "\n";
	t.report();
}