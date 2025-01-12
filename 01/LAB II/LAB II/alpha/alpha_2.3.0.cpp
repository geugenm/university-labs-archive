#include "../headers/config.h"

void alpha_2_3_0() {
	/* Given natural numbers n, m. Get their common divisors */

	/* Local variables */
	int m, n;

	cout << "m:"; cin >> m;
	cout << "n:"; cin >> n;

	for (int i{1}; i < min(m, n); i++) { // i{1}, division by '0'
		if ((m % i == 0) && (n % i == 0)) {
			printf("One possible division by %d", i);
		}
	}

}