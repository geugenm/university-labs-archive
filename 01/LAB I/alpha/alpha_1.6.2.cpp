#include "../headers/config.h"

void alpha_source_1_6_2() {
	/* Given real x, y, z. Calculate the ingestion using if operator */

	/* Local variables */
	double x, y, z, max_var, min_var, num, den;

	cout << "x:"; cin >> x;
	cout << "y:"; cin >> y;
	cout << "z:"; cin >> z;

	if (max(x, y) < z) {
		max_var = z;
	}
	else {
		max_var = max(x, y);
	}

	if (min(x, y) > z) {
		min_var = z;
	}
	else {
		min_var = min(x, y);
	}

	num = pow(max_var, 2) - pow(2, x) * min_var;
	den = sin(2) + max_var / min_var;

	cout << num / den;

}