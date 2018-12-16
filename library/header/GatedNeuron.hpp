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

template <class floatType>
struct LSTMUnit
{
    LSTMUnit (unsigned int inputSize);
    std::vector<floatType> calculate(const std::vector<floatType> &input);
    std::vector<double> previousOutput;
    std::vector<double> previousHiddenCellState;
    Gate<floatType> cellStateGate;
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
    : Gate(inputSize, ZNN::Fermi<floatType>())
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
template<class floatType>
LSTMUnit<floatType>::LSTMUnit (unsigned int inputSize, unsigned int hiddenStates) 
: forgetGate (inputSize), inputGate (inputSize), outputGate(inputSize), cellStateGate (inputSize), previousOutput (inputSize, )
{
}

template<class floatType>
std::vector<floatType> LSTMUnit<floatType>::calculate(const std::vector<floatType> &input)
{
    previousOutput = UTIL::addVectors (UTIL::multiplyVectors (forgetGate.calculateActivations(input, previousHiddenCellState), previousOutput), UTIL::multiplyVectors (inputGate.calculateActivations(input, previousHiddenCellState), cellStateGate.calculateActivations (input, previousHiddenCellState)));
    previousHiddenCellState = UTIL::multiplyVectors (outputGate.calculateActivations(input, previousHiddenCellState), previousOutput);
    return previousOutput;
}

} // namespace ZNN
