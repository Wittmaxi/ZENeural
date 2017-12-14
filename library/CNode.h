#pragma once
#include <vector>
#include "CLayer.h"

class CNode {
public:
	CNode (double numberW);
	double getSum ();
	void setSum (double sum);
	void setError (double err);
	void calcWSum (std::vector<double>& lastLayerSums);
	void adjustWeights (CLayer lastLayer);
private:
	std::vector<double> weights;
	double val;
	double error;
};