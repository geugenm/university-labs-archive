#include "../headers/config.h"

/**
	* Perform the task without storing a sequence of values. 
	* A natural number k is given.
	* Determine the k-th digit of the sequence: 
	* 
	*				1101001000..., 
	* 
	* in which the degrees 10 are written out in a row.
	* 
	* NOTE: Monotonically decreasing sequence consists of 
	* the sum of powers of tens, the difference between powers 
	* increases by 1 after each iteration, for example, 
	* 10^(10-0) -> 10^(10-1) -> 10^((10-1) - 2) -> ..., 
	* degrees 10, 9, 7, 4, 0, ... are formed.
	*/

void beta_2_5_0() {
	/* Local variables */
	int k, j;

	cout << "k:"; cin >> k;

	j = k - 1;

	for (int i{}; i < k; i++) {
		cout << "j:" << j << endl;
		j -= i;
		cout << pow(10, j) << endl;
		if (j < 0) {
			j += i; // Increasing 'i' in order to check the number in the end
			cout << "Final 'j':" << j << endl;
			break;
		}
	}

	if (pow(10, j) == 1) {
		printf("Postion 'k' is '1'");
	}
	else {
		printf("Postion 'k' is '0'");
	}

	exit(0);
}
