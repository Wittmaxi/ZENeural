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

}