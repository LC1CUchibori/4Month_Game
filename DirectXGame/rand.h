#pragma once
#include <iostream>
#include <cstdlib>
#include <ctime>

class Rand {
public:
	Rand() {
		srand(static_cast<unsigned int>(time(0)));

	}
	int GetRandamNumber(int min, int max) {
		return rand() % (max - min +1)+min;
	}
};