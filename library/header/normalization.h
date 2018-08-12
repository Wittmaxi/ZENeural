#pragma once
#include <math.h>
#include <functional>

namespace ZNN
{
template <class floatType>
class Normalization
{
  public:
	Normalization(){};
	Normalization(std::function<floatType(floatType)> norm, std::function<floatType(floatType)> der)
	{
		normalization = norm;
		derivative = der;
	}
	std::function<floatType(floatType)> normalization;
	std::function<floatType(floatType)> derivative;
};

template <class floatType>
Normalization<floatType> Fermi()
{
	std::function<floatType(floatType)> normalization = [=](floatType input) -> floatType {
		return (1 / (1 + (std::exp(-input))));
	};
	std::function<floatType(floatType)> derivative = [=](floatType input) -> floatType {
		std::cout << "hi" << input << " " << input * (1 - input) << "\n";
		return input * (1 - input);
	};
	return Normalization<floatType>(normalization, derivative);
}

template <class floatType>
Normalization<floatType> Identity()
{
	std::function<floatType(floatType)> normalization = [=](floatType input) -> floatType {
		return input;
	};
	std::function<floatType(floatType)> derivative = [=](floatType input) -> floatType {
		return 1;
	};
	return Normalization<floatType>(normalization, derivative);
}
} // namespace ZNN