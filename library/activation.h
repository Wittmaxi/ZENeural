#pragma once
#include <cmath>

//Defines some standard Activation functions. 

constexpr double ACT_SIGMOID (double x) {
	return (1 / (1 + exp(-1 * x)));
};