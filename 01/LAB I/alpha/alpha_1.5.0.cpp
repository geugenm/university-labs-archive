#include "../headers/config.h"

void alpha_source_1_5_0() {
	/* This is a program that calculates the value of the function
	given in the form of a graph based on the entered value of the argument. */

	/* Local variables */
	double x, y;

	cout << "x:"; cin >> x;

	if (x <= -8) {
		y = -3;
	}
	else {
		if (x <= -3 && x >= -8) {
			y = 3 / 5 * x + 9 / 5 * x;
		}
		else {
			if (x <= 3 && x >= -4) {
				y = -pow(9 - pow(x, 2), 1 / 2);
			}
			else {
				if (x <= 5 && x >= 3) {
					y = x - 3;
				}
				else {
					if (x >= 5) {
						y = 3;
					}
				}
			}
		}
	}

	cout << y;

}