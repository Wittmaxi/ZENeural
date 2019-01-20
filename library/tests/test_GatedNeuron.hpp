/*
2018 Maximilian Wittmer
wittmaxi@linux.pizza

https://github.com/Wittmaxi/ZENeural/blob/master/LICENSE

*/

TEST_CASE("GatedNeuron.hpp")
{
    SECTION ("Gate") {
        SECTION ("constructor") {
            ZNN::Gate<double> g(100);
            REQUIRE (g.layer.inputSize == 101);
            REQUIRE (g.layer.normalization.normalization(1) == ZNN::Fermi<double>().normalization(1));
        }
        SECTION ("guess") {
            ZNN::Gate<double> g(10);
            std::vector<double> w(10, 1);
            std::vector<double> v(10, 1);
            REQUIRE (g.calculateActivations(v, w).size() == 10);
        }
    } 
}

