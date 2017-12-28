#include "zeneural/CNode.h"
#include "zeneural/CLayer.h"
#include <cmath>
#include <iostream>

namespace ML {
	CNeuron::CNeuron (int numberWeights){
		for (int i = 0; i < numberWeights; i++) {
			m_weights.push_back (1.0f); //arbitrary starting value - 0.0 is the safest bet.
		}
		m_error = 0.0f;
		m_value = 0.0f;
	}
	std::vector<double>& CNeuron::getRawWeights () {
		return m_weights;
	}

	double CNeuron::fermi (double input) {
		input = 1 / ( 1 + exp (-input));
	}

	void CNeuron::wSum (std::vector<double> lastLayerValues) {
		double nVal = 0.0f;
		for (int i = 0; i < m_weights.size (); i++) {
			std::cout << "llva " << lastLayerValues[i] << std::endl;
			std::cout << "weights " << m_weights [i] << std::endl;
			std::cout << "calculating " << lastLayerValues [i] * m_weights[i] << std::endl;
			nVal += lastLayerValues [i] * m_weights [i];
		}
		m_value = fermi(nVal);
		std::cout<<nVal << std::endl;
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
				std::cout << "error  " <<  m_error << std::endl;
				std::cout << __LINE__ << ": 0.25f * m_error = " << 0.25f * m_error << std::endl;
				m_weights[i] += 0.003f * m_error;
			}
	}

	std::vector<double> CNeuron::backpropagate(){
		std::vector<double> retErrors;
		for (int i = 0; i < m_weights.size(); i++) {
			std::cout << __LINE__ << ": m_errors * m_weights[i]" << m_error * m_weights[i] << std::endl;
			retErrors.push_back(m_error * m_weights[i]);
		}
		return retErrors;
	}
}
