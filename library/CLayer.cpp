#include "CLayer.h"

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


int CLayer::size () {
	return m_neurons.size();
}
}