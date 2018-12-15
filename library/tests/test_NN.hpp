/*
2018 Maximilian Wittmer
wittmaxi@linux.pizza

https://github.com/Wittmaxi/ZENeural/blob/master/LICENSE

*/

#include <fenv.h>

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
            setInputLayerSize(1);
            setOutputLayerSize(1);
            CHECK(this->outputLayerSize == 1);
        }
    };

    struct testAddHiddenLayer : public ZNN::NeuralNetwork<double>
    {
        const unsigned int numberHiddenLayers = 4;
        const unsigned int hiddenLayerSize = 3;
        testAddHiddenLayer()
        {
            withHiddenLayers();
            requireCorrectNumberHiddenLayers();
            requireHiddenLayersCorrectNeuronSize();
        }

        void withHiddenLayers()
        {
            setInputLayerSize(1);
            for (unsigned int i = 0; i < numberHiddenLayers; i++)
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

    struct testGoodNumberNeuronsWeights : public ZNN::NeuralNetwork<double>
    {
        testGoodNumberNeuronsWeights()
        {
            withHiddenLayers();
            requireCorrectNumberNeuronsWeights();
        }

        void withHiddenLayers()
        {
            setInputLayerSize(1);
            addHiddenLayer(10);
            addHiddenLayer(3);
            addHiddenLayer(5);
        }

        void requireCorrectNumberNeuronsWeights()
        {
            CHECK(this->layers[0].neurons[0].weights.size() == 1 + 1);
            CHECK(this->layers[1].neurons[0].weights.size() == 10 + 1);
            CHECK(this->layers[2].neurons[0].weights.size() == 3 + 1);
        }
    };

    struct testGuess : public ZNN::NeuralNetwork<double>
    {
        const unsigned int inputSize = 1;
        const unsigned int outputSize = 2;
        const unsigned int hiddenSize = 0;
        const unsigned int hiddenLayerSize = 2;

        testGuess()
        {
            withNeuralNetwork();
            std::vector<double> guessOutput = andGuessOutput();
            requireCorrectOutputSize(guessOutput);
        }

        void withNeuralNetwork()
        {
            setInputLayerSize(inputSize);
            for (size_t i = 0; i < hiddenSize; i++)
            {
                addHiddenLayer(hiddenLayerSize);
            }
            setOutputLayerSize(outputSize);
        }

        std::vector<double> andGuessOutput()
        {
            try
            {
                return guess(std::vector<double>(inputSize, 0));
            }
            catch (const std::exception &e)
            {
                CHECK(false);
            }
            return std::vector<double>(0, 0);
        }

        void requireCorrectOutputSize(std::vector<double> out)
        {
            CHECK(out.size() == outputSize);
        }
    };

    struct testSetLearningRate : public ZNN::NeuralNetwork<double>
    {
        const unsigned int inputSize = 1;
        const unsigned int outputSize = 2;
        const unsigned int hiddenSize = 7;
        const unsigned int hiddenLayerSize = 2;
        const unsigned int learningRate = 1234;

        testSetLearningRate()
        {
            withNeuralNetwork();
            andLearningRate();
            requireCorrectLearningRate();
        }

        void withNeuralNetwork()
        {
            setInputLayerSize(inputSize);
            for (size_t i = 0; i < hiddenSize; i++)
            {
                addHiddenLayer(hiddenLayerSize);
            }
            setOutputLayerSize(outputSize);
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
            setInputLayerSize(1);
            addHiddenLayer(10);
            CHECK(getLastLayersSize() == 10);
        }
    };

    struct testGetLastLayersSizeWithBias : public ZNN::NeuralNetwork<double>
    {
        testGetLastLayersSizeWithBias()
        {
            setInputLayerSize(1);
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

    struct testTrain : public ZNN::NeuralNetwork<double>
    {
        ZNN::NeuralNetwork<double> b;
        std::vector<std::vector<double>> input{{1, 0}, {0, 1}, {0, 0}, {1, 1}};
        std::vector<std::vector<double>> target{{0}, {0}, {1}, {0}};
        testTrain()
        {
            withNeuralNetwork();
            trainForNIterations(5000);
            requireCorrectOutputs();
        }

        void withNeuralNetwork()
        {
            b.setInputLayerSize(2);
            b.addHiddenLayer(2);
            b.setOutputLayerSize(1);
            b.setLearningRate(0.25);
            b.setNormalization(ZNN::Fermi<double>());
        }

        void trainForNIterations(size_t iterations)
        {
            for (size_t i = 0; i < iterations; i++)
            {
                b.train(input[0], target[0]);
                b.train(input[1], target[1]);
                b.train(input[2], target[2]);
                b.train(input[3], target[3]);
            }
        }

        void requireCorrectOutputs()
        {

            ZNN::NeuralNetwork<double> c;
            c.loadFromString (b.getAsString());
            c.setNormalization(ZNN::Fermi<double>());
            
            //artificially add one so the epsilon works better
            CHECK(Approx(b.guess(input[0])[0] + 1).epsilon(0.15) == target[0][0] + 1);
            CHECK(Approx(b.guess(input[1])[0] + 1).epsilon(0.15) == target[1][0] + 1);
            CHECK(Approx(b.guess(input[2])[0] + 1).epsilon(0.15) == target[2][0] + 1);
            CHECK(Approx(b.guess(input[3])[0] + 1).epsilon(0.15) == target[3][0] + 1);
            
            CHECK (c.getAsString() == b.getAsString());
            CHECK(Approx(c.guess(input[0])[0] + 1).epsilon(0.15) == target[0][0] + 1);
            CHECK(Approx(c.guess(input[1])[0] + 1).epsilon(0.15) == target[1][0] + 1);
            CHECK(Approx(c.guess(input[2])[0] + 1).epsilon(0.15) == target[2][0] + 1);
            CHECK(Approx(c.guess(input[3])[0] + 1).epsilon(0.15) == target[3][0] + 1);
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
    testTrain();
    testGoodNumberNeuronsWeights();
}
