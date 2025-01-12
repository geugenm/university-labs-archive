#include "../headers/config.h"

/*
    * Obtain a square matrix B of order n, each element bij of which is equal to 
    * the maximum of the elements of the original square matrix A of order n, 
    * located in the shaded area (including the borders), defined by the corresponding 
    * indices i, j in the figure. The matrix A is generated randomly.  
    */

int main() {
    srand(time(0)+123); // Initialization of the random number generator kernel using seed '123'
    int initial_matrix_size, final_matrix_size, row_max_element, counter{};
    
    cout << "Initial matrix size:"; cin >> initial_matrix_size;
    cout << "Final matrix size:"; cin >> final_matrix_size;
    
    vector <vector<int>> matrix_initial, matrix_final;
    matrix_initial.assign(initial_matrix_size, vector<int> (initial_matrix_size,0));
    matrix_final.assign(final_matrix_size, vector<int> (final_matrix_size,0));
    
    cout << "\nInitial matrix:\n";

    //  Filling the initial matrix with random values, consistently outputting them
    for(int i{}; i < initial_matrix_size; i++) {
        for(int j{}; j < initial_matrix_size; j++) {
            matrix_initial[i][j] = rand() % int(pow(10, 2));
            cout << matrix_initial[i][j] << ",";
        }
        cout << endl;
    }
    
    cout << "\nFinal matrix:\n";
    
    //  A global "for" loop to fill in the final matrix and sequentially output its values
    for(int i{};i < initial_matrix_size;i++) {
        
        row_max_element = matrix_initial[i][0];
        
        //  Getting the max element of the row
        for(int j{1};j < initial_matrix_size;j++) {
            if(matrix_initial[i][j] > row_max_element) {
                row_max_element = matrix_initial[i][j];
            }
        }

        //  Filling the final array with the max element of the row
        for(int j{}; j < initial_matrix_size - 1; j++) {
            matrix_final[i][j]= row_max_element; 
            cout << matrix_final[i][j] << ",";
        }

        cout << endl;
    }
    return 0;
}
