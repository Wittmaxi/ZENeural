#define CATCH_CONFIG_MAIN
#include "../header/NeuralNetwork.hpp"
#include "../header/Layer.hpp"
#include "catch.hpp"

TEST_CASE("Neural Network")
{

    struct testSetInputLayerSize : public ZNN::NeuralNetwork<double>
    {
        testSetInputLayerSize()
        {
            setInputLayerSize(1);
            CHECK(this->inputLayerSize == 1);
        }
    };

    struct testSetOutputLayerSize : public ZNN::NeuralNetwork<double>
    {
        testSetOutputLayerSize()
        {
            setOutputLayerSize(1);
            CHECK(this->outputLayerSize == 1);
        }
    };

    struct testAddHiddenLayer : public ZNN::NeuralNetwork<double>
    {
        const int numberHiddenLayers = 4;
        const int hiddenLayerSize = 3;
        testAddHiddenLayer()
        {
            withHiddenLayers();
            requireCorrectNumberHiddenLayers();
            requireHiddenLayersCorrectNeuronSize();
        }

        void withHiddenLayers()
        {
            for (size_t i = 0; i < numberHiddenLayers; i++)
            {
                addHiddenLayer(hiddenLayerSize);
            }
        }

        void requireCorrectNumberHiddenLayers()
        {
            CHECK(this->layers.size() == numberHiddenLayers);
        }

        void requireHiddenLayersCorrectNeuronSize()
        {
            for (auto i : this->layers)
            {
                CHECK(i.size == hiddenLayerSize);
            }
        }
    };

    struct testGuess : public ZNN::NeuralNetwork<double>
    {
        const int inputSize = 1;
        const int outputSize = 2;
        const int hiddenSize = 0;
        const int hiddenLayerSize = 2;

        testGuess()
        {
            withNeuralNetwork();
            std::vector<double> guessOutput = andGuessOutput();
            requireCorrectOutputSize(guessOutput);
        }

        void withNeuralNetwork()
        {
            setInputLayerSize(inputSize);
            setOutputLayerSize(outputSize);
            for (size_t i = 0; i < hiddenSize; i++)
            {
                addHiddenLayer(hiddenLayerSize);
            }
        }

        std::vector<double> andGuessOutput()
        {
            try
            {
                return guess(std::vector<double>(inputSize, 0));
            }
            catch (std::exception e)
            {
                CHECK(false);
            }
        }

        void requireCorrectOutputSize(std::vector<double> out)
        {
            CHECK(out.size() == outputSize);
        }
    };

    struct testSetLearningRate : public ZNN::NeuralNetwork<double>
    {
        const int inputSize = 1;
        const int outputSize = 2;
        const int hiddenSize = 7;
        const int hiddenLayerSize = 2;
        const int learningRate = 1234;

        testSetLearningRate()
        {
            withNeuralNetwork();
            andLearningRate();
            requireCorrectLearningRate();
        }

        void withNeuralNetwork()
        {
            setInputLayerSize(inputSize);
            setOutputLayerSize(outputSize);
            for (size_t i = 0; i < hiddenSize; i++)
            {
                addHiddenLayer(hiddenLayerSize);
            }
        }

        void andLearningRate()
        {
            setLearningRate(learningRate);
        }

        void requireCorrectLearningRate()
        {
            for (auto i : this->layers)
            {
                CHECK(i.learningRate == learningRate);
            }
            CHECK(outputLayer.learningRate == learningRate);
        }
    };

    struct testGetLastLayersSize : public ZNN::NeuralNetwork<double>
    {
        testGetLastLayersSize()
        {
            addHiddenLayer(10);
            CHECK(getLastLayersSize() == 10);
        }
    };

    struct testGetLastLayersSizeWithBias : public ZNN::NeuralNetwork<double>
    {
        testGetLastLayersSizeWithBias()
        {
            addHiddenLayer(10);
            CHECK(getLastLayersSizeWithBias() == 11);
        }
    };

    struct testCalculateTotalError : public ZNN::NeuralNetwork<double>
    {
        testCalculateTotalError()
        {
            outputLayer.errors = std::vector<double>{1, 1};
            CHECK(calculateTotalError() == 1);
        }
    };

    struct testReconstructOutputLayer : public ZNN::NeuralNetwork<double>
    {
        const int size = 10;
        const int lastLayerSize = 100;
        testReconstructOutputLayer()
        {
            withLayers();
            reconstructOutputLayer();
            requireCorrectOutputLayer();
        }

        void withLayers()
        {
            setOutputLayerSize(size);
            addHiddenLayer(lastLayerSize);
        }

        void requireCorrectOutputLayer()
        {
            CHECK(outputLayer.size == size);
            CHECK(outputLayer.inputSize == lastLayerSize + 1);
        }
    };

    struct testTrain : public ZNN::NeuralNetwork<double>
    {
        ZNN::NeuralNetwork<double> b;
        std::vector<std::vector<double>> input{{1, 0}, {0, 1}, {0, 0}, {1, 1}};
        std::vector<std::vector<double>> target{{0}, {0}, {1}, {0}};
        testTrain()
        {
            withNeuralNetwork();
            trainForNIterations(500);
            requireCorrectOutputs();
        }

        void withNeuralNetwork()
        {
            b.setInputLayerSize(2);
            b.setOutputLayerSize(1);
            b.setLearningRate(0.25);
        }

        void trainForNIterations(size_t iterations)
        {
            for (int i = 0; i < iterations; i++)
            {
                b.train(input[0], target[0]);
                b.train(input[1], target[1]);
                b.train(input[2], target[2]);
                b.train(input[3], target[3]);
            }
        }

        void requireCorrectOutputs()
        {
            CHECK(Approx(b.guess(input[0])[0] + 1).epsilon(0.15) == target[0][0] + 1);
            CHECK(Approx(b.guess(input[1])[0] + 1).epsilon(0.15) == target[1][0] + 1);
            CHECK(Approx(b.guess(input[2])[0] + 1).epsilon(0.15) == target[2][0] + 1);
            CHECK(Approx(b.guess(input[3])[0] + 1).epsilon(0.15) == target[3][0] + 1);
        }
    };

    testSetInputLayerSize();
    testSetOutputLayerSize();
    testAddHiddenLayer();
    testGuess();
    testSetLearningRate();
    testGetLastLayersSize();
    testGetLastLayersSizeWithBias();
    testCalculateTotalError();
    testReconstructOutputLayer();
    testTrain();
}

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
            Layer<double> layer(10, 100);
            std::vector<double> inputs(9, 100);
            CHECK(layer.calculate(inputs).size() == 10);
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

TEST_CASE("OutputLayer")
{
    struct testCalculateDerivatives : public ZNN::OutputLayer<double>
    {
        testCalculateDerivatives()
        {
            ZNN::OutputLayer<double> outLayer(10, 100);
            outLayer.errors = std::vector<double>(10, -10);
            outLayer.layerOutputValues = std::vector<double>(10, 10);
            CHECK(outLayer.calculateDerivatives().size() == 10);
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
            std::vector<double> deriv = outLayer.calculateDerivatives();
            outLayer.changeWeights(deriv);
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

    testCalculateDerivatives();
    testChangeWeights();
    testBiasNode();
}
