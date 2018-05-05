#pragma once
#include <math.h>

namespace ZNN
{
inline double fermi(double x)
{
	return (1 / (1 + (exp(-x))));
}

inline double ident(double x)
{
	return x;
}

inline double binaryStep(double x)
{
	if (x > 0)
	{
		return 1;
	}
	return 0;
}
inline double step(double x)
{
	return floor(x);
}
}