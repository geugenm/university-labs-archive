#include "../headers/config.h"

long double M_FACT(int target_num) {
	int result{1};
	for (int i{0}; i < target_num; i++) {
		result *= target_num - i;
	}
	
	return result;
}

void alpha_2_4_0() {
	/* Given a natural n, a real x. Calculate the result of the expression */

	/* Local variables */
	int k{1}, n, m{k};
	double x, sum{};

	cout << "x:"; cin >> x;
	cout << "n:"; cin >> n;

	for (k; k <= n; k++) {
		for (m; m <= n; m++) {
			sum += (x + k) / (m * M_FACT(n));
			//cout << sum << endl;
		}
	}

	cout << sum;
}