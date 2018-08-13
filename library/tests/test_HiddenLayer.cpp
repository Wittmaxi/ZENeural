/*
2018 Maximilian Wittmer
wittmaxi@linux.pizza

https://github.com/Wittmaxi/ZENeural/blob/master/LICENSE

*/
#include "../header/NeuralNetwork.hpp"
#include "../header/Layer.hpp"
#include "catch.hpp"

TEST_CASE("HiddenLayer")
{
    struct testConstructor : public ZNN::HiddenLayer<double>
    {
        testConstructor()
        {
            HiddenLayer<double> layer(10, 100);
            CHECK(layer.size == 10);
            CHECK(layer.inputSize == 100);
            CHECK(layer.neurons.size() == 10);
            CHECK(layer.neurons[0].weights.size() == 100);
        }
    };

    struct testCalculateDerivatives : public ZNN::HiddenLayer<double>
    {
        testCalculateDerivatives()
        {
            HiddenLayer<double> layer(10, 300);
            layer.layerOutputValues = std::vector<double>(10, 10);
            layer.calculateDerivatives(std::vector<double>(100, 3), std::vector<ZNN::Neuron<double>>(100, ZNN::Neuron<double>(10)));
            CHECK(layer.derivatives.size() == 10);
        }
    };

    struct testChangeWeights : public ZNN::HiddenLayer<double>
    {
        HiddenLayer<double> inputLayer;
        std::vector<double> oldWeights;
        testChangeWeights()
        {
            inputLayer.layerOutputValues = std::vector<double>(10, 10);
            withOutputLayer();
            andChangedWeights();
            CHECK(oldWeights != inputLayer.neurons[0].weights);
        }

        void withOutputLayer()
        {
            inputLayer = HiddenLayer<double>(1, 1);
            inputLayer.layerOutputValues = std::vector<double>{1};
            inputLayer.layerInputValues = std::vector<double>{1};
            oldWeights = inputLayer.neurons[0].weights;
        }

        void andChangedWeights()
        {
            inputLayer.calculateDerivatives(std::vector<double>(1, 1), std::vector<ZNN::Neuron<double>>(12, ZNN::Neuron<double>(1)));
            inputLayer.changeWeights();
        }
    };

    testConstructor();
    testCalculateDerivatives();
    testChangeWeights();
}