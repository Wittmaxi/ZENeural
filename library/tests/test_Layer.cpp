/*
2018 Maximilian Wittmer
wittmaxi@linux.pizza

https://github.com/Wittmaxi/ZENeural/blob/master/LICENSE

*/

#include "../header/NeuralNetwork.hpp"
#include "../header/Layer.hpp"
#include "catch.hpp"

TEST_CASE("Layer")
{
    struct testConstructor : public ZNN::Layer<double>
    {
        testConstructor()
        {
            Layer<double> layer(10, 100);
            CHECK(layer.size == 10);
            CHECK(layer.inputSize == 100);
            CHECK(layer.neurons.size() == 10);
            CHECK(layer.neurons[0].weights.size() == 100);
        }
    };

    struct testCalculate : public ZNN::Layer<double>
    {
        testCalculate()
        {
            Layer<double> layer(1000, 100);
            std::vector<double> inputs(999, 100);
            std::vector<double> outputs = layer.calculate(inputs);
            CHECK(outputs.size() == 1000);
            CHECK(outputs[0] <= 1);
        }
    };

    struct testWeightedSum : public ZNN::Layer<double>
    {
        testWeightedSum()
        {
            Layer<double> layer(10, 100);
            std::vector<double> inputs(9, 100);
            CHECK(layer.weightedSum(inputs).size() == 10);
        }
    };

    struct testBiasNode : public ZNN::Layer<double>
    {
        testBiasNode()
        {
            Layer<double> layer(10, 11);
            std::vector<double> inputs(10, 0);
            CHECK(layer.calculate(inputs)[0] != 0.5);
        }
    };

    testConstructor();
    testCalculate();
    testWeightedSum();
    testBiasNode();
}
