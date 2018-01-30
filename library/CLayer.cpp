#include "CLayer.h"

namespace ML {
CLayer::CLayer(size_t size, size_t llsize) : m_neurons (size, CNeuron (llsize)) {}	

void CLayer::m_forward (std::vector<double>& input) {
	m_input = input;
	m_output.resize (0);
	for (size_t i = 0; i < input.size(); ++i) {
		m_output.push_back (m_normalisation(m_neurons[i].m_forwardSum (input)));
	}
}
}