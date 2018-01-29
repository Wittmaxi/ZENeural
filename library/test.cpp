#include <vector>

#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "CNeuron.h"
#include "CLayer.h"

using namespace ML;

TEST_CASE ("NEURON", ".") {
	CNeuron testNeuron(3);
	std::vector<double> testVec {1.0f, 3.4f, 0.5f};
	SECTION ("CONSTR") {
		REQUIRE (testNeuron.m_weights.size() == 3);
	}
	SECTION ("FORWARD SUM") {
		REQUIRE (testNeuron.forwardSum (testVec) > 0);
	}
}

TEST_CASE ("LAYER", ".") {
	CLayer testLayer (10, 3);
	REQUIRE (testLayer.m_neurons.size() == 10);
	SECTION ("ALL NEURONS HAVE ENOUGH WEIGHTS") {
		for (size_t i = 0; i < testLayer.m_neurons.size(); ++i) {
			REQUIRE (testLayer.m_neurons[i].m_weights.size() == 3);
		}
	}
}

TEST_CASE ("NN", ".") {

}