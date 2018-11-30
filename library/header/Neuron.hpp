/*
2018 Maximilian Wittmer
wittmaxi@linux.pizza

https://github.com/Wittmaxi/ZENeural/blob/master/LICENSE

*/

#pragma once
#include <string>
#include <string_view>

namespace ZNN {
template <class floatType>
class Neuron
{
  public:
	explicit Neuron(unsigned int inputSize);
	floatType weightedSum(std::vector<floatType> inputs);

	std::string getAsString();

	std::vector<floatType> weights;
};

template<class floatType>
std::string Neuron<floatType>::getAsString () {
	std::string temp;
	for (const auto& weight : weights)
		for (size_t readPos = 0; readPos < sizeof (floatType); readPos++)
			temp += std::string (1, reinterpret_cast<const char*> (&weight)[readPos]);
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