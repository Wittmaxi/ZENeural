#include "../header/NeuralNetwork.hpp"
#include "../header/VanillaRecurrentNetwork.hpp"

struct testTrainWithMultipleLayers : public ZNN::FeedForwardNeuralNetwork<double>
{
    ZNN::FeedForwardNeuralNetwork<double> b;
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

std::ostream& operator<< (std::ostream& os, std::vector<double> vec) {
    for (const auto &i: vec)
        os << i << ",";
    os << "\n";
    return os;
}

void testVRNN()
{
    ZNN::VanillaRecurrentNeuralNetwork<double> textCreator;
    textCreator.setInputLayerSize(4);
    textCreator.addHiddenLayer(10);
    textCreator.addHiddenLayer(10);
    textCreator.setOutputLayerSize(4);
    textCreator.setNormalization(ZNN::Fermi<double>());
    textCreator.setLearningRate(0.02);
    std::vector<std::vector<double>> dictionary {{1, 0, 0, 0},
                                                 {0, 1, 0, 0},
                                                 {0, 0, 1, 0},
                                                 {0, 0, 0, 1},
                                                 {0, 0, 0, 0}};
    double sumOfErr = 0;
    for (int i = 0; i < 100000; i++)
    {
        sumOfErr += textCreator.train(dictionary[0], dictionary[0]);
        sumOfErr += textCreator.train(dictionary[4], dictionary[1]);
        sumOfErr += textCreator.train(dictionary[4], dictionary[2]);
        sumOfErr += textCreator.train(dictionary[4], dictionary[2]);
        sumOfErr += textCreator.train(dictionary[4], dictionary[3]);
        textCreator.clearStates();
        if (i % 100 == 0)
            std::cout << "iteration: " << i << " AVG ERROR: " << sumOfErr / i << "\n";
    }
    std::cout << std::fixed;
    std::cout << textCreator.guess(dictionary[0]);
    std::cout << textCreator.guess(dictionary[4]);
    std::cout << textCreator.guess(dictionary[4]);
    std::cout << textCreator.guess(dictionary[4]);
    std::cout << textCreator.guess(dictionary[4]);
}

int main()
{
    ZNN::UTIL::ts.resize(5);
    testTrainWithMultipleLayers();
    testVRNN();
}