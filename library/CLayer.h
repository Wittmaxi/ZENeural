#include <vector>
#include "CNode.h"

namespace ML {
	class CLayer {
	public: 
		CLayer(int size, CLayer* lastLayer);
		CLayer(int size);
		std::vector <CNeuron*> getRawNeurons ();
		int size();
	private:
		CLayer* m_lastLayer;
		std::vector <CNeuron*> m_neurons;
	};
}