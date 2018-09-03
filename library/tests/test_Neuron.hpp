/*
2018 Maximilian Wittmer
wittmaxi@linux.pizza

https://github.com/Wittmaxi/ZENeural/blob/master/LICENSE

*/

TEST_CASE("Neuron")
{
    struct testConstructor
    {
        testConstructor()
        {
            ZNN::Neuron<double> neuron(1000);
            CHECK(neuron.weights.size() == 1000);
        }
    };

    struct testWeightedSum
    {
        testWeightedSum()
        {
            std::vector<double> fakeInputs(2, 10);
            ZNN::Neuron<double> neuron(2);

            neuron.weights = std::vector<double>(2, 0.1);
            CHECK(neuron.weightedSum(fakeInputs) == 2);
        }
    };

    testConstructor();
    testWeightedSum();
}