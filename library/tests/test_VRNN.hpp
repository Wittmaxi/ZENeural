/*
2018 Maximilian Wittmer
wittmaxi@linux.pizza

https://github.com/Wittmaxi/ZENeural/blob/master/LICENSE

*/
#include <iostream>

TEST_CASE("Vanilla Recurrent Neural Network")
{
    struct testAddHiddenLayer : public ZNN::VRNN<double>
    {
        testAddHiddenLayer()
        {
            setInputLayerSize(10);
            addHiddenLayer(123);
            CHECK(layers[0].neurons[0].weights.size() == 10 + 123 + 1);
        }
    };

    struct testClearStates : public ZNN::VRNN<double>
    {
        testClearStates()
        {
            setInputLayerSize(1);
            addHiddenLayer(3);
            layers[0].layerOutputValues = std::vector<double>{1, 2, 3};
            clearStates();
            CHECK(layers[0].layerOutputValues == std::vector<double>{0, 0, 0});
        }
    };

    struct testGuess : public ZNN::VRNN<double>
    {
        testGuess()
        {
            setInputLayerSize(1);
            addHiddenLayer(3);
            setOutputLayerSize(1);
            CHECK(guess({1}).size() == 1);
        }
    };

    // testAddHiddenLayer();
    //´ testClearStates();
    testGuess();
}
