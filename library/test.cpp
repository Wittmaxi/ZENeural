#include "header/NeuralNetwork.hpp"
#include "header/normalization.h"
#include <iostream>

ZNN::NeuralNetwork<double> b;
std::vector<std::vector<double>> input{{1, 0}, {0, 1}, {0, 0}, {1, 1}};
std::vector<std::vector<double>> target{{0}, {0}, {1}, {1}};

void showAll();

int main()
{

	b.setInputLayerSize(2);
	b.setOutputLayerSize(1);

	showAll();

	for (int i = 0; i < 1600; i++)
	{
		b.train(input[0], target[0]);
		b.train(input[1], target[1]);
		b.train(input[2], target[2]);
		b.train(input[3], target[3]);
	}

	showAll();
}

void showAll()
{
	std::cout << b.guess(input[0])[0] << " : GUESS 1\n";
	std::cout << b.guess(input[1])[0] << " : GUESS 2\n";
	std::cout << b.guess(input[2])[0] << " : GUESS 3\n";
	std::cout << b.guess(input[3])[0] << " : GUESS 4\n";
}
