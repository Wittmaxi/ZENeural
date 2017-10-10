
#include <iostream>
#include <vector>
#include "neuralNet.h"

using namespace ML;

int main () {
  Neural myNN(true);
  myNN.createInputLayer(1); 
  myNN.addHiddenLayer(10);
  myNN.addHiddenLayer(12);
  myNN.addHiddenLayer(12);
  myNN.createOutputLayer(1);

  std::vector < float > input (2.0);
  std::vector < float > output = myNN.guess(input);

  for (auto i : output) {
  	std::cout << i << std::endl; 
  }
}
