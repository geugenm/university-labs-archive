#pragma once

#include "../../../headers/config.h"

template <class T>

void descendingFill(T array[], int array_size, T min_value, T max_value, T step) {

	for (int i{}; (max_value - i * step >= min_value) && (i <= array_size - 1); i++) {

		array[i] = max_value - i * step;
	}
}