/*
2018 Maximilian Wittmer
wittmaxi@linux.pizza

https://github.com/Wittmaxi/ZENeural/blob/master/LICENSE

*/

#pragma once
#include <string>
#include "util/numbers.hpp"
#include "util/ThreadScheduler.hpp"
#include "util/operations.hpp"

namespace ZNN
{
template <class floatType>
struct Gate
{
    Gate(unsigned int inputSize);
    Gate(unsigned int inputSize, const ZNN::Normalization<floatType> &norm);
    std::vector<floatType> calculateActivations(const std::vector<floatType> &input, const std::vector<floatType> &previousOutput);
    void adjust(const std::vector<floatType> &derivatives);
    OutputLayer<floatType> layer;
};

template<class floatType>
struct LSTMUnit
{
    std::vector <floatType> previousOutput; 
    Gate<floatType> forgetGate;
    Gate<floatType> inputGate;
    Gate<floatType> outputGate;
};

template <class floatType>
Gate<floatType>::Gate(unsigned int inputSize, const ZNN::Normalization<floatType> &norm)
    : layer(inputSize, inputSize + 1)
{
    layer.normalization = norm;
}

template <class floatType>
Gate<floatType>::Gate(unsigned int inputSize)
    : Gate (inputSize, ZNN::Fermi<floatType>())
{
}

template <class floatType>
std::vector<floatType> Gate<floatType>::calculateActivations(const std::vector<floatType> &input, const std::vector<floatType> &previousOutput)
{
    return layer.calculate(UTIL::addVectors(input, previousOutput));
}

template <class floatType>
void Gate<floatType>::adjust(const std::vector<floatType> &derivatives)
{
    layer.derivatives = derivatives;
    layer.changeWeights();
}

///


} // namespace ZNN
