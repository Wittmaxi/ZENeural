#pragma once
#include <string>
#include <iostream>
#include <cstdlib>
#include <vector>

class __debugMachine {
public:
	__debugMachine (bool _write = true) {
		write = _write;
	}
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
	void good (std::string toWrite, bool nl = true) {
		if (write) {
			std::cout << "\033[32mGOOD: " << toWrite << "\033[0m";
			if (nl) {
				std::cout << std::endl;
			}
		}
	}
	bool write;
	bool writeWarnings = true;
	bool writeInfos = true;
	bool writeDebug = true;
};

struct __assert {
	int line_number;
	std::string name;
	__assert (int a, std::string b) {
		line_number = a;
		name = b;
	}
};

class __tester {
	std::vector<__assert> failed_assert;
	__debugMachine dm;
public:
	__tester () {
		dm.write = true;
	}
	void REQUIRE (bool i, std::string T) {
		if (!(i)) {
			dm.warn ("ASSERT >>" + T + "<< FAILED");
			failed_assert.push_back (__assert (__LINE__, T));
		} else {
			dm.good ("ASSERT >>" + T + "<< WORKED");
		} 
	}
	void report () {
		if (failed_assert.size() > 0) {
			dm.out ("=================================================");
		}
		for (auto i : failed_assert) {
			dm.warn (i.name + " FAILED");
		}
	}
};
