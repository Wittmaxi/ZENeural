#include "../header/NeuralNetwork.hpp"

struct testTrainWithMultipleLayers : public ZNN::NeuralNetwork<double>
{
    ZNN::NeuralNetwork<double> b;
    std::vector<std::vector<double>> input{{1, 0}, {0, 1}, {0, 0}, {1, 1}};
    std::vector<std::vector<double>> target{{1}, {1}, {0}, {0}};
    testTrainWithMultipleLayers()
    {
        withNeuralNetwork();
        trainForNIterations(1);
    }

    void withNeuralNetwork()
    {
        b.setInputLayerSize(2);
        b.addHiddenLayer(50);
        b.setOutputLayerSize(1);
        b.setLearningRate(0.7);
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
};

void testVRNN()
{
    ZNN::VRNN<double> textCreator;
    textCreator.setInputLayerSize(4);
    textCreator.addHiddenLayer(50);
    textCreator.addHiddenLayer(50);
    textCreator.setOutputLayerSize(4);
    textCreator.setNormalization(ZNN::Fermi<double>());
    textCreator.setLearningRate(0.1);
    std::vector<std::vector<double>> dictionary {{1, 0, 0, 0},
                                                 {0, 1, 0, 0},
                                                 {0, 0, 1, 0},
                                                 {0, 0, 0, 1},
                                                 {0, 0, 0, 0}};
    for (int i = 0; i < 1000000; i++)
    {
        textCreator.train(dictionary[0], dictionary[1]);
        textCreator.train(dictionary[4], dictionary[2]);
        textCreator.train(dictionary[4], dictionary[3]);
        textCreator.train(dictionary[4], dictionary[3]);
        textCreator.train(dictionary[4], dictionary[4]);
        textCreator.clearStates();
    }
    std::cout << textCreator.guess(dictionary[0]);
    std::cout << textCreator.guess(dictionary[4]);
    std::cout << textCreator.guess(dictionary[4]);
    std::cout << textCreator.guess(dictionary[4]);
    std::cout << textCreator.guess(dictionary[4]);
}

int main()
{
    testTrainWithMultipleLayers();
    testVRNN();
}