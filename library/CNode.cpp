#include "CNode.h"

namespace ML {
	CNeuron::CNeuron (int numberWeights){
		for (int i = 0; i < numberWeights; i++) {
			m_weights.push_back (1.0); //arbitrary starting value - 0.0 is the safest bet.
		}
		m_error = 0.0;
		m_value = 0.0;
	}
	std::vector<double>& CNeuron::getRawWeights () {
		return m_weights;
	}

	void CNeuron::wSum (std::vector<double> lastLayerValues) {
		double nVal = 0.0;
		for (int i = 0; i < m_weights.size (); i++) {
			nVal += lastLayerValues [i] * m_weights [i];
		}
		m_value = nVal;
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
}
