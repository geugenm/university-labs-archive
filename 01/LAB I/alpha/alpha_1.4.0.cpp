#include "../headers/config.h"

void alpha_source_1_4_0() {
	/* Real numbers x, y are given. Determine if a point with
	coordinates x, y belongs to the shaded part of the plane. */

	/* Local variables */
	double x, y;

	cout << "x:"; cin >> x;
	cout << "y:"; cin >> y;

	if (abs(x) + abs(y) <= 1) {
		cout << "x,y are in";
	}
	else {
		cout << "x,y are not in";
	}

}