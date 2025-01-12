#include "../headers/config.h"

/*
    * This program uses the "Eratosthenes sieve" algorithm
    * to find prime numbers. We determine the maximal prime
    * number that can be found by this algorithm in this programming system.
    */

//  It's asymptotics work O (sqrt(N))
bool prime(long long n){ 
	for(long long i{2};i<=sqrt(n);i++) {
		if(n%i==0) {
			return false;
        }
    }
	return true;
}

int main() {
    srand(time(0)+123); // Initialization of the random number generator kernel using seed '123'
    long long int initial_matrix_size, final_matrix_size, row_max_element;
    
    cout << "Initial matrix size:"; cin >> initial_matrix_size;
    cout << "Final matrix size:"; cin >> final_matrix_size;
    
    vector <vector<long long int>> matrix_initial, matrix_final;
    matrix_initial.assign(initial_matrix_size, vector<long long int> (initial_matrix_size,0));
    matrix_final.assign(final_matrix_size, vector<long long int> (final_matrix_size,0));
    
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
        
        row_max_element = (prime(matrix_initial[i][0]) == true) ? matrix_initial[i][0] : 0;
        
        //  Getting the max prime element of the row
        //  NOTE: If there are no prime numbers in the line, then fill it with zeros
        for(int j{1};j < initial_matrix_size;j++) {
            if((matrix_initial[i][j] > row_max_element) && (prime(matrix_initial[i][j]) == true)) {
                row_max_element = matrix_initial[i][j];
            }
        }

        //  Assignment and sequential output of the final matrix values
        for(int j{}; j < initial_matrix_size - 1; j++) {
            matrix_final[i][j]= row_max_element; 
            cout << matrix_final[i][j] << ",";
        }

        cout << endl;
    }
    return 0;
}
