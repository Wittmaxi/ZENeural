#include "CLayer.h"
#include "CNode.h"
#include <iostream>

CLayer::CLayer (unsigned int layerSize, unsigned int lastLayerSize) {
	if (layerSize == 0) {
		return;
	}
	for (int i = 0; i < layerSize-1; i++) {
		Nodes.push_back (new CNode(lastLayerSize));
	}
}

void CLayer::setSums (std::vector<double>& sums) {
	for (int i = 0; i < sums.size(); i++) {
		Nodes[i]->setSum (sums[i]);
	}
}

void CLayer::setErrors (std::vector<double>& errors) {
	for (int i = 0; i < errors.size(); i++) {
		Nodes[i]->setError (errors[i]);
	}		
}

void CLayer::setError (double error, unsigned int index) {
	Nodes[index]->setError (error);
}

void CLayer::calcWSums (std::vector<double>& lastLayerSums) {
	for (int i = 0; i < Nodes.size(); i++) {
		Nodes[i]->calcWSum (lastLayerSums);
	}
}

std::vector<double> CLayer::getSums() {
	std::vector<double> sums;
	for (int i = 0; i < Nodes.size (); i++) {
		sums.push_back (Nodes[i]->getSum());
	}
	return sums;
}

void CLayer::backPropagate(std::vector<CLayer*>& layers) {
	for (int i = layers.size()-1; i > 1; i--) {
		for (int j = 0; j < layers[i]->size(); j++) {
			Nodes[j]-> adjustWeights(*layers[i-1]);
		}
	}
}

int CLayer::size () {
	std::cout << "getting size" << std::endl;
	return Nodes.size();
	std::cout << "got the size" << std::endl;
}