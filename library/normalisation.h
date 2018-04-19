#pragma once
#include <math.h>

namespace ZNN {
	double fermi (double x) {
		if (x == 0) {
			return 0.5;
		}
		return (1 / (exp (-x)));
	}
}