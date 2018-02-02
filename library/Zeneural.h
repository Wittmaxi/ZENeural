#pragma once 
#include <vector>
#include <stdlib.h>
#include <iostream>
#include "debugMachine.h"
#include <functional>

#include "CLayer.h"
#include "activation.h"


namespace ML {
class NeuralNetwork {
public:
	NeuralNetwork (bool debug);
	std::vector<double> guess (std::vector<double>& input);
	void addLayer (size_t layerSize, std::function <double(double)> activation = ACT_SIGMOID);
	std::vector<CLayer> m_layers;
private:
};
}