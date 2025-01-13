/**
 * 
 * Write a function that returns a reference to the minimum number
 * that occurs in a given array of arbitrary size (the argument of the function)
 * more than once. 
 * If there is no such number, return a reference to the minimal number in the
 * array. Replace this element with a value of k
 * 
 */

#include "../headers/config.h"

void generateMatrix(int** _matrix, int _matrix_size, int _random_min, int _random_max) {
    /* Random generator settings */
    random_device random_number;
    mt19937 generate(random_number());
    uniform_int_distribution<> range(_random_min, _random_max);

    for (int i{}; i < _matrix_size; i++) {
        for (int j{}; j < _matrix_size; j++) {
            _matrix[i][j] = range(generate);
        }
    }
}

void outputMatrix(int** _matrix, int _matrix_size) {
    for (int i{}; i < _matrix_size; i++) {
        for (int j{}; j < _matrix_size; j++) {
            cout << setw(8) << _matrix[i][j];
        }
        cout << endl;
    }
}

void getLink(int** _matrix, int _matrix_size, int &_replacer) {
    int local_row{}, local_column{}, min_value{}, initial_replacer = _replacer;
    int comparator = INT_MAX;
    /* Finding the minimum repetable element */
    for (int i{}; i < _matrix_size; i++) {
        for (int j{}; j < _matrix_size; j++) {
            for (int t = i, counter{}; t < _matrix_size; t++) {
                for (int s = j; s < _matrix_size; s++) {

                    if (_matrix[i][j] == _matrix[t][s]) {
                        counter++;

                        local_row = i;
                        local_column = j;
                    } 

                    if (counter > 1) {
                        min_value = _matrix[local_row][local_column];
                        if (comparator > min_value) {
                            comparator = min_value;
                            _replacer = min_value;
                        }
                    }
                }
            }
        }
    }
    
    /* Finding the minimum non-repetable element and replacing it */
    if (_replacer == initial_replacer) {
        int comparator = INT_MAX;
        for (int i{}; i < _matrix_size; i++) {
            for (int j{}; j < _matrix_size; j++) {
                if (comparator > _matrix[i][j]) {
                    comparator = _matrix[i][j];
                    local_row = i;
                    local_column = j;
                }
                
            }
        }

        _matrix[local_row][local_column] = _replacer;
    }
    else {
        for (int i{}; i < _matrix_size; i++) {
            for (int j{}; j < _matrix_size; j++) {
                if (_matrix[i][j] == _replacer) {
                    _matrix[i][j] = initial_replacer;
                }
            }
        }
    }

}


void runBeta_1_3() {
    int matrix_size, replacer, min_range, max_range;

    cout << "Enter the number of values: "; cin >> matrix_size;
    cout << "Enter a replacer: "; cin >> replacer;
    cout << "Define min matrix number: "; cin >> min_range;
    cout << "Define max matrix number: "; cin >> max_range;


    int** matrix = new int* [matrix_size];

    for (int i{}; i < matrix_size; i++) {
        matrix[i] = new int[matrix_size];
    }


    generateMatrix(matrix, matrix_size, min_range, max_range);

    outputMatrix(matrix, matrix_size);

    getLink(matrix, matrix_size, replacer);

    cout << "The link is: " << replacer << endl;

    outputMatrix(matrix, matrix_size);

    memset(matrix, 0, matrix_size * matrix_size);

}



