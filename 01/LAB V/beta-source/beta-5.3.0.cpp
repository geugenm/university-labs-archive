#include "../headers/config.h"
#include "../headers/references.h"

void inputMatrix(int **matrix, int vertical_size, int horizontal_size) {

	srand((unsigned int)time(NULL));

	for (int i{}; i <= vertical_size -1; i++) {

		matrix[i] = new int[horizontal_size];

		for (int j{}; j <= horizontal_size - 1; j++) {

			matrix[i][j] = int( - 256 + rand() % 512);
		}

	}

}

void showMatrix(int** matrix, int vertical_size, int horizontal_size) {

	for (int i{}; i <= vertical_size - 1; i++) {

		for (int j{}; j <= horizontal_size - 1; j++) {

			cout << setw(vertical_size) << matrix[i][j];

		}

		cout << endl;
	}
}

void matrixSort(int** matrix, int vertical_size, int horizontal_size) {

	for (int i{}; i <= horizontal_size - 1; i++) {

		for (int j{ i }; j > 0 && matrix[0][j - 1] <= matrix[0][j]; j--) {

			for (int k{}; k < vertical_size; k++) {

				swap(matrix[k][j - 1], matrix[k][j]);
			}
		}

	}

}

void runBeta_5_3_0() {

	srand((unsigned int)time(NULL));

	int vertical_size, horizontal_size;

	cout << "Enter the size of the matrix: ";
	cin >> vertical_size >> horizontal_size;

	int** initial_matrix = new int* [vertical_size];

	inputMatrix(initial_matrix, vertical_size, horizontal_size); 
	showMatrix(initial_matrix, vertical_size, horizontal_size);

	printf("\n\n");

	matrixSort(initial_matrix, vertical_size, horizontal_size); 
	showMatrix(initial_matrix, vertical_size, horizontal_size);
	
}