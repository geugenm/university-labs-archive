#include "../headers/config.h"

/*
 * Perform the task using dynamic memory allocation for a two-dimensional array in two ways:
 *	1. Describing a two-dimensional array as a one-dimensional array, calculating an array
 *	   element offset using a linear formula;
 *
 *	2. Describing a two-dimensional array as a pointer to an array of pointers.
 */


 //
 // ────────────────────────────────────────────────────────────────────────────── I ──────────
 //   :::::: F U N C T I O N   P R O T O T Y P E S : :  :   :    :     :        :          :
 // ────────────────────────────────────────────────────────────────────────────────────────
 //

template <typename T> void sumMatrix(T _matrix_a, T _matrix_b, T _result_matrix, int matrix_size);

template <typename T> void printMatrix(T _matrix, int _matrix_size);

template <typename T> void multiplicateMatrix(T _matrix_a, T _matrix_b, T _result_matrix, int _matrix_size);


double * getMatrixElementLink(double ** _matrix, int _row, int _col, int _offset);

double * getMatrixElementLink(double ** _matrix, int _row, int _col, int _offset);


void initRandomMatrix(double ** _matrix, int _matrix_size);

void initRandomMatrix(double * _matrix, int _matrix_size);


// ────────────────────────────────────────────────────────────────────────────────



//
// ────────────────────────────────────────────────────────────────── II ──────────
//   :::::: C O R E   F U N C T I O N : :  :   :    :     :        :          :
// ────────────────────────────────────────────────────────────────────────────
//

void runBeta_2_2() {
	int matrix_size;

	cout << "Enter matrix size:"; cin >> matrix_size;

	cout << endl;


	double ** matrix_A = new double * [matrix_size];
	double ** matrix_B = new double * [matrix_size];
	double ** matrix_C = new double * [matrix_size];

	double ** matrix_sum = new double * [matrix_size];
	double ** matrix_multiplication = new double * [matrix_size];


	initRandomMatrix(matrix_A, matrix_size); cout << "Matrix A:" << endl;
	printMatrix(matrix_A, matrix_size);

	initRandomMatrix(matrix_B, matrix_size); cout << "Matrix B:" << endl;
	printMatrix(matrix_B, matrix_size);

	initRandomMatrix(matrix_C, matrix_size); cout << "Matrix C:" << endl;
	printMatrix(matrix_C, matrix_size);



	sumMatrix(matrix_A, matrix_B, matrix_sum, matrix_size); cout << "Matrix A + B:" << endl;
	printMatrix(matrix_sum, matrix_size);

	multiplicateMatrix(matrix_sum, matrix_C, matrix_multiplication, matrix_size); cout << "Matrix (A + B) * C:" << endl;
	printMatrix(matrix_multiplication, matrix_size);
}

// ────────────────────────────────────────────────────────────────────────────────



//
// ──────────────────────────────────────────────────────────────────────────────────────────────── III ──────────
//   :::::: M I S C E L L A N E O U S   H E L P   F U N C T I O N S : :  :   :    :     :        :          :
// ──────────────────────────────────────────────────────────────────────────────────────────────────────────
//

double * getMatrixElementLink(double ** _matrix, int _row, int _col, int _offset) {
	return &_matrix[_row][_col];
}

double * getMatrixElementLink(double * _matrix, int _row, int _col, int _offset) {
	return &_matrix[_row * _offset + _col];
}

// ────────────────────────────────────────────────────────────────────────────────



//
// ──────────────────────────────────────────────────────────────────────────────────────────────────────────── IV ──────────
//   :::::: M A T R I C E S   I N I T I A L I Z A T I O N   A N D   O U T P U T : :  :   :    :     :        :          :
// ──────────────────────────────────────────────────────────────────────────────────────────────────────────────────────
//

template <typename T> void printMatrix(T _matrix, int _matrix_size) {
	for (int i {}; i < _matrix_size; i++) {
		for (int j {}; j < _matrix_size; j++) {
			cout << setw(12) << *getMatrixElementLink(_matrix, i, j, _matrix_size) << flush;
		}
		cout << endl;
	}
	cout << "\n\n" << endl;
}

random_device random_figure;
mt19937 generate_figure(random_figure());
uniform_real_distribution<double> real_range(0.0, 100.0);

void initRandomMatrix(double ** _matrix, int _matrix_size) {
	for (int i {}; i < _matrix_size; i++) {
		_matrix[i] = new double[_matrix_size];
		for (int j {}; j < _matrix_size; j++) {
			_matrix[i][j] = real_range(generate_figure);
		}
	}
}

void initRandomMatrix(double * _matrix, int _matrix_size) {
	for (int i {}; i < _matrix_size * _matrix_size; i++) {
		_matrix[i] = real_range(generate_figure);
	}
}

// ────────────────────────────────────────────────────────────────────────────────



//
// ────────────────────────────────────────────────────────────────────────── V ──────────
//   :::::: M A T R I X   O P E R A T I O N S : :  :   :    :     :        :          :
// ────────────────────────────────────────────────────────────────────────────────────
//

template <typename T> void sumMatrix(T _matrix_a, T _matrix_b, T _result_matrix, int _matrix_size) {
	initRandomMatrix(_result_matrix, _matrix_size);
	for (int i {}; i < _matrix_size; i++) {
		for (int j {}; j < _matrix_size; j++) {
			*getMatrixElementLink(_result_matrix, i, j, _matrix_size) = *getMatrixElementLink(_matrix_a, i, j, _matrix_size) + *getMatrixElementLink(_matrix_b, i, j, _matrix_size);
		}
	}
}

template <typename T> void multiplicateMatrix(T _matrix_a, T _matrix_b, T _result_matrix, int _matrix_size) {
	initRandomMatrix(_result_matrix, _matrix_size);
	for (int i {}; i < _matrix_size; i++) {
		for (int j {}; j < _matrix_size; j++) {
			*getMatrixElementLink(_result_matrix, i, j, _matrix_size) = 0;
			for (int k {}; k < _matrix_size; k++) {
				*getMatrixElementLink(_result_matrix, i, j, _matrix_size) += *getMatrixElementLink(_matrix_a, i, k, _matrix_size) * *getMatrixElementLink(_matrix_b, k, j, _matrix_size);
			}
		}
	}
}

// ────────────────────────────────────────────────────────────────────────────────