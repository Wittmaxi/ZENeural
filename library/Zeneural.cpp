#include "Zeneural.h"
#include <iostream>

namespace ML {
NeuralNetwork::NeuralNetwork (bool debug) {
	d.write = debug;
}

void NeuralNetwork::addLayer (size_t layerSize, std::function <double(double)> activation) {
	d.info ("Adding layer of size " + std::to_string (layerSize));
	if (m_layers.size() == 0) {
		m_layers.push_back (CLayer (layerSize, 0));
		m_layers.at(0).m_normalisation = activation;
	} else {
		m_layers.push_back (CLayer (layerSize, m_layers.at(m_layers.size()-1).m_neurons.size()));
		m_layers.at(m_layers.size()-1).m_normalisation = activation;
	}
}

std::vector<double> NeuralNetwork::guess (std::vector<double>& input) {
	m_layers.at(0).m_output = input;
	d.out ("NeuralNetwork::Guess (std::vector<double>& input) "); 
	d.out (":::");
	m_forward ();
	d.out (":::");
	d.out ("Finished guessing");
	return m_layers.at(m_layers.size()-1).m_output;
}

double NeuralNetwork::train (std::vector<double>& input, std::vector<double>& expected) {
	m_layers.at (0).m_output = input;
	d.out ("NeuralNetwork::train");
	d.out (":::");
	for (size_t i = 0; i< m_trainingEpochs; i++) {
		m_forward ();
		m_backward (calculateErrors(expected, m_layers.at(m_layers.size()-1).m_output));
	}
	d.out (":::");
	d.out ("Finished training");
}

void NeuralNetwork::m_forward () {
	for (size_t i = 1; i < m_layers.size(); ++i) {
		d.out ("NeuralNetwork::Guess => Looping through layers - Iteration: " + std::to_string(i));
		m_layers[i].m_forward (m_layers.at(i-1).m_output);
	}	
}

void NeuralNetwork::m_backward (std::vector<double>& expected) {
	d.out ("backwarding last Layer");
	m_layers.rbegin()->m_backward (expected); 
	d.out ("finished");
	for (size_t i = m_layers.size()-1; i > 1; i--) {
		//m_layers.at(i-1).m_backward(m_layers.at(i).m_expected);
	}
}

std::vector<double>& NeuralNetwork::calculateErrors (std::vector<double>& expected, std::vector<double>& out) {
	std::vector<double> *retVec = new std::vector<double>;
	for (size_t i = 0; i < expected.size(); i++) {
		d.info ("7891");
		retVec->push_back (-(expected[i] - out[i]));
	}
	return *retVec;
}
}