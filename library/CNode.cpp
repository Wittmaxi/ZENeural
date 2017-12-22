#include "CNode.h"

namespace ML {
	CNeuron::CNeuron (int numberWeights){
		for (int i = 0; i < numberWeights; i++) {
			m_weights.push_back (0.0); //arbitrary starting value - 0.0 is the safest bet.
		}
	}
	std::vector<double>& CNeuron::getRawWeights () {
		return m_weights;
	}
}