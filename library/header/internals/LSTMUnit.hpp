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
    void adjust(const std::vector<floatType> &nextLayersDerivatives, const std::vector<Neuron<floatType>> &nextLayersNeurons);
    HiddenLayer<floatType> layer;
};

template <class floatType>
struct LSTMUnit
{
    LSTMUnit(unsigned int inputSize, unsigned int hiddenStates);
    std::vector<floatType> calculate(const std::vector<floatType> &input);
    void adjust(const std::vector<floatType> &nextLayerDerivatives, const std::vector<Neuron<floatType>> &nextLayersNeurons);
    void adjust(const std::vector <LSTMUnit<floatType>> & units);
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
void Gate<floatType>::adjust(const std::vector<floatType> &nextLayersDerivatives, const std::vector<Neuron<floatType>> &nextLayersNeurons)
{
    layer.train(nextLayersDerivatives, nextLayersNeurons);
}

///
template <class floatType>
LSTMUnit<floatType>::LSTMUnit(unsigned int inputSize, unsigned int hiddenStates)
    : forgetGate(inputSize), inputGate(inputSize), outputGate(inputSize), cellStateGate(inputSize), previousOutput(inputSize, 0)
{
}

template <class floatType>
void LSTMUnit<floatType>::adjust(const std::vector<floatType> &nextLayersDerivatives, const std::vector<Neuron<floatType>> &nextLayersNeurons)
{
    outputGate.train(nextLayersDerivatives, nextLayersNeurons);
    inputGate.train(nextLayersDerivatives, nextLayersNeurons);
    forgetGate.train(nextLayersDerivatives, nextLayersNeurons);
}

template <class floatType>
void LSTMUnit<floatType>::adjust(const std::vector <LSTMUnit<floatType>> &units)
{
    for (const auto &i : units) {
        adjust (i.outputGate.layer.derivatives, i.outputGate.layer.neurons);
        adjust (i.inputGate.layer.derivatives, i.inputGate.layer.neurons);
        adjust (i.forgetGate.layer.derivatives, i.forgetGate.layer.neurons);
    }
}

template <class floatType>
std::vector<floatType> LSTMUnit<floatType>::calculate(const std::vector<floatType> &input)
{
    previousOutput = UTIL::addVectors(UTIL::multiplyVectors(forgetGate.calculateActivations(input, previousHiddenCellState), previousOutput),
                                      UTIL::multiplyVectors(inputGate.calculateActivations(input, previousHiddenCellState), cellStateGate.calculateActivations(input, previousHiddenCellState)));
    previousHiddenCellState = UTIL::multiplyVectors(outputGate.calculateActivations(input, previousHiddenCellState), previousOutput);
    return previousOutput;
}

} // namespace ZNN
