#include <vector>

#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "CNeuron.h"
#include "CLayer.h"
#include "Zeneural.h"
#include "activation.h"

using namespace ML;

TEST_CASE ("NEURON", ".") {
	CNeuron testNeuron(3);
	std::vector<double> testVec {1.0f, 3.4f, 0.5f};
	SECTION ("CONSTR") {
		REQUIRE (testNeuron.m_weights.size() == 3);
	}
	SECTION ("FORWARD SUM") {
		REQUIRE (testNeuron.m_forwardSum (testVec) > 0);
	}
}

TEST_CASE ("LAYER", ".") {
	CLayer testLayer (10, 3);
	testLayer.m_normalisation = ACT_SIGMOID;
	std::vector<double> testVec {1.0f, 3.4f, 0.5f};	
	REQUIRE (testLayer.m_neurons.size() == 10);
	SECTION ("ALL NEURONS HAVE ENOUGH WEIGHTS") {
		REQUIRE (testLayer.m_neurons.size() == 10);
		for (size_t i = 0; i < testLayer.m_neurons.size(); ++i) {
			REQUIRE (testLayer.m_neurons[i].m_weights.size() == 3);
		}
	}
	SECTION ("FORWARDING SOME SUMS") {
		testLayer.m_forward (testVec);
		REQUIRE(testLayer.m_output.size() == 3);
		REQUIRE(testLayer.m_input.size() == 3);
	}
}

TEST_CASE ("NN", ".") {
	NeuralNetwork NN;
	std::vector<double> testVec {1.0f, 3.4f, 0.5f};
	NN.addLayer (3, ACT_SIGMOID);
	NN.addLayer (3, ACT_SIGMOID);
	NN.addLayer (100, ACT_SIGMOID);
	NN.addLayer (2, ACT_SIGMOID);
	SECTION ("ENOUGH LAYERS") {
		REQUIRE (NN.m_layers.size() == 4);
	}
	SECTION ("GUESSING") {
		REQUIRE (NN.guess (testVec).size() == 2);
	}
}
