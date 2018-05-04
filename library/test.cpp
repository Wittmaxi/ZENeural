#include "header/debugMachine.h"
#include "header/Perceptron.hpp"
#include "header/NeuralNetwork.hpp"
#include "header/normalisation.h"

int main() {
	__tester t;
	ZNN::NeuralNetwork b{};
	std::vector <double> a {0};
	b.addLayer (1);
	b.addLayer (20);
	b.addLayer (2);
	t.REQUIRE (b.getRawLayers().size() == 3, "RIGHT NUMBER OF LAYERS");
	t.REQUIRE (b.getRawLayers()[0].size == 1, "L1 RIGHT SIZE");
	t.REQUIRE (b.getRawLayers()[1].size == 20, "L2 RIGHT SIZE");
	t.REQUIRE (b.getRawLayers()[2].size == 2, "L3 RIGHT SIZE");
	t.REQUIRE (b.getRawLayers()[0].isize == 0, "L1 RIGHT ISIZE");
	t.REQUIRE (b.getRawLayers()[1].isize == 1, "L2 RIGHT ISIZE");
	t.REQUIRE (b.getRawLayers()[2].isize == 20, "L3 RIGHT ISIZE");
	std::cout << b.guess (a)[0] << "\n";
	t.report();
}