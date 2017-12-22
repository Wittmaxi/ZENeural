#include "Neural.h"

namespace ML {
Neural::Neural () {

}

void Neural::addLayer(int size) {
	if (m_layers.size() == 0) {
		m_layers.push_back (new CLayer (size));
	} else {
		m_layers.push_back (new CLayer(size, m_layers[m_layers.size()-2]));
	}
}

std::vector<CLayer*>& Neural::getRawLayers() {
	return m_layers;
}
}