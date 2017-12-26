#include <vector>
#pragma once

namespace ML {
	class CNeuron {
	public:
		CNeuron (int numberWeights);
		std::vector<double>& getRawWeights ();
		void wSum (std::vector<double> lastLayerValues);
		double getValue ();
		void setValue (double value);
		double getError();
		void setError (double error);
		void addError (double error);
		void adjustWeights();
		std::vector<double> backpropagate();
	private:
		std::vector<double> m_weights;
		double m_value;
		double m_error;
	};
}
