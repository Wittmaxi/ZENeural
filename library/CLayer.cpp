#include "CLayer.h"

namespace ML {
CLayer::CLayer(size_t size, size_t llsize) : m_neurons (size, CNeuron (llsize)) {}	

CLayer::m_forward (std::vector<double>& input) {
	m_input = input;
	for (size_t i = 0; i < input.size(); ++i) {
		m_weights[i].m_forwardSum (input);
	}
}
}