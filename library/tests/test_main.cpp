#define CATCH_CONFIG_MAIN
#include "../header/NeuralNetwork.hpp"
#include "catch.hpp"

TEST_CASE("Neural Network")
{
    struct testSetInputLayerSize : public ZNN::NeuralNetwork<double>
    {
        testSetInputLayerSize()
        {
            setInputLayerSize(1);
            REQUIRE(this->inputLayerSize == 1);
        }
    };

    struct testSetOutputLayerSize : public ZNN::NeuralNetwork<double>
    {
        testSetOutputLayerSize()
        {
            setOutputLayerSize(1);
            REQUIRE(this->outputLayerSize == 1);
        }
    };

    struct testAddHiddenLayer : public ZNN::NeuralNetwork<double>
    {
        const int numberHiddenLayers = 4;
        const int hiddenLayerSize = 3;
        testAddHiddenLayer()
        {
            withHiddenLayers();
            requireHiddenLayerCorrectSize();
        }

        void withHiddenLayers()
        {
            for (size_t i = 0; i < numberHiddenLayers; i++)
            {
                addHiddenLayer(hiddenLayerSize);
            }
        }

        void requireHiddenLayerCorrectSize()
        {
            REQUIRE(this->layers.size() == numberHiddenLayers);
            for (auto i : this->layers)
            {
                REQUIRE(i.size == hiddenLayerSize);
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
                REQUIRE(false);
            }
        }

        void requireCorrectOutputSize(std::vector<double> out)
        {
            REQUIRE(out.size() == outputSize);
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
                REQUIRE(i.learningRate == learningRate);
            }
            REQUIRE(outputLayer.learningRate == learningRate);
        }
    };

    testSetInputLayerSize();
    testSetOutputLayerSize();
    testAddHiddenLayer();
    testGuess();
    testSetLearningRate();
}