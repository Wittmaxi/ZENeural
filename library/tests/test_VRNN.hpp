/*
2018 Maximilian Wittmer
wittmaxi@linux.pizza

https://github.com/Wittmaxi/ZENeural/blob/master/LICENSE

*/

TEST_CASE("Vanilla Recurrent Neural Network")
{
    struct testAddHiddenLayer : public ZNN::VRNN <double>{
        testAddHiddenLayer () {
            setInputLayerSize (10);
            addHiddenLayer(123);
            CHECK (layers[0].neurons[0].weights.size() == 10 + 123 + 1);
        }
    };

    testAddHiddenLayer();
}