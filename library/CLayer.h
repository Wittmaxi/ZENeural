#include <vector>
#include "CNode.h"
#pragma once

namespace ML {
	class CLayer {
	public:
		CLayer(int size, CLayer* lastLayer);
		CLayer(int size);
		void setSums (std::vector<double>& sums);
		std::vector <CNeuron*>& getRawNeurons ();
		CLayer* getLastLayer();
		std::vector <double> getLayerValues ();
		void setErrors (std::vector<double> errors);
		std::vector<double> getErrors();
		void wSum ();
		int size();
		void backpropagate();
		void addErrors (std::vector<double> errors);
	private:
		CLayer* m_lastLayer;
		std::vector <CNeuron*> m_neurons;
	};
}
