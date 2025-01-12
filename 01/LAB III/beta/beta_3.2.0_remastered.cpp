#include "../headers/config.h"

/*
    * Obtain a square matrix B of order n, each element bij of which is equal to 
    * the maximum of the elements of the original square matrix A of order n, 
    * located in the shaded area (including the borders), defined by the corresponding 
    * indices i, j in the figure. The matrix A is generated randomly.  
    */

int main() {
    srand(time(0)+123); // Initialization of the random number generator kernel using seed '123'
    int initial_matrix_size, row_max_element, mi;
    mi = -10000;
    
    cout << "Initial matrix size:"; cin >> initial_matrix_size;
    
    vector <vector<int>> matrix_initial, matrix_final;
    matrix_initial.assign(initial_matrix_size, vector<int> (initial_matrix_size,mi));
    matrix_final.assign(initial_matrix_size, vector<int> (initial_matrix_size,mi));
    
    cout << "\nInitial matrix:\n";

    //  Filling the initial matrix with random values, consistently outputting them
    for(int i{}; i < initial_matrix_size; i++) {
        for(int j{}; j < initial_matrix_size; j++) {
            matrix_initial[i][j] = rand() % int(pow(10, 2));
            cout << setw(4) << matrix_initial[i][j] ;
        }
        cout << endl;
    }
    
    for(int i{}; i < initial_matrix_size; i++) {
        for(int j{}; j < initial_matrix_size; j++) {
            for(int k{}; k <= i; k++) {
                for(int l{j}; l < initial_matrix_size; l++) {
                    matrix_final[i][j] = max(matrix_final[i][j], matrix_initial[k][l]);
                }
            }
        }
    }
    
    cout << matrix_final[0][0];
    
    for(int i{}; i < initial_matrix_size; i++) {
        for(int j{}; j < initial_matrix_size; j++) {
            cout << setw(4) << matrix_final[i][j] ;
        }
        cout << endl;
    }
    
    
    return 0;
}
