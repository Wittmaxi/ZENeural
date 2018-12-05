/*
2018 Maximilian Wittmer
wittmaxi@linux.pizza

https://github.com/Wittmaxi/ZENeural/blob/master/LICENSE

*/

void testConstructor();
void testCalculate();
void testWeightedSum();
void testBiasNode();
void testGetAsString();
void testLoadFromString();

void testConstructor()
{
    ZNN::Layer<double> layer(10, 100);
    CHECK(layer.size == 10);
    CHECK(layer.inputSize == 100);
    CHECK(layer.neurons.size() == 10);
    CHECK(layer.neurons[0].weights.size() == 100);
}

void testCalculate()
{
    ZNN::Layer<double> layer(1000, 100000);
    layer.normalization = ZNN::Fermi<double>();
    std::vector<double> inputs(9000000, 100);
    std::vector<double> outputs = layer.calculate(inputs);
    CHECK(outputs.size() == 1000);
    CHECK(outputs[0] <= 1);
}

void testGetAsString()
{
    ZNN::Layer<double> layer(10, 100);
    CHECK(layer.getAsString().size() > 100);
}

void testLoadFromString()
{
    ZNN::Layer<double> layer(100, 10);
    ZNN::Layer<double> layer2(0, 0);
    layer2.loadFromString(layer.getAsString());
    CHECK(layer2.neurons.size() == 100);
    CHECK(layer2.neurons[0].weights.size() == 10);
}

void testWeightedSum()
{
    ZNN::Layer<double> layer(10, 100);
    std::vector<double> inputs(9, 100);
    CHECK(layer.weightedSum(inputs).size() == 10);
}

void testBiasNode()
{
    ZNN::Layer<double> layer(10, 11);
    std::vector<double> inputs(10, 0);
    CHECK(layer.calculate(inputs)[0] != 0.5);
}

TEST_CASE("Layer")
{
    testConstructor();
    testCalculate();
    testWeightedSum();
    testBiasNode();
    testLoadFromString();
}
