#include "zeneural/Neural.h"
#include <iostream>

namespace ML {
Neural::Neural () {

}

void Neural::addLayer(int size) {
	if (m_layers.size() == 0) {
		m_layers.push_back (new CLayer (size));
	} else {
		m_layers.push_back (new CLayer(size, m_layers[m_layers.size()-1]));
	}
}

std::vector<CLayer*>& Neural::getRawLayers() {
	return m_layers;
}

std::vector<double> Neural::guess(std::vector<double> input) {
	m_layers[0]->setSums(input);
	for (int i = 1; i < m_layers.size(); i++) {
		m_layers[i]->wSum();
	}
	return m_layers[m_layers.size()-1]->getLayerValues();
}

void Neural::adjust (std::vector<double> input, std::vector<double> expected) {
	std::vector<double> errors = calcErrors (guess (input), expected);

	m_layers[m_layers.size()-1]->setErrors(errors);
	m_layers[m_layers.size()-1]->backpropagate();
}

std::vector<double> Neural::calcErrors (std::vector<double> guess, std::vector<double> expected) {
	std::vector<double> retVec;
	for (auto i: expected) {
	}
	for (auto i: guess) {
	}
	for (int i = 0; i < guess.size(); i++) {
		retVec.push_back (expected[i] - guess[i]);
	}
	return retVec;
}

}
