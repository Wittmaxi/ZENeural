#include "CLayer.h"

namespace ML {
CLayer::CLayer(size_t size, size_t llsize) : m_neurons (size, CNeuron (llsize)) {}	

void CLayer::m_forward (std::vector<double>& input) {
	d.out ("NeuralNetwork::guess --> CLayer::m_forward");
	d.out ("================================");
	m_input = input;
	m_output.resize (0);
	for (size_t i = 0; i < m_neurons.size(); ++i) {
		d.out ("Looping through Neurons of Layer. Iterations: " + std::to_string (i));
		d.debug ("Size of m_neurons: " + std::to_string(m_neurons.size()));
		m_output.push_back (m_normalisation(m_neurons.at(i).m_forwardSum (input)));
	}
	d.out ("================================");
}

void CLayer::m_backward (std::vector<double>& expected) {
	for (size_t i = 0; i < m_neurons.size(); i++) {
		for (size_t j = 0; j < m_neurons.at(i).m_weights.size(); j++) {
			m_neurons.at(i).m_weights[j] -= (0.03f * expected.at(i) * m_output.at(i) * (1 - m_output.at(i)) * m_input.at(j)); 
		}
	}
}
}