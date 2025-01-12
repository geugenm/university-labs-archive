#pragma once

#include "../../../headers/config.h"

template <class T>

void randomFill(T array[], int array_size, T min_value, T max_value) {
	srand((unsigned int)time(NULL));

	for (int i{}; i <= array_size - 1; i++) {

		array[i] = min_value + rand() % (2 * max_value);
	}
}