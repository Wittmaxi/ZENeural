#include "Zeneural.h"

namespace ML {
NeuralNetwork::NeuralNetwork () {

}

void NeuralNetwork::addLayer (size_t layerSize, double (*activation) (double)) {
	if (m_layers.size() == 0) {
		m_layers.push_back (CLayer (layerSize, 0));
		m_layers[1].m_normalisation = activation;
	} else {
		m_layers.push_back (CLayer (layerSize, m_layers[m_layers.size()-1].m_neurons.size()));
		m_layers[m_layers.size()-1].m_normalisation = activation;
	}
}

std::vector<double> NeuralNetwork::guess (std::vector<double>& input) {
	m_layers[1].m_input = input;
	for (size_t i = 1; i < m_layers.size(); ++i) {
		m_layers[i].m_forward (m_layers[m_layers.size() -1].m_output);
	}
	return m_layers[m_layers.size() -1].m_output;
}
}