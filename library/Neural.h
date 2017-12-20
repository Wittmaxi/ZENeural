#pragma once

#include <vector>
#include "CLayer.h"

namespace ML {

class CNeural {
public:
	void addLayer (unsigned int layerSize);
	std::vector<double> guess (std::vector <double>& input);
	std::vector<double> adjust (std::vector<double>& input, std::vector<double>& correct);
	//for unit testing. lol
	std::vector<CLayer*> getRawLayers();
	int numbLayers();
private:
	std::vector<CLayer*> Layers;
};
}