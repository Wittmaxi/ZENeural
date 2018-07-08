#pragma once
#include <vector>
#include <functional>
#include "Layer.hpp"
#include "debugMachine.h"
#include "normalisation.h"

namespace ZNN
{
class NeuralNetwork
{
	std::vector<Layer> layers;
	std::vector<double> target;
	std::vector<double> lastLayerDerivative;					  //derivative of the last layer
	std::vector<double> calculateLastLayerDerivatives(int index); //last layer
	std::vector<double> calculateDerivatives(int index);		  //calculate the derivatives
  public:
	Normalization norm;
	NeuralNetwork();
	~NeuralNetwork();
	void addLayer(size_t size, double stdWeightVal = 0.01f);
	std::vector<double> guess(std::vector<double> &inputs);
	double train(std::vector<double> &input, std::vector<double> &expected);
	void setLearnRate(double learnRate);
	void setNormalization(Normalization norm);
	const std::vector<Layer> getRawLayers();
};
} // namespace ZNN