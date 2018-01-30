#pragma once
#include <vector>
#include <functional>
#include "CNeuron.h"

namespace ML {
class CLayer{
public:
	CLayer(size_t size, size_t llsize);
	std::vector<CNeuron> m_neurons;
	std::vector<double> m_input;
	std::vector<double> m_output;
	std::vector<double> m_expected;
	double (*m_normalisation) (double);
	void m_forward (std::vector<double>& input);
	void m_backward (std::vector<double>& expected);
};
}