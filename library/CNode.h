#include <vector>

namespace ML {
	class CNeuron {
	public:
		CNeuron (int numberWeights);
		std::vector<double>& getRawWeights ();
	private:
		std::vector<double> m_weights;
		double m_value;
		double m_error;
	};
}