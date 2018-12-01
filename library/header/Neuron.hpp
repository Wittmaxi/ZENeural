/*
2018 Maximilian Wittmer
wittmaxi@linux.pizza

https://github.com/Wittmaxi/ZENeural/blob/master/LICENSE

*/

#pragma once
#include <string>
#include "util/numbers.hpp"

namespace ZNN {
template <class floatType>
class Neuron
{
  public:
	explicit Neuron(unsigned int inputSize);
	floatType weightedSum(std::vector<floatType> inputs);

	std::string getAsString();
	void loadFromString (const std::string& string);

	std::vector<floatType> weights;
};

template<class floatType>
std::string Neuron<floatType>::getAsString () {
	std::string temp;
	for (const auto& weight : weights)
		temp += Serializer <floatType>{}.serialize(weight) + ",";
	return temp;
}

template <class floatType>
Neuron<floatType>::Neuron(unsigned int inputSize)
	: weights(inputSize, 0.1f)
{
}

template <class floatType>
floatType Neuron<floatType>::weightedSum(std::vector<floatType> inputs)
{
	floatType temporaryResult = 0.0;
	for (size_t j = 0; j < weights.size(); j++)
		temporaryResult += inputs[j] * weights[j];
	return temporaryResult;
}
}