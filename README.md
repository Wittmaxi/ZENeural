THIS LIBRARY IS CURRENTLY WORK IN PROGRESS! 
NOT EVERYTHING DESCRIBED IN THE README IS GUARANTEED TO WORK!

ALSO, FUNCTION NAMES ARE SUBJECT TO CHANGE! 
I GIVE NO GUARANTEE, THAT LATER VERSIONS ARE BACKWARDS-COMPATIBLE!

# Creator of ZENeural
Made by Maximilian W. 
Contact me at wittmaxi@outlook.de if you have suggestions

# Installation
This Library doesnt need installation. Simply download the files and include them in C++ with 
```c++
#include "pathToFile.h"
```
If you want to add everything, use 
```c++
#include "pathtoIntegral.h/integral.h"
```
It includes the integral package.

Also, you need to add the compilation argument lpthread to your compiler like so:

```
g++ main.cpp -lpthreads -o out
```


# Hardware 
This Library works best with NVidia Graphics cards, as it uses CUDA-Optimization. A Vulcan version may be released in the future.

# Usage 
The entire Library uses the Namespace "ML".

## Neural Network

The class for the Neural Network is called "Neural". It is included in "neuralNet.h".
Instantiate it like so:

``` c++
bool debugMode = true;  //if you want to get informations about the learning process. 
//Set to false in production
ML::Neural myNN (debugMode);
```

You need to give it an Input-Layer, hidden Layers and an Output-Layer. 
You need One Input layer, Atleast one hidden Layer, and an Output-Layer.

```c++
myNN.createInputLayer (inputSize = int, activation function);
myNN.addHiddenLayer (layerSize = int, activation function);
myNN.createOutputLayer (outputSize = int, activation function);
```
Note that, the activation is optional.
Here are the different activation functions you can use: 
```c++
act_sigmoid
act_threshact
act_gauss
act_ramp
act_binarystep
act_identity
```


Now you can make the Network guess something. As input, it takes a std::vector of doubles that must be of the same size as the input layer.

As output you will also get a std::vector of doubles. 

```c++
std::vector <double> input (2.0, 7.0);
std::vector <double> output = myNN.guess (input);
```

You can also train the Network in order for it to guess more accurately.
The train function needs an input like guess does. Additionally it needs an array of doubles that represents the Expected values. This array needs to be as big as the output Layer.

```c++
std::vector <double> input (2.0, 7.0);
std::vector <double> expected (1.0);
myNN.train (input, expected);
```

### dependencies
This class needs the following files in the same directory:
```c++
node.h
activation.h
```

### Real coding example

This example might be a little overkill (a simple modulo would work better) but it shows the Neural 
Network in action quite well.

```c++
//programm that decides wether a number is divisible by 2 without mathematical operators

#include <vector>
#include "neuralNet.h"

using namespace ML;

int main () {
  Neural* myNN = new Neural (true);
  myNN.createInputLayer(1); 
  myNN.addHiddenLayer(10);
  myNN.addOutputLayer(1, act_threshold);
}


```

## Pure activation

You might want to calculate the activation of a number.

Therefore use ```activation ()```-function.
it takes a double input and an activation-function-id and returns a double.

To use it, include "activation.h"

possible activation-ids: 
```
act_sigmoid
act_threshact
act_gauss
act_ramp
act_binarystep
act_identity
```

### Example
```c++
double activated = activation (7.5, act_sigmoid);
```
