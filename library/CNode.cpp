#include "CNode.h"
#include <iostream>

CNode::CNode (double numberW) {
	for (int i = 0; i<numberW -1; i++) {
		weights.push_back (0.1);
	}
}

double CNode::getSum () {
	return val;
}

void CNode::setSum (double sum) {
	val = sum;
}

void CNode::setError (double err) {
	error += err;
}

void CNode::calcWSum (std::vector<double>& lastLayerSums) {
	double tempVal = 0.0;
	for (int i = 0; i < weights.size(); i++) {
		tempVal += lastLayerSums[i] * weights[i];
	}
	val = tempVal;
}

void CNode::adjustWeights (CLayer* lastLayer) {
	std::cout << "adjusting weights" << std::endl;
	std::vector<CNode*> lln = lastLayer->getRawNodes();
	std::cout << "got ll nodes" << std::endl;
	for (int i = 0; i < lln.size(); i++) {
		lastLayer->setError (error * weights[i], i);
	}
	for (int i = 0; i < weights.size(); i ++) {
		weights[i] += error * 0.25;
	}
}