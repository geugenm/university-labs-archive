/* An array of numbers of arbitrary length is given. Sort the array using merge sorting.
 *
 * Create templates and function overloads for sorting, displaying results, and filling arrays.
 *
 * Perform array sorting for data of different types:
 * integers, real, character, C-strings, using the written functions.
 */

#include "../headers/config.h"
#include <map>


 //
 // ─── ARRAY SORT SECTION ─────────────────────────────────────────────────────────
 //

template<typename T> T * mergeSort(T * _initial_array, T * _buffer, unsigned int _left, unsigned int _right) {
	if (_left == _right) {
		_buffer[_left] = _initial_array[_left];
		return _buffer;
	}

	unsigned int middle = _left + (_right - _left) / 2;

	// Divide and sort
	T * l_buff = mergeSort(_initial_array, _buffer, _left, middle);
	T * r_buff = mergeSort(_initial_array, _buffer, middle + 1, _right);

	// Merge the two sorted halves
	T * sorted_array = l_buff == _initial_array ? _buffer : _initial_array;

	unsigned int l_cur = _left, r_cur = middle + 1;
	for (unsigned int i = _left; i <= _right; i++) {
		if (l_cur <= middle && r_cur <= _right) {
			if (l_buff[l_cur] < r_buff[r_cur]) {
				sorted_array[i] = l_buff[l_cur];
				l_cur++;
			}
			else {
				sorted_array[i] = r_buff[r_cur];
				r_cur++;
			}
		}
		else {
			if (l_cur <= middle) {
				sorted_array[i] = l_buff[l_cur];
				l_cur++;
			}
			else {
				sorted_array[i] = r_buff[r_cur];
				r_cur++;
			}
		}

	}
	return sorted_array;
}

char ** mergeSort(char ** _initial_array, char ** _buffer, unsigned int _left, unsigned int _right) {
	unsigned int array_size = _right - _left + 1;

	char * buffer = new char[array_size];
	char * buffer_sort = new char[array_size];

	char ** sorted_array = new char * [4];

	for (unsigned int i {}; i < array_size; i++) {
		*(buffer + i) = *(*(_initial_array + i) + 0);
		*(sorted_array + i) = new char[array_size];
	}

	char * buffer_sorted = mergeSort(buffer, buffer_sort, _left, _right);
	delete[] buffer, buffer_sort;

	unsigned int current_row {};


	for (unsigned int i {}; i < array_size; i++) {
		for (unsigned int j {}; j < array_size && *(*(_initial_array + j) + 0) != '\0'; j++) {
			if (*(buffer_sorted + i) == *(*(_initial_array + j) + 0)) {
				for (unsigned int m {}; m < 4 && current_row < array_size; m++) {
					*(*(sorted_array + current_row) + m) = *(*(_initial_array + j) + m);
					*(*(sorted_array + current_row) + m + 1) = '\0';
				}
				current_row++;
			}
		}
	}

	return sorted_array;
}


//
// ─── ARRAY FILL SETTING SECTION ─────────────────────────────────────────────────
//

random_device random_figure;
mt19937 generate_figure(random_figure());

void randomArrayFill(char ** _target, int _elements_number) {
	// String array fill 
	uniform_int_distribution<> distr(33, 126);
	int string_length = 4;

	for (int i {}; i < _elements_number; i++) {
		_target[i] = new char[string_length + 1];

		for (int j {}; j < string_length; j++) {
			_target[i][j] = distr(generate_figure);
		}

		_target[i][string_length] = '\0';
	}
}

void randomArrayFill(int * _target, int _elements_number) {
	// Integer array fill
	uniform_int_distribution<> distr(0, 1000);
	for (int i = 0; i < _elements_number; i++) {
		_target[i] = distr(generate_figure);
	}
}

void randomArrayFill(double * _target, int _elements_number) {
	// Double array fill 
	uniform_real_distribution<> distr(0.0, 1000.0);
	for (int i {}; i < _elements_number; i++) {
		_target[i] = distr(generate_figure);
	}
}

void randomArrayFill(char * _target, int _elements_number) {
	// Char array fill 
	uniform_int_distribution<> distr(33, 126);
	for (int i {}; i < _elements_number; i++) {
		_target[i] = distr(generate_figure);
	}
}


//
// ─── INPUT-OUTPUT FUNCTION SECTION ──────────────────────────────────────────────
//

template <typename T>
void inputOutput(T max_element, int _elements_number, const char * _data_type) {
	cout << "Unsorted array:" << endl;

	T * initial_array = new T[_elements_number];
	randomArrayFill(initial_array, _elements_number);

	// Output unsorted array
	for (int i {}; i < _elements_number; i++) {
		cout << initial_array[i] << " ";
	}

	T * sorted_array = new T[_elements_number];
	T * buffer_array = new T[_elements_number];

	sorted_array = mergeSort(initial_array, buffer_array, 0, _elements_number - 1);

	cout << "\n\nSorted array:" << endl;

	// Output sorted array
	for (int i {}; i < _elements_number; i++) {
		cout << *(sorted_array + i) << " ";
	}

	cout << endl;
}


//
// ─── RUN FUNCTION SECTION ───────────────────────────────────────────────────────
//

void runBeta_1_6() {
	int elements_number;
	char * data_type = new char[10];

	cout << "Elements number: "; cin >> elements_number;

	cout << "Data type: "; cin >> data_type;

	if (strcmp(data_type, "int") == 0) {
		inputOutput(10, elements_number, "%d ");
	}
	else {
		if (strcmp(data_type, "char") == 0) {
			inputOutput('z', elements_number, "%c ");
		}
		else {
			if (strcmp(data_type, "str") == 0 or strcmp(data_type, "string") == 0) {
				inputOutput(data_type, elements_number, "%s ");
			}
			else {
				if (strcmp(data_type, "double") == 0) {
					inputOutput((double) 1, elements_number, "%f ");
				}
				else {
					cout << "Undefined type";
				}
			}
		}
	}

}
