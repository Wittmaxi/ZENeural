#include "header/debugMachine.h"
#include "header/Perceptron.hpp"
#include "header/NeuralNetwork.hpp"
#include "header/normalisation.h"

int main()
{
	ZNN::NeuralNetwork b;
	std::vector<std::vector<double>> input{{1, 0}, {0, 1}, {0, 0}, {1, 1}};
	std::vector<std::vector<double>> target{{0}, {0}, {1}, {0}};
	b.addLayer(2);
	b.addLayer(5);
	b.addLayer(1);
	b.setLearnRate(0.5);
	b.setNormalization(ZNN::Fermi());
	std::cout << b.guess(input[0])[0] << "\n\n\n";
	for (int i = 0; i < 1000; i++)
	{
		b.train(input[0], target[0]);
		b.train(input[1], target[1]);
		b.train(input[2], target[2]);
		b.train(input[3], target[3]);
	}
	std::cout << std::fixed << b.guess(input[0])[0] << "\n";
	std::cout << std::fixed << b.guess(input[1])[0] << "\n";
	std::cout << std::fixed << b.guess(input[2])[0] << "\n";
	std::cout << std::fixed << b.guess(input[3])[0] << "\n";
	/*double aa, bb;
	std::cin >> aa;
	std::cin >> bb;
	std::vector<double> ninput{double(aa), double(bb)};
	std::cout << std::fixed << b.guess(ninput)[0] << "\n";
	*/
}
