/*
2018 Maximilian Wittmer
wittmaxi@linux.pizza

https://github.com/Wittmaxi/ZENeural/blob/master/LICENSE

*/

#define CATCH_CONFIG_MAIN
#define CATCH_CONFIG_FAST_COMPILE
#define CATCH_CONFIG_DISABLE_STRINGIFICATION
#define CATCH_CONFIG_DISABLE_MATCHERS
#include "../header/NeuralNetwork.hpp"
#include "../header/Layer.hpp"
#include "catch.hpp"

#include "test_Layer.hpp"
#include "test_HiddenLayer.hpp"
#include "test_Neuron.hpp"
#include "test_OutputLayer.hpp"
#include "test_NN.hpp"
