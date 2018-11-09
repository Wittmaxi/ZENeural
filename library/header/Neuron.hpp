
namespace ZNN {
template <class floatType>
class Neuron
{
  public:
	Neuron(unsigned int inputSize);
	floatType weightedSum(std::vector<floatType> inputs);

	std::vector<floatType> weights;
};


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