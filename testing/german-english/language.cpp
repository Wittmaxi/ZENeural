#include <iostream>
#include <vector> 
#include <string>
#include <fstream>
#include <stdlib.h>
#include <time.h>

#include "../../library/integral.h"

using namespace ML;

std::vector < std::string > english;
std::vector < std::string > german;

std::vector < double > inputVals{
0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0
};

std::fstream fileReader;

Neural myNN(true);

void loadFiles();
void generateCharsForString(std::string input);

int main () {


	myNN.createInputLayer(13);
	myNN.addHiddenLayer(13 * 2);
	myNN.addHiddenLayer(13 * 2);
	myNN.createOutputLayer(2, act_threshact); //the output is to be interpreted like so: 
										   // |LANG: | GERMAN |  ENGLISH  |
										   // |------+--------+-----------|
										   // |OUT1: |    1   |     0     |
			                               // |OUT2: |    0   |     1     |
	myNN.setLearningRate(0.25);

	loadFiles();

	srand (time (NULL));

	int germanSize = german.size();
	int englishSize = english.size();

	std::vector < double > expected_german;
	std::vector < double > expected_english;

	expected_english.push_back (0.0);
	expected_english.push_back (1.0);
	expected_german.push_back (1.0);
	expected_german.push_back (0.0);

	for (int i = 0; i < 10000; i++) { //the learning iterations
		int lang = rand () % 2+1;
		if (lang == 1) { //use english
			generateCharsForString(english[rand () % englishSize]);
			myNN.train (inputVals, expected_english);
		}
		if (lang == 2) { //use german
			generateCharsForString(german[rand () % germanSize]);
			myNN.train (inputVals, expected_german);
		}
	}

}

void loadFiles () {
	fileReader.open ("english.txt");
	while (!fileReader.eof()) {
		english.push_back("");
		getline (fileReader, english[english.size()-1]);
	}
	fileReader.open ("wordlist-german.txt");
	while (!fileReader.eof()) {
		german.push_back("");
		getline (fileReader, german[german.size()-1]);
	}
}

void generateCharsForString (std::string input) {
	for (int i = 0; i < 13; i++) {
		inputVals[i] = input[i];
	}
}