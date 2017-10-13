#ifndef ACTIVATION_H
#define ACTIVATION_H


#define CONST_PI 3.141592653589
#define CONST_E 2.718281828459

#include <stdexcept>
#include <cmath>

#define act_sigmoid 1
#define act_threshact 2
#define act_gauss 3
#define act_ramp 4
#define act_binarystep 5
#define act_identity 6

namespace ML {
	double activation (double input, unsigned int function_id) {
		if (function_id > 6 || function_id < 1) {throw std::invalid_argument ("Activation-function not known!");} //if the activation function doesnt exist
		
		int output = 0;
		
		if (function_id == act_identity) {output = input;} //the identity function
		
		if (function_id == act_threshact) { //the threshold-activation function
			if (input < 0) {
				output = 0;
			} else {
				output = 1;
			}
		}
		
		if (function_id == act_ramp) { //the ramp function
			output = 0;
			if (input > 0) {
				output = input;
			}
		}
		
		if (function_id == act_binarystep) { //everything below 0 is 0, else its a normal identity
			output = 0;
			if (input > 0) {
				output = 1;
			}				
		}
		
		if (function_id == act_gauss) {
			output = pow(CONST_E, - 1 / 2 * pow (input, 2));
		}
		
		if (function_id == act_sigmoid) {
			output = 1 / 1 + pow (CONST_E, - input); 
		}

		return output;

	}

}

#endif
