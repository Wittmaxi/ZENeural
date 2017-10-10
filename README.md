THIS LIBRARY IS CURRENTLY WORK IN PROGRESS! 
NOT EVERYTHING DESCRIBED IN THE README IS GUARANTEED TO WORK!

ALSO, FUNCTION - NAMES MIGHT CHANGE! 
I GIVE NO GUARANTEE, THAT LATER VERSIONS ARE BACKWARDS-COMPATIBLE!

# Creator of ZENeural
Made by Maximilian W. 
Contact me at wittmaxi@outlook.de if you have suggestions

# Installation
This Library doesnt need installation. Simply download the files and include them in C++ with 
```
#include "pathToFile.h"
```

# Hardware 
This Library works best with NVidia Graphics cards, as it uses CUDA-Optimization.

However, a version for Vulcan might get created.

# Usage 
The entire Library uses the Namespace "ML"

## Neural Network

The class for the Neural Network is called "Neural". It is included in "neuralNet.h".
Instantiate it like so:

``` 
bool debugMode = true;  //if you want to get informations about the learning process. 
//Set to false in production
ML::Neural myNN (debugMode);
```

You need to give it an Input-Layer, hidden Layers and an Output-Layer. 
You need One Input layer, Atleast one hidden Layer, and an Output-Layer.

```
myNN.createInputLayer (inputSize = int);
myNN.addHiddenLayer (layerSize = int);
myNN.createOutputLayer (outputSize = int);
```

Now you can make the Network guess something. As input, it takes a std::vector of doubles that must be of the same size as the input layer.

As output you will also get a std::vector of doubles. 

```
std::vector <double> input (2.0, 7.0);
std::vector <double> output = myNN.guess (input);
```

You can also train the Network in order for it to guess more accurately.
The train function needs an input like guess does. Additionally it needs an array of doubles that represents the Expected values. This array needs to be as big as the output Layer.

```
std::vector <double> input (2.0, 7.0);
std::vector <double> expected (1.0);
myNN.train (input, expected);
```

### dependencies
This class needs the following files in the same directory:
```
node.h
layer.h
```

### Real coding example

This example might be a little overkill (a simple modulo would work better) but it shows the Neural 
Network in action quite well.

```
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
