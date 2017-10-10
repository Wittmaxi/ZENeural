
#include <iostream>
#include <vector>
#include "neuralNet.h"

using namespace ML;

int main () {
  Neural myNN(true);
  myNN.createInputLayer(1); 
  myNN.addHiddenLayer(10);
  myNN.addHiddenLayer(2, act_ramp);
  myNN.addHiddenLayer(2);
  myNN.createOutputLayer(1, act_threshact);

  std::cout << "creation finished" << std::endl;

  std::vector < double > input;
  input.push_back (2.0);
  std::cout << "INPUT" << input[0] << std::endl;
  std::vector < double > output = myNN.guess(input);

  for (auto i : output) {
  	std::cout << i << std::endl; 
  }
}
