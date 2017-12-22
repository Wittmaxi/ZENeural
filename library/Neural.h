#include <vector>
#include "CLayer.h"

namespace ML {
class Neural {
public:
	Neural ();
	void addLayer(int size);
	std::vector<CLayer*>& getRawLayers();
private:
	std::vector <CLayer*> m_layers; //void* needs to be replaced by CLayer
};
}