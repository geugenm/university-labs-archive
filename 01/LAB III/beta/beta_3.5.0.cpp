/* afl-3.0 License */

/*
    * Square matrices (triangular or symmetric) of order n are specified
    * as one-dimensional arrays of (n + 1) n/2 numbers to save memory: 
    * first there are n elements of the first row, then n - 1 elements of 
    * the second row, starting from the second element, and so on. 
    * (from the last n-th line only n-th element is taken). 
    */
	
#include "../headers/config.h"

void matrixOutput(double* target_array, double* spread_array, int elements_quantity) {
    for(int i{}, j{}; max(i, j) <= elements_quantity - 1; j++) {
        if(j == spread_array[i]) {
            i++;
            cout << endl;
        }
        cout << target_array[j]<< ",";
    }
}

int main() {
    srand(time(0)+123); //  Initialization of the random number generator kernel using seed '123'
    double bufferSize;  //  bufferSize can be replaced with maxLine_size
    int i{}, j{}, counter{}, maxLine_size, elements_number;

    cout << "Enter the max number of data:"; cin >> maxLine_size;
    elements_number = ((maxLine_size + 1) * maxLine_size) / 2;

    double* init_matrix = new double[elements_number];

    double* coursor_array = new double[maxLine_size];   //  Responsible for moving the row when displaying the matrix

    double* transposed_matrix = new double[elements_number];

    bufferSize = maxLine_size;

    for(int i{}, j{}; bufferSize > 0; i++, j++) {
        if(j >= bufferSize) {
            coursor_array[counter] = j + coursor_array[counter - 1];
            counter++;
            bufferSize--;
            j = 0;
        }
        init_matrix[i] = rand() % int(pow(10, 2));
    }

    //  Output the values of the initial matrix 
    cout << "\n\nInitial Matrix:\n\n";
    matrixOutput(init_matrix, coursor_array, elements_number);

    //  Transpose Matrix
    for(int m{}; m <= maxLine_size - 1; m++) {
        for(int k{}; k <= maxLine_size - m - 1; k++) {
            transposed_matrix[(2*maxLine_size - k + 1)*k / 2 + m] = init_matrix[(2*maxLine_size - m + 1)*m / 2 + k];
        }
    }
    
    //  Output the values of the transposed matrix
    cout << "\n\nTransposed Matrix:\n\n";
    matrixOutput(transposed_matrix, coursor_array, elements_number);

    //  Multiplication of a transposed matrix by an initial matrix
    cout << "\n\nMultiplied Matrix:\n\n";
    for(int i{}, j{}; max(i, j) <= elements_number - 1; j++) {
        if(j == coursor_array[i]) {
            i++;
            cout << endl;
        }
        cout << transposed_matrix[j] * init_matrix[j] << ",";
    } 

    exit(0);
}