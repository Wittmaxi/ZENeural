#pragma once
#include <math.h>
#include <functional>

namespace ZNN
{
class Normalization
{
  public:
	Normalization(){};
	Normalization(std::function<double(double)> norm, std::function<double(double)> der)
	{
		normalization = norm;
		derivative = der;
	}
	std::function<double(double)> normalization;
	std::function<double(double)> derivative;
};

Normalization Fermi();
} // namespace ZNN