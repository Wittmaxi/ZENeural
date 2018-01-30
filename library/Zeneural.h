#pragma once 
#include <vector>
#include <stdlib.h>

#include "CLayer.h"
#include "activation.h"


namespace ML {
class NeuralNetwork {
public:
	NeuralNetwork ();
	std::vector<double> guess (std::vector<double>& input);
	void addLayer (size_t layerSize, double (*activation) (double));
	std::vector<CLayer> m_layers;
private:
};
}