#pragma once
#include <stdlib.h>
#include <vector>

namespace ML {
class CNeuron {
public:
	std::vector<double> m_weights;
	CNeuron (size_t llsize);
	double forwardSum (std::vector<double>& input);
};
}