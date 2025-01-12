/*
	* Insertion sort iterates, consuming one input element each repetition, 
	* and grows a sorted output list. At each iteration, insertion sort removes
	* one element from the input data, finds the location it belongs within the 
	* sorted list, and inserts it there. It repeats until no input elements remain.
	* 
	* Original idea source: https://en.wikipedia.org/wiki/Insertion_sort
	*/

#pragma once

#include "../../../headers/config.h"

template<typename T>
void insertionSort(T array[], int array_size) {
	int operation_swap_counter{}, operation_compare_counter{};

	for (int j{ 2 }, i{}; j <= array_size - 1; j++) {
		int key = array[j];
		i = j - 1;
		while (i > 0 && array[i] > key) {
			array[i + 1] = array[i];
			i--;

			operation_swap_counter++;
			operation_compare_counter++;
		}

		array[i + 1] = key;

		operation_swap_counter++;
		operation_compare_counter += 2;
	}

	printf("Total Operations:\nSwap: %d\nCompare: %d\n", operation_swap_counter, operation_compare_counter);
}