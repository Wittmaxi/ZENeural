#pragma once

namespace ZNN {
	class CLayer;
	class NeuralNetwork {
		std::vector<CLayer> layers;
	public:
		NeuralNetwork();
		~NeuralNetwork();
		void addLayer (size_t number, double stdWeightVal = 0.1f);
		std::vector<double> guess (std::vector<double>& inputs);
		double train (std::vector<double>& input, std::vector<double>& expected);
		void setLearnRate (double learnRate);
		void setNormalisation (std::function<double(double)> func);
	}
}