#include <vector>
#include "CLayer.h"

namespace ML {
class Neural {
public:
	Neural ();
	void addLayer(int size);
	std::vector<double> guess (std::vector<double> input);
	std::vector<CLayer*>& getRawLayers();
private:
	std::vector <CLayer*> m_layers; //void* needs to be replaced by CLayer
};
}
