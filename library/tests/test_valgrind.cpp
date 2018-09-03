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

int main()
{
    testTrainWithMultipleLayers();
}