#pragma once
#include <cmath>
#include <functional>

//Defines some standard Activation functions. 

double ACT_SIGMOID (double x) {
	return (1 / (1 + exp(-1 * x)));
};