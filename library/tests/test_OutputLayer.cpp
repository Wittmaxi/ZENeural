/*
2018 Maximilian Wittmer
wittmaxi@linux.pizza

https://github.com/Wittmaxi/ZENeural/blob/master/LICENSE

*/

#include "../header/NeuralNetwork.hpp"
#include "../header/Layer.hpp"
#include "catch.hpp"

TEST_CASE("OutputLayer")
{
    struct testConstructor : public ZNN::OutputLayer<double>
    {
        testConstructor()
        {
            OutputLayer<double> layer(10, 100);
            CHECK(layer.size == 10);
            CHECK(layer.inputSize == 100);
            CHECK(layer.neurons.size() == 10);
            CHECK(layer.neurons[0].weights.size() == 100);
        }
    };

    struct testCalculateDerivatives : public ZNN::OutputLayer<double>
    {
        testCalculateDerivatives()
        {
            ZNN::OutputLayer<double> outLayer(10, 100);
            outLayer.errors = std::vector<double>(10, -10);
            outLayer.layerOutputValues = std::vector<double>(10, 10);
            outLayer.calculateDerivatives();
            CHECK(outLayer.derivatives.size() == 10);
        }
    };

    struct testChangeWeights : public ZNN::OutputLayer<double>
    {
        OutputLayer<double> outLayer;
        std::vector<double> oldWeights;
        testChangeWeights()
        {
            withOutputLayer();
            andChangedWeights();
            CHECK(oldWeights != outLayer.neurons[0].weights);
        }

        void withOutputLayer()
        {
            outLayer = OutputLayer<double>(1, 1);
            outLayer.errors = std::vector<double>{-3};
            outLayer.layerOutputValues = std::vector<double>{1};
            outLayer.layerInputValues = std::vector<double>{1};
            oldWeights = outLayer.neurons[0].weights;
        }

        void andChangedWeights()
        {
            outLayer.calculateDerivatives();
            outLayer.changeWeights();
        }
    };

    struct testBiasNode : public ZNN::OutputLayer<double>
    {
        testBiasNode()
        {
            OutputLayer<double> layer(10, 11);
            std::vector<double> inputs(10, 0);
            CHECK(layer.calculate(inputs)[0] != 0.5);
        }
    };

    testConstructor();
    testCalculateDerivatives();
    testChangeWeights();
    testBiasNode();
}
