/*
 * The goal of the program is to get a square matrix of order n,
 * the elements of which are given numbers a1, ..., an, arranged
 * in a spiral in it.
 * To enumerate matrix rows/columns pointers are used.
 */

#include "../headers/config.h"


void printMatrix(int** _matrix, int _matrix_size) {
    for (int i{}; i < _matrix_size; i++) {
        for (int j{}; j < _matrix_size; j++) {
            cout << setw(trunc(log(_matrix_size * _matrix_size)) + 1) << _matrix[i][j];
        }
        cout << endl;
    }
}

void fillMatrix(int** _matrix, int _matrix_size) {
    int num = 1;
    int sizer = _matrix_size - 1;
    int pulser{};

    while (num <= _matrix_size * _matrix_size) {
        /* Last row */
        for (int i = sizer; i > pulser; i--) {
            *(*(_matrix + sizer) + i) = num++;
        }
        /* First column */
        for (int i = sizer; i > pulser; i--) {
            *(*(_matrix + i) + pulser) = num++;
        }
        /* First row */
        for (int i = pulser; i < sizer; i++) {
            *(*(_matrix + pulser) + i) = num++;
        }
        /* Last column */
        for (int i = pulser; i < sizer; i++) {
            *(*(_matrix + i) + sizer) = num++;
        }
        pulser++; sizer--;

        if (num >= _matrix_size * _matrix_size - 1) {
            *(*(_matrix + _matrix_size / 2) + _matrix_size / 2) = _matrix_size * _matrix_size;
            break;
        }
    }
}

void runBeta_1_1() {
    int matrix_size{};

    cout << "Enter matrix size: ";
    cin >> matrix_size;


    auto matrix = new int* [matrix_size];
    for (int i{}; i < matrix_size; i++) {
        *(matrix + i) = new int[matrix_size];
    }

    fillMatrix(matrix, matrix_size);
    printMatrix(matrix, matrix_size);
}
