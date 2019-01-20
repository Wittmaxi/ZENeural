/*
2018 Maximilian Wittmer
wittmaxi@linux.pizza

https://github.com/Wittmaxi/ZENeural/blob/master/LICENSE

*/

#define CATCH_CONFIG_MAIN
#include "../header/NeuralNetwork.hpp"
#include "../header/internals/Layer.hpp"
#include "../header/internals/GatedNeuron.hpp"
#include "../header/VanillaRecurrentNetwork.hpp"
#include "../header/Perceptron.hpp"
#include "../header/internals/typedefs.hpp"
#include "../header/internals/util/numbers.hpp"
#include "../header/internals/util/ThreadScheduler.hpp"
#include "../header/internals/util/operations.hpp"
#include "../external/catch.hpp"

#include "test_Layer.hpp"
#include "test_HiddenLayer.hpp"
#include "test_Neuron.hpp"
#include "test_OutputLayer.hpp"
#include "test_NN.hpp"
#include "test_VRNN.hpp"
#include "test_Perceptron.hpp"
#include "test_numbers.hpp"
#include "test_threadScheduler.hpp"
#include "test_GatedNeuron.hpp"
#include "test_operations.hpp"