#pragma once
#include <vector>
#include <functional>
#include "CNeuron.h"
#include "debugMachine.h"

namespace ML {
class CLayer{
public:
	CLayer(size_t size, size_t llsize);
	std::vector<CNeuron> m_neurons;
	std::vector<double> m_input;
	std::vector<double> m_output;
	std::vector<double> m_expected;
	std::function<double(double)> m_normalisation;
	void m_forward (std::vector<double>& input);
	void m_backward (std::vector<double>& expected);
};
}