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
	double train (std::vector<double>& input, std::vector<double>& expected);
	void addLayer (size_t layerSize, std::function <double(double)> activation = ACT_SIGMOID);
	std::vector<CLayer> m_layers;
private:
	size_t m_trainingEpochs = 10;
	void m_forward ();
	void m_backward (std::vector<double>& expected);
	std::vector<double>& calculateErrors (std::vector<double>& expected, std::vector<double>& out);
};
}