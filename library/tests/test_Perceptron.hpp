/*
2018 Maximilian Wittmer
wittmaxi@linux.pizza

https://github.com/Wittmaxi/ZENeural/blob/master/LICENSE

*/

TEST_CASE("Perceptron")
{
    struct test_constructor : ZNN::Perceptron<double>
    {
        test_constructor() : Perceptron(10)
        {
            CHECK(neuron.weights.size() == 11);
        }
    };

    struct test_setNormalization : ZNN::Perceptron<double>
    {
        test_setNormalization() : Perceptron (10)
        {
            setNormalization (ZNN::Fermi<double>());
            CHECK (normalization.normalization(0) == 0.5);
        }
    };

    struct test_setLearningRate : ZNN::Perceptron<double>
    {
        test_setLearningRate() : Perceptron (10)
        {
            setLearningRate (1337);
            CHECK (learningRate == 1337);
        }
    };

    struct test_guess : ZNN::Perceptron<double>
    {
        test_guess () : Perceptron (3) {
            CHECK (guess ({1, 1, 1}) > 0.0f);
        }
    };

    struct test_calculateError : ZNN::Perceptron<double>
    {
        test_calculateError () : Perceptron (3) {
            CHECK (calculateError (1, 1) == 0);
            CHECK (calculateError (1, 0) == -1);
        }
    };

    struct test_train : ZNN::Perceptron<double>
    {
        test_train () : Perceptron (2) {
            setLearningRate(0.01);
            for (int i = 0; i < 10000; i++)
                train ({1, static_cast<float>(i % 3)}, 0.23);
            CHECK (Approx(guess ({1, 2})).epsilon(0.15) == 0.23);
        }
    };

    test_constructor();
    test_setNormalization();
    test_guess();
    test_calculateError();
    test_train();
    test_setLearningRate();
}