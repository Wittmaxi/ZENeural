#include "CLayer.h"
#include <iostream>


namespace ML {
CLayer::CLayer (int size, CLayer* lastLayer) {
	std::cout << "in the big function " << std::endl;
	m_lastLayer = lastLayer;
	std::cout << lastLayer << std::endl;
	int llSize = lastLayer->size();
	std::cout << "pointer arithmetics" << std::endl;
	for (int i = 0; i < size; i++){
		m_neurons.push_back (new CNeuron (llSize));
	}
	std::cout<< "outta the big function " << std::endl;
}

CLayer::CLayer (int size) {
	std::cout << "im here" << std::endl;
	m_lastLayer = nullptr;	
	for (int i = 0; i < size; i++){
		m_neurons.push_back (new CNeuron (0));
	}
	std::cout << "not anymore" << std::endl;
}


int CLayer::size () {
	return m_neurons.size();
}
}