#include "header/NeuralNetwork.hpp"
#include "header/normalization.h"
#include <iostream>

int main()
{
	ZNN::NeuralNetwork<double> b;
	std::vector<std::vector<double>> input{{1, 0}, {0, 1}, {0, 0}, {1, 1}};
	std::vector<std::vector<double>> target{{1}, {1}, {0}, {1}};
	b.setInputLayerSize(2);
	b.setOutputLayerSize(1);

	b.setNormalization(ZNN::Identity<double>());
	for (int i = 0; i < 1600; i++)
	{
		std::cout << "iteration " << i << "\n";
		b.train(input[i % 4], target[i % 4]);
	}

	std::cout << b.guess(input[0])[0] << "\n";
	std::cout << b.guess(input[1])[0] << "\n";
	std::cout << b.guess(input[2])[0] << "\n";
	std::cout << b.guess(input[3])[0] << "\n";
}
