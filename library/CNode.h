#include <vector>

namespace ML {
	class CNeuron {
	public:
		CNeuron (int numberWeights);
		std::vector<double>& getRawWeights ();
		double getValue ();
		void setValue (double value);
	private:
		std::vector<double> m_weights;
		double m_value;
		double m_error;
	};
}
