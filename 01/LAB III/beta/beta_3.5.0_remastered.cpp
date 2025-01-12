/* afl-3.0 License */

/*
 * Square matrices (triangular or symmetric) of order n are specified
 * as one-dimensional arrays of (n + 1) n/2 numbers to save memory: 
 * first there are n elements of the first row, then n - 1 elements of 
 * the second row, starting from the second element, and so on. 
 * (from the last n-th line only n-th element is taken). 
 */

#include "../headers/config.h"
#define  num(row,col)  ((col) + (row) * max_line_size) // Macro for converting two indexes into one

int getRandomNumber(int min, int max) {
    static const double fraction = 1.0 / (static_cast<double>(RAND_MAX) + 1.0); 
	
    return static_cast<int>(rand() * fraction * (max - min + 1) + min);
}

void showMatrix(int* matrix, int max_matrix_line) {
    for (int i{}; i < max_matrix_line; ++i) {   //  Row selection 
        for (int j{}; j < max_matrix_line; ++j) {   //  Сolumn selection 
            cout << setw(max_matrix_line) << matrix[i * max_matrix_line + j];
        }
        cout << '\n';
    }
    cout << '\n';
}
 
int main() {
    int max_line_size, matrix_size, counter{};

    cout << "Enter the max number of data:"; cin >> max_line_size;

    matrix_size = pow(max_line_size, 2); // It is used only to set the size of source matrices

    int* initial_matrix = new int[matrix_size];

    int* transposed_matrix = new int[matrix_size];

    int* final_matrix = new int[matrix_size];

    // Filling the initial matrix
    for(int i{}; i <= (max_line_size - 1); i++) {
        //  Fill the original line with zeros
        for(int k{}; k <= (max_line_size - 1); k++) {
            initial_matrix[(i + 1) * (max_line_size) - k] = 0;
        }
        //  Fill in the original line with numbers up to counter
        for(int l{}; l <= counter; l++) {
            initial_matrix[i * (max_line_size) + l] = getRandomNumber(0, 12);
        }
        counter++;
    }

    showMatrix(initial_matrix, max_line_size);
    counter = 0;

    // Output the transposed matrix
    for(int i{}; i <= max_line_size - 1; i++) {
        for(int j{}; j <= max_line_size - 1; j++) {
            transposed_matrix[i * (max_line_size) + j] = initial_matrix[j * max_line_size + counter];
        }
        counter++;
    }

    showMatrix(transposed_matrix, max_line_size);

    //  Matrix multiplication
    for(int i = 0; i < max_line_size; ++i){
        for(int j = 0; j < max_line_size; ++j) {
            int sum{};
            for(int k = 0; k < max_line_size; ++k) {
                sum += initial_matrix[num(i,k)] * transposed_matrix[num(k,j)];
                final_matrix[num(i, j)] = sum;
            }
        }
    }
 
    showMatrix(final_matrix, max_line_size);
 
    exit(0);
}