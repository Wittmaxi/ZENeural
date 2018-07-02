#include "header/normalisation.h"

namespace ZNN
{
Normalization Fermi()
{
    std::function<double(double)> normalization = [=](double input) -> double {
        return (1 / (1 + (std::exp(-input))));
    };
    std::function<double(double)> derivative = [=](double input) -> double {
        return normalization(input) * (1 - normalization(input));
    };
    return Normalization(normalization, derivative);
}
} // namespace ZNN