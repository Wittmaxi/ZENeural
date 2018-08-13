/*
2018 Maximilian Wittmer
wittmaxi@linux.pizza

https://github.com/Wittmaxi/ZENeural/blob/master/LICENSE

*/

#include "../header/NeuralNetwork.hpp"
#include "../header/Layer.hpp"
#include "catch.hpp"

TEST_CASE("Neuron")
{
    struct testConstructor : public ZNN::Neuron<double>
    {
        testConstructor()
        {
            Neuron<double> neuron(1000);
            CHECK(neuron.weights.size() == 1000);
        }
    };

    struct testWeightedSum : public ZNN::Neuron<double>
    {
        testWeightedSum()
        {
            std::vector<double> fakeInputs(2, 10);
            Neuron<double> neuron(2);

            neuron.weights = std::vector<double>(2, 0.1);
            CHECK(neuron.weightedSum(fakeInputs) == 2);
        }
    };

    testConstructor();
    testWeightedSum();
}