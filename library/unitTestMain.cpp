#define CATCH_CONFIG_MAIN
#include <iostream>
#include <vector>
#include <stdlib.h>
#include <time.h>

#include "catch.hpp"
#include "Neural.h"
#include "CLayer.h"
#include "CNode.h"

TEST_CASE("Neural Network", "[NN]") {
	std::vector <double> testvec;
	testvec.push_back (1);
	testvec.push_back(1);
	ML::CNeural tnn{};
	tnn.addLayer(2);
	tnn.addLayer(2);
	tnn.addLayer(2);
	SECTION ("RAW LAYERS") {
		std::vector <CLayer*> layersTest;
		layersTest = tnn.getRawLayers();
		std::vector<CNode*> nodesTest;
		SECTION ("RAW NODES") {
			nodesTest = layersTest[0]->getRawNodes();
			REQUIRE (nodesTest.size() == 2);
		}
		SECTION ("WSUM") {
			REQUIRE (layersTest.size() == 3);
			REQUIRE (layersTest[0]->getSums().size() == 2);
		}
		SECTION ("SIZE") {
			REQUIRE (tnn.numbLayers() == 3);
			REQUIRE ((tnn.guess(testvec)).size() == 2);
		}
	}
}