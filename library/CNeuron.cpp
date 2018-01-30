#include "CNeuron.h"

namespace ML {
	CNeuron::CNeuron (size_t llsize) : m_weights (llsize, 0.5) {}

	double CNeuron::m_forwardSum (std::vector<double>& input) {
		double output = 0.0f;
		for (int i = 0; i < input.size(); i++) {
			output += (input[i] * m_weights[i]);
		} 
		return output;
	}
}