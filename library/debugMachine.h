#pragma once
#include <string>
#include <iostream>
#include <cstdlib>

inline class debugMachine {
public:
	void out (std::string toWrite, bool nl = true) {
		if (write) {
			std::cout << toWrite;
			if (nl) {
				std::cout << std::endl;
			}
		}
	}
	void warn (std::string toWrite, bool nl = true) {
		if (write && writeWarnings) {
			std::cout << "\033[31mWARNING: " << toWrite << "\033[0m";
			if (nl) {
				std::cout << std::endl;
			}
		}
	}
	void info (std::string toWrite, bool nl = true) {
		if (write && writeInfos) {
			std::cout << "\033[36mINFO: " << toWrite << "\033[0m";
			if (nl) {
				std::cout << std::endl;
			}
		}
	}
	void debug (std::string toWrite, bool nl = true) {
		if (write && writeDebug) {
			std::cout << "\033[35mDEBUG: " << toWrite << "\033[0m";
			if (nl) {
				std::cout << std::endl;
			}
		}
	}	
	bool write;
	bool writeWarnings = true;
	bool writeInfos = true;
	bool writeDebug = true;
} d;
