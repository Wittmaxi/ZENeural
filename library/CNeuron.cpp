#include "CNeuron.h"

namespace ML {
	CNeuron::CNeuron (size_t llsize) : m_weights (llsize, 0.5) {}

	double CNeuron::m_forwardSum (std::vector<double>& input) {
		d.out ("NeuralNetwork::guess() -> CLayer::m_forward -> CNeuron::m_forward_sum");
		d.out ("--");
		double output = 0.0f;
		for (size_t i = 0; i < m_weights.size(); i++) {
			d.out ("Calculating wSum from last layer. Iteration: " + std::to_string (i));
			output += (input.at(i) * m_weights.at(i));
		} 
		d.out ("--");
		return output;
	}
}