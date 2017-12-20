#pragma once

#include <vector>

class CNode;

class CLayer {
public:
	CLayer (unsigned int layerSize, unsigned int lastLayerSize);
	void setSums (std::vector<double>& sums);
	void setErrors (std::vector<double>& errors);
	void setError (double error, unsigned int index);
	void calcWSums (std::vector<double>& lastLayerSums);
	std::vector<double> getSums();
	void backPropagate(std::vector<CLayer*>& layers);
	int size();
	std::vector<CNode*> getRawNodes();
private:
	std::vector<CNode*> Nodes;
};