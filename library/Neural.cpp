#include "Neural.h"
#include <iostream>

namespace ML {
void CNeural::addLayer (unsigned int layerSize) {
	if (Layers.size() == 0) {
		Layers.push_back (new CLayer (layerSize, 0));
	} else {
		Layers.push_back (new CLayer (layerSize, Layers[Layers.size()-1]->size()));
	}
}  

std::vector<double> CNeural::guess (const std::vector <double>& input) {
	Layers[0]->setSums (input);
	for (int i = 1; i < Layers.size(); i++) { //w-Sum for all except the first layer, since it already contains the values
		Layers[i]->calcWSums (Layers[i-1]->getSums()); //calculate the wheighted sum with the values of the last Layer
	}
	return Layers[Layers.size()-1]->getSums();
}

std::vector<double> CNeural::adjust (const std::vector<double>& input,const std::vector<double>& correct) {
	std::vector<double> guesses = guess (input);
	std::vector<double> errors;
	std::cout << "guessed" << std::endl;
	//calculate the errors
	for (int i = 0; i < guesses.size(); i ++) {
		errors.push_back (correct[i] - guesses[i]);
	}
	int lastLayer = Layers.size()-1;
	std::cout << "errors fixed" << std::endl;
	Layers[lastLayer]->setErrors (errors);
	std::cout << "set errors" << std::endl;
 	Layers[lastLayer]->backPropagate(Layers);
}
}