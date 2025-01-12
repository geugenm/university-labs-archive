#include <iostream>
#include <iomanip>
#include <time.h>

using namespace std;

/*
 * This code zeroes all repeated elements from the two-dimensional array, 
 * moving them to the end, while the unique elements are shifted to the 
 * positions of the zeroed elements
 * 
 * NOTE:
 * 	Initial zeros are changed to '-1' so as not to be shifted
 * 
 * VS Code 1.62.3: windows-gcc-x86(C++14)
 */

void showMatrix(int **matrix, int matrix_size) {
	for(int i{}; i < matrix_size; i++) {
		for(int j{}; j < matrix_size; j++) {
			switch(matrix[i][j]) {
				case -1: 
					// Relevant during the output of the modified matrix
					// It is easier just to output a zero than to change the matrix again
					cout << setw(3) << "0"; 
					break;
				case 0:	
					// It is active during the output of the initial matrix
					cout << setw(3) << matrix[i][j];
					matrix[i][j] = -1; // Initial zero is changed to '-1'
					break;
				default:
					cout << setw(3) << matrix[i][j];
					break;
			}
		}
		cout << endl;
	}
}

void matrixUnique(int **matrix, int matrix_size) {	
	int rep_counter{};
    for(int i{}; i < matrix_size; i++) {
		for(int j{}; j < matrix_size; j++) {
			for(int k = j + 1; k <= matrix_size; k++) {
				if(matrix[i][j] == matrix[i][k]) {
					// We nullify the elements that coincide with the one being compared
					matrix[i][k] = 0; 
					rep_counter++; 
				}
			}
			if (rep_counter != 0) {
				// Zeroing the object to which we were comparing 
				matrix[i][j] = 0; 
				rep_counter = 0; 
			}
		}
		for (int j{}, e; j < matrix_size; j++) { 
			// Dragging the zeroed element to the end
			if (! matrix[i][j]) {
				e = j;
				while (! matrix[i][e]) {
					e++;
				}
				if (e >= matrix_size) {
					e = matrix_size - 1;
				}
				swap(matrix[i][j], matrix[i][e]);
			}
		}
	}
}

int main() {
	setlocale(LC_ALL, "en_US.UTF-8");
	
	srand(time(NULL));

	int matrix_size; 

	cout << "Enter the size of the matrix: "; 
	cin >> matrix_size;

	int **matrix = new int*[matrix_size];

	for(int i{}; i < matrix_size; ++i) {
    	matrix[i] = new int[matrix_size];
		for(int j{}; j < matrix_size; j++) {
			matrix[i][j] = rand() % 20;
		}
	}

	showMatrix(matrix, matrix_size);

	cout << "\nNew matrix:\n\n";

	matrixUnique(matrix, matrix_size);

	showMatrix(matrix, matrix_size);

	exit(0);
}