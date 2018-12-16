/*
2018 Maximilian Wittmer
wittmaxi@linux.pizza

https://github.com/Wittmaxi/ZENeural/blob/master/LICENSE

*/

#pragma once
#include <string>
#include "util/numbers.hpp"
#include "util/ThreadScheduler.hpp"

namespace ZNN
{
template <class floatType>
struct Gate
{
    Gate(unsigned int inputSize);
    Gate(unsigned int inputSize, const ZNN::Normalization<floatType> &norm);
    std::vector<floatType> calculateActivations(const std::vector<double> &input);
    void adjust(const std::vector<double> &derivatives);
    OutputLayer<floatType> layer;
};

template <class floatType>
Gate<floatType>::Gate(unsigned int inputSize, const ZNN::Normalization<floatType> &norm)
    : layer(inputSize, inputSize + 1)
{
    layer.normalization = norm;
}

template <class floatType>
Gate<floatType>::Gate(unsigned int inputSize)
    : Gate (inputSize, ZNN::Fermi<double>())
{
}

template <class floatType>
std::vector<floatType> Gate<floatType>::calculateActivations(const std::vector<double> &input)
{
    return layer.calculate(input);
}

template <class floatType>
void Gate<floatType>::adjust(const std::vector<double> &derivatives)
{
    layer.derivatives = derivatives;
    layer.changeWeights();
}

} // namespace ZNN
