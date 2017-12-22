#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include <vector>
#include <iostream>
#include "Neural.h"

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
	}
	SECTION ("RAW NODES") {
		REQUIRE (neurons.size() == 2);
		REQUIRE (neurons[1]->getRawWeights().size() == 2);
	}
	SECTION ("GUESSING"){
			REQUIRE (testNN.guess(testvec).size() == 2);
	}
}
