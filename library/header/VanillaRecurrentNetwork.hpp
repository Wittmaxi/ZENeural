/*
2018 Maximilian Wittmer
wittmaxi@linux.pizza

https://github.com/Wittmaxi/ZENeural/blob/master/LICENSE

*/

#pragma once
#include "NeuralNetwork.hpp"

namespace ZNN {
template<class floatType>
class VanillaRecurrentNeuralNetwork : public FeedForwardNeuralNetwork<floatType> {
public: 
    void addHiddenLayer (unsigned int layerSize);
    void clearStates ();
	std::vector<floatType> guess(const std::vector<floatType>& input);
};
}