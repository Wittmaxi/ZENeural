#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include <vector>
#include "Neural.h"

using namespace ML;

TEST_CASE("EVERY FUNCTION OF MY NN", "please dont you dare to fail on me.") {
	Neural testNN;
	std::vector <CLayer*> layers;

	testNN.addLayer(2); //add a layer of size 2
	testNN.addLayer(2);
	testNN.addLayer(2);
	SECTION ("RAW LAYERS") {
		layers = testNN.getRawLayers();
		REQUIRE (layers.size() == 3);
		REQUIRE (layers[0]->size() == 2);
	}
}