/*
2018 Maximilian Wittmer
wittmaxi@linux.pizza

https://github.com/Wittmaxi/ZENeural/blob/master/LICENSE

*/

#pragma once
#include "../includes.hpp"
#include "util/assert.hpp"
#include "util/normalization.hpp"
#include "LSTMUnit.hpp"
#include "util/ThreadScheduler.hpp"

namespace ZNN
{
template<class floatType>
class LSTMLayer {
public:
	LSTMLayer() {}
	LSTMLayer(unsigned int _size, unsigned int _inputSize);

	const std::vector<floatType> &calculate(const std::vector<floatType> &inputs);
	std::vector<floatType> weightedSum(const std::vector<floatType> &inputs);

	std::string getAsString() const;
	void loadFromString(const std::string &string);

	void changeWeights();

	unsigned int size;
	unsigned int inputSize;
	floatType learningRate = 0.2;

	Normalization<floatType> normalization;
	std::vector<LSTMUnit> neurons;
};

LSTMLayer::LSTMLayer(unsigned int _size, unsigned int _inputSize)
{
}

} // namespace ZNN