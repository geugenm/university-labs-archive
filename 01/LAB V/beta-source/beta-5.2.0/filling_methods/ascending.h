#pragma once

#include "../../../headers/config.h"

template <class T>

void ascendingFill(T array[], int array_size, T min_value, T max_value, T step) {

	for (int i{}; (min_value + i * step <= max_value) && (i <= array_size - 1); i++) {

		array[i] = min_value + i * step;
	}
}