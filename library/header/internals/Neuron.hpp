/*
2018 Maximilian Wittmer
wittmaxi@linux.pizza

https://github.com/Wittmaxi/ZENeural/blob/master/LICENSE

*/

#pragma once
#include <string>
#include "util/numbers.hpp"
#include "util/ThreadScheduler.hpp"

namespace ZNN {
template <class floatType>
class Neuron
{
  public:
	explicit Neuron(unsigned int inputSize);
	Neuron();
	floatType weightedSum(std::vector<floatType> inputs);

	std::string getAsString() const;
	void loadFromString (std::string string);

	std::vector<floatType> weights;
};

template<class floatType>
std::string Neuron<floatType>::getAsString () const {
	std::string temp;
	for (const auto& weight : weights)
		temp += Serializer <floatType>{}.serialize(weight) + ",";
	return temp;
}

template<class floatType>
void Neuron<floatType>::loadFromString (std::string string) {
	std::string temp;
	weights.resize(0);
	for (const auto i : string)
		if (i == ',') {
			weights.push_back (Serializer<floatType>{}.deserialize(temp));
			temp = "";
		}
		else
			temp += i;
}

template <class floatType>
Neuron<floatType>::Neuron(unsigned int inputSize)
	: weights(inputSize, 0.1f)
{
}

template <class floatType>
Neuron<floatType>::Neuron()
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