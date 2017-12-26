#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include <vector>
#include <iostream>
#include "Neural.h"
#include <cmath>

using namespace ML;

TEST_CASE("EVERY FUNCTION OF MY NN", "please dont you dare to fail on me.") {
	Neural testNN;
	std::vector <double> testvec;
	std::vector <CLayer*> layers;
	std::vector <CNeuron*> neurons;

	testvec.push_back (1.0);
	testvec.push_back (2.0);

	testNN.addLayer(2); //add a layer of size 2
	testNN.addLayer(2);
	testNN.addLayer(2);
	layers = testNN.getRawLayers();
	neurons = layers[1]->getRawNeurons();
	SECTION ("RAW LAYERS") {
		REQUIRE (layers.size() == 3);
		REQUIRE (layers[0]->size() == 2);
		REQUIRE (layers[1]->size() == 2);
		REQUIRE (layers[1]->getLastLayer()->size() == 2);
		REQUIRE (layers[1]->getLayerValues().size() == 2);
		REQUIRE (layers[1]->getLayerValues()[0] == 0.0);
		layers[1]->setSums (testvec);
		REQUIRE (layers[1]->getLayerValues() == testvec);
	}
	SECTION ("RAW NODES") {
		REQUIRE (neurons.size() == 2);
		REQUIRE (neurons[1]->getRawWeights().size() == 2);
		REQUIRE (neurons[1]->getValue () == 0.0);
		layers[0]->setSums (testvec);
		REQUIRE (layers[0]->getRawNeurons()[0]->getValue () == 1.0);
		neurons[0]->setError (2.0);
		REQUIRE (neurons[0]->getError() == 2.0);
	}
	SECTION ("GUESSING"){
			REQUIRE (testNN.guess(testvec).size() == 2);
			REQUIRE (testNN.guess(testvec)[0] != 0);
	}
	SECTION ("ADJUSTING") {
		REQUIRE (testNN.calcErrors(testvec, testvec)[0] == 0);
		std::cout << "clcerr" << std::endl;
		for (int i = 0; i < 100; i++) {
			testNN.adjust (testNN.guess (testvec), testvec);
		}
		REQUIRE (round(testNN.guess(testvec)[0]) == 1.0); //see if an improvement occured
	}
}
