/*
 * Perform the task using dynamic memory allocation for a one-dimensional array.
 * Given (in a text file) n>109 positive integers (each number 10^4). The memory
 * limit is 1 Mb. Get the array in one file elements view:
 *
 * 2. in which all the numbers in the source file are arranged in descending order
 * (without repetitions);
 */

#include "../headers/config.h"

void createFile(string _file_name, const int _max_array_number);

void runBeta_2_1() {
	string file_name = "filename.txt";
	const int MAX_ARRAY_NUMBER = 10000;

	//createFile(file_name, MAX_ARRAY_NUMBER); // Creates a file (already created 2.2 GB file)

	bool * array = new bool[MAX_ARRAY_NUMBER + 1];

	fill_n(array, MAX_ARRAY_NUMBER, false);	// Filling the array with zeros


	// Reading file section 
	ifstream Myfile(file_name, ios_base::in);

	for (int i {}, element; i < MAX_ARRAY_NUMBER; i++) {
		Myfile >> element;
		array[element] = 1;
	}

	Myfile.close();


	// Array output section
	printf("Sorted part:\n");

	for (int j = MAX_ARRAY_NUMBER - 1; j > 0; j--) {
		if (array[j]) {
			cout << j << " " << flush;
		}
	}

	delete[] array;

}


void createFile(string _file_name, const int _max_array_number) {
	const int MAX_FIGURE_NUMBER = INT_MAX;

	random_device random_figure;
	mt19937 generate_figure(random_figure());
	uniform_int_distribution<> distr(1, _max_array_number);

	ofstream MyFile(_file_name);

	for (int i {}; i < MAX_FIGURE_NUMBER; i++) {
		MyFile << distr(generate_figure) << " ";
	}

	MyFile.close();
}
