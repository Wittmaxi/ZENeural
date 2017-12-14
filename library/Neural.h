#pragma once

#include <vector>
#include "CLayer.h"

namespace ML {

class CNeural {
public:
	void addLayer (unsigned int layerSize);
	std::vector<double> guess (const std::vector <double>& input);
	std::vector<double> adjust (const std::vector<double>& input, const std::vector<double>& correct);
private:
	std::vector<CLayer*> Layers;
};
}