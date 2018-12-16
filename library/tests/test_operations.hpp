/*
2018 Maximilian Wittmer
wittmaxi@linux.pizza

https://github.com/Wittmaxi/ZENeural/blob/master/LICENSE

*/

TEST_CASE("operations.hpp")
{
    SECTION("addition")
    {
        std::vector<double> v(11, 1);
        std::vector<double> w(11, 1);
        REQUIRE(v.size() == 11);
        REQUIRE(w.size() == 11);
        REQUIRE(ZNN::UTIL::addVectors(w, v).size() == 11);
    }
}
