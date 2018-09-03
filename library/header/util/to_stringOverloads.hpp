#pragma once
#include <string>
#include "json.hpp"
namespace std
{
template <class T>
std::string to_string(ZNN::Neuron<T> &input)
{
}

template <class T>
std::string to_string(ZNN::Layer<T> &input)
{
}

template <class T>
std::string to_string(ZNN::NeuralNetwork<T> &input)
{
    nlohman::json temporary_json;
}
} // namespace std