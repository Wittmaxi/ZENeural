#include "zeneural/CNode.h"
#include "zeneural/CLayer.h"
#include <cmath>
#include <iostream>

namespace ML {
	CNeuron::CNeuron (int numberWeights){
		for (int i = 0; i < numberWeights; i++) {
			m_weights.push_back (10000.0f); //arbitrary starting value - 0.0 is the safest bet.
		}
		m_error = 0.0f;
		m_value = 0.0f;
	}
	std::vector<double>& CNeuron::getRawWeights () {
		return m_weights;
	}

	double CNeuron::sigmoid (double input) {
		return (1 / ( 1 + exp (-input)));
	}

	void CNeuron::wSum (std::vector<double> lastLayerValues) {
		double nVal = 0.0f;
		std::cout << "STARTING WSUM" << std::endl;
		for (int i = 0; i < m_weights.size (); i++) {
			std::cout << "LLVAL: " << lastLayerValues[i] << std::endl;
			std::cout << "WEIGHT: " << m_weights[i] << std::endl;
			nVal += lastLayerValues [i] * m_weights [i];
		}
		std::cout << "nVal: " << nVal << std::endl;
		std::cout << "SIGMOID nVAL: " << sigmoid (nVal) << std::endl;
		std::cout << "ENDING WSUM" << std::endl;
		m_value = sigmoid(nVal);
	}

	double CNeuron::getValue () {
		return m_value;
	}

	void CNeuron::setValue (double value) {
		m_value = value;
	}

	double CNeuron::getError() {
		return m_error;
	}

	void CNeuron::setError (double error) {
		m_error = error;
	}

	void CNeuron::addError (double error) {
		m_error += error;
	}

	void CNeuron::adjustWeights(){
			for (int i = 0; i < m_weights.size(); i++) {
				m_weights[i] += 0.0003 * m_error;
			}
	}

	std::vector<double> CNeuron::backpropagate(){
		std::vector<double> retErrors;
		for (int i = 0; i < m_weights.size(); i++) {
			retErrors.push_back(m_error * m_weights[i]);
		}
		return retErrors;
	}
}
