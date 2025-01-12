/*
    * The algorithm divides the input list into two parts: 
    * a sorted sublist of items which is built up from left to right at 
    * the front (left) of the list and a sublist of the remaining unsorted items
    * that occupy the rest of the list. Initially, the sorted sublist is empty and
    * the unsorted sublist is the entire input list. The algorithm proceeds by finding
    * the smallest (or largest, depending on sorting order) element in the unsorted sublist,
    * exchanging (swapping) it with the leftmost unsorted element (putting it in sorted order),
    * and moving the sublist boundaries one element to the right.
    * 
    * Original idea source: https://en.wikipedia.org/wiki/Selection_sort
    */

#pragma once

#include "../../../headers/config.h"

template<typename T>
void samplingSort(T array[], int array_size) {
    int operation_swap_counter{}, operation_compare_counter{};

    for (int idx_i{}; idx_i < array_size - 1; idx_i++) {

        int min_idx = idx_i;

        for (int idx_j = idx_i + 1; idx_j < array_size; idx_j++) {

            if (array[idx_j] < array[min_idx]) {

                min_idx = idx_j;

                operation_compare_counter++;
            }
        }

        if (min_idx != idx_i) {

            swap(array[idx_i], array[min_idx]);

            operation_swap_counter++;
        }

        operation_compare_counter += 2;
    }

    printf("Total Operations:\nSwap: %d\nCompare: %d\n", operation_swap_counter, operation_compare_counter);
}