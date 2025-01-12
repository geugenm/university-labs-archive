#include "../headers/config.h"
#include <vector>

void beta_source_1_3_2() {
	/* Execute the task in two ways:
	using the if statement and using the conditional operator ? */

	/* Local variables */
	double x, y, z, min_var, max_var, mid_var;

	cout << "x:"; cin >> x;
	cout << "y:"; cin >> y;
	cout << "z:"; cin >> z;


	if (max(x, y) <= z) {
		max_var = z;
	}
	else {
		if (x >= y) {
			max_var = x;
		}
		else {
			max_var = y;
		}

	}

	if (min(x, y) >= z) {
		min_var = z;
	}
	else {
		if (x <= y) {
			min_var = x;
		}
		else {
			min_var = y;
		}

	}

	if (min(x, y) <= z && z <= max(x, y)) {
		mid_var = z;
	}
	else {
		mid_var = max(min_var, max(x, y));
	}


	cout << "x: " << min_var << endl;
	cout << "y: " << mid_var << endl;
	cout << "z: " << max_var << endl;
}