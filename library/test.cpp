
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
  myNN.addHiddenLayer(30, act_sigmoid);
  myNN.createOutputLayer(2, act_ramp);

  myNN.setLearningRate(1);

  std::cout << "creation finished" << std::endl;

  std::vector < double > input;
  input.push_back (2.0);
  std::vector < double > output;
  std::vector < double > expected;
  expected.push_back(0.0);
  expected.push_back(0.0);
  for (int i = 0; i < 100000; i++) { //training over 200 iterations
    srand (i * 10);

    input [0] = rand() % 10000 + 1;

    std::cout << int (floor (input [0])) << std::endl << int(floor(input [0])) % 2 << std::endl << std::endl; 


    if (int(floor(input [0])) % 2 == 0) {
      expected[0] = 1;
      expected[1] = 0;
    } else {
      expected[0] = 0;
      expected[1] = 1;
    }    
    myNN.train (input, expected);
  }


  for (int i = 0; i < 10; i++) {
    std::cin >> input [0];
    output.clear();
    output = myNN.guess(input);
    for (double i : output) {
      std::cout << activation (i, act_threshact) << std::endl; 
    }
  }
}
