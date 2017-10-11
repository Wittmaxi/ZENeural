#include <iostream>
#include <vector>
#include "integral.h"
#include <cmath>

#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */


using namespace ML;

int main () {
  Neural myNN(false);

  myNN.createInputLayer(1); 
  myNN.addHiddenLayer(10);
  myNN.createOutputLayer(1);

  myNN.setLearningRate(0.00000000000000000000000001);

  std::vector < double > input;
  std::vector < double > output;
  std::vector < double > expected;

  input.push_back (0.0);
  expected.push_back(0.0);


  expected[0] = double(22);

  for (int i = 0; i < 10000; i++) {

    myNN.train (input, expected);
  }

  for (int i = 0; i < 10; i++) {
    std::cin >> input [0];

    output = myNN.guess (input);

    for (auto i : output)  {
      std::cout << i << std::endl;
    }
  }
}
