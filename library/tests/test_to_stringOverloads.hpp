#include "../header/util/to_stringOverloads.hpp"

TEST_CASE("To string overloads")
{
    struct test_NeuralNetwork_RawConversion
    {
        ZNN::NeuralNetwork<double> a;
        ZNN::NeuralNetwork<double> b;
        std::string a_string;
        std::string b_string;
        test_NeuralNetwork_RawConversion()
        {
            withNetworks();
            getStrings();
            requireStringsNotEqual();
        }

        void withNetworks()
        {
            a.setInputLayerSize(1);
            a.addHiddenLayer(10);
            a.setOutputLayerSize(10);
            b.setInputLayerSize(4);
            b.addHiddenLayer(11);
            b.setOutputLayerSize(11);
        }

        void getStrings()
        {
            a_string = std::to_string(a);
            b_string = std::to_string(b);
        }

        void requireStringsNotEqual()
        {
            CHECK_FALSE(a_string == b_string);
        }
    };

    test_NeuralNetwork_RawConversion{};
}