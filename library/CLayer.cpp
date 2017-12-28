#include "zeneural/CLayer.h"
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

	void CLayer::wSum () {
		std::vector<double> llval = m_lastLayer->getLayerValues();
		for (int i = 0; i < m_neurons.size (); i++) {
			m_neurons[i]->wSum (llval);
		}
	}

	std::vector<double> CLayer::getLayerValues () {
		std::vector<double> values;
		for (int i = 0; i < m_neurons.size(); i++) {
			values.push_back (m_neurons[i]->getValue());
		}
		return values;
	}

	int CLayer::size () {
		return m_neurons.size();
	}

	CLayer* CLayer::getLastLayer() {
		return m_lastLayer;
	}

	std::vector<double> CLayer::getErrors () {
		std::vector<double> retvec;
		for (auto i : m_neurons) {
			retvec.push_back(i -> getError());
		}
	}

	void CLayer::setErrors (std::vector<double> errors){
		for (int i = 0; i < m_neurons.size(); i++){
			m_neurons[i]->setError (errors[i]);
		}
	}

	void CLayer::addErrors (std::vector<double> errors){
		for (int i = 0; i < m_neurons.size(); i++){
			m_neurons[i]->addError (errors[i]);
		}
	}

	void CLayer::backpropagate () {
		if (m_lastLayer != nullptr) {
			for (auto i : m_neurons) {
				i->adjustWeights();
				m_lastLayer->addErrors(i->backpropagate());
			}
			m_lastLayer->backpropagate();
		}
	}
}
