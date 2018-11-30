/*
2018 Maximilian Wittmer
wittmaxi@linux.pizza

https://github.com/Wittmaxi/ZENeural/blob/master/LICENSE

*/

#pragma once
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
std::string getAsString () {
	std::stringstream temp;
	for (const auto& i : weights)
		temp << i << "|";
	return temp.str();
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