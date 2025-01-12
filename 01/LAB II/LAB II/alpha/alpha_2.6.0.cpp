#include "../headers/config.h"

bool M_SIMPLICITY(long long _TARGET) {
	/* If _TARGET is divided by an iterator, 
	the function becomes 'false'(number is not simple) */
	for (long long i{ 2 }; i < _TARGET; i++) { // ?sqrt(_TARGET)
		if (_TARGET % i == 0) {
			return false;
		}
	}
	return true;
}

void alpha_2_6_0() {
	/* A natural n is given. Get all its prime divisors. */

	/* Local variables */
	int n;

	cout << "n:"; cin >> n;

	for (int i{2}; i <= n; i++) {
		if ((n % i == 0) && (M_SIMPLICITY(i) == true)) {
			printf("'%d' is a simple divisor of %d \n", i, n);
		}
	}

}