/*
	* An array of numbers of arbitrary length is given. The array is
	* sorted by specified methods: sorting by selection and insertion. 
	* To test the program, we fill the array with values in three ways: 
	* ascending, descending, and random. 
	* Each method of sorting, each method of filling the arrays is designed as separate functions.
	* The functions are written in a separate file. 
	* For each sorting method, the number of comparisons and permutations (permutations from one place to another)
	* of elements during program execution is determined. 
	* We compare the experimental results with the known theoretical estimates of 
	* these parameters for the specified sorting methods.
	* We have provided overloading and templates of necessary functions to perform the task with types of array elements char, int, float, double.
	*/

#include "../../headers/config.h"
#include "../../headers/references.h"


template <class T>
void showArray(T array[], size_t array_size) {
	for (int i{1}; i <= array_size - 1; i++) {
		cout << array[i] << " ";
	}
	printf("\n\n");
}


void runBeta_5_2_0() {
	int array_size, max_value, min_value, value_step, user_input;

	bool user_input_checker{true};

	cout << "Enter the value of the array:"; cin >> array_size;
	cout << "Maximum value to generate:"; cin >> max_value;
	cout << "Minimum value to generate:"; cin >> min_value;
	cout << "Generation step:"; cin >> value_step;
	
	int* object_array = new int[array_size];

	for (int i{}; i <= array_size - 1; i++) {
		object_array[i] = 0;
	}

	while (user_input_checker) {

		printf("Select the method of filling the array:\n1. Ascending\n2. Descending\n3. Random\n:"); cin >> user_input;

		switch (user_input) {
		case 1:
			ascendingFill(object_array, array_size, min_value, max_value, value_step);
			user_input_checker = false;
			break;
		case 2:
			descendingFill(object_array, array_size, min_value, max_value, value_step);
			user_input_checker = false;
			break;
		case 3:
			randomFill(object_array, array_size, min_value, max_value);
			user_input_checker = false;
			break;
		}

	}

	showArray(object_array, array_size);
	user_input = 0; user_input_checker = true;


	while (user_input_checker) {

		printf("Select the method of sorting the array:\n1. Insertion\n2. Sampling\n:"); cin >> user_input;

		switch (user_input) {
		case 1:
			insertionSort(object_array, array_size);
			user_input_checker = false;
			break;
		case 2:
			samplingSort(object_array, array_size);
			user_input_checker = false;
			break;
		}
	}
	
	showArray(object_array, array_size);

}
