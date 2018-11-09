#ifndef __TYPEDEFS_HPP
#define __TYPEDEFS_HPP


namespace ZNN {
    
template<class floatType = double>
using FFNN = FeedForwardNeuralNetwork<floatType>;  


template<class floatType = double>
using NeuralNetwork = FFNN<floatType>;

}

#endif