#include "CLayer.h"
#include <iostream>

namespace ML {
	CLayer::CLayer (int size, CLayer* lastLayer) {
		m_lastLayer = lastLayer;
		int llSize = lastLayer->size();
		for (int i = 0; i < size; i++){
			m_neurons.push_back (new CNeuron (llSize));
		}
	}

	CLayer::CLayer (int size) {
		m_lastLayer = nullptr;
		for (int i = 0; i < size; i++){
			m_neurons.push_back (new CNeuron (0));
		}
	}

	std::vector <CNeuron*>& CLayer::getRawNeurons () {
		return this->m_neurons;
	}

	void CLayer::setSums(std::vector<double>& sums) {
		for (int i = 0; i < sums.size (); i++) {
			m_neurons[i]->setValue (sums[i]);
		}
	}

	int CLayer::size () {
		return m_neurons.size();
	}
}
