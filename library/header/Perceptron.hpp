/*
2018 Maximilian Wittmer
wittmaxi@linux.pizza

https://github.com/Wittmaxi/ZENeural/blob/master/LICENSE

*/

#pragma once
#include "Neuron.hpp"
#include "normalization.hpp"

namespace ZNN {
template<class floatType>
class Perceptron {
public:
    Perceptron(unsigned int inputs);
    floatType guess (std::vector<floatType> input);
    floatType train (std::vector<floatType> input, floatType target);

    void setNormalization (Normalization<floatType> norm);
    void setLearningRate (floatType lr);
protected:
    floatType calculateError (floatType result, floatType target);
    Neuron<floatType> neuron;
    Normalization<floatType> normalization = ZNN::Fermi<double>();
    floatType learningRate = 0.25;
};

template<class floatType>
Perceptron<floatType>::Perceptron(unsigned int inputs) : neuron (inputs + 1) 
{
}

template<class floatType>
floatType Perceptron<floatType>::guess (std::vector<floatType> input) {
    input.push_back(1);
    return normalization.normalization(neuron.weightedSum(input));
}

template<class floatType>
floatType Perceptron<floatType>::train (std::vector<floatType> input, floatType target) {
    floatType err = calculateError (guess (input), target);
    for (size_t i = 0; i < input.size(); i++)
        neuron.weights[i] += learningRate * err * input[i];
    return err;
}

template<class floatType>
floatType Perceptron<floatType>::calculateError (floatType result, floatType target) {
    return target - result;
}

template<class floatType>
void Perceptron<floatType>::setNormalization (Normalization<floatType> norm) {
    normalization = norm;
}

template<class floatType>
void Perceptron<floatType>::setLearningRate (floatType lr) {
    learningRate = lr;
}

}