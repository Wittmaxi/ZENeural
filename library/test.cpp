#include "header/debugMachine.h"
#include "header/Perceptron.hpp"
#include "header/NeuralNetwork.hpp"
#include "header/normalisation.h"

int main()
{
	ZNN::NeuralNetwork b(true);
	std::vector<double> a{1};
	std::vector<double> target{0.6, 0.31415};
	b.addLayer(1);
	b.addLayer(20);
	b.addLayer(20);
	b.addLayer(2);
	std::cout << b.guess(a)[0] << " " << b.guess(a)[1] << "\n";
	for (int i = 0; i < 1000; i++)
	{
		b.train(a, target);
	}
	std::cout << std::fixed << b.guess(a)[0] << " " << b.guess(a)[1] << "\n";
}