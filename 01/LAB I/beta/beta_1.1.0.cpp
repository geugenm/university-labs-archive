#include "../headers/config.h"

void beta_source_1_1_0() {
	/* A program that calculates the value of the function for
	the given initial data (s, t are integers, x is real), providing options:
	entering data from the keyboard, initializing data in the program,
	displaying the result on the screen */

	/* Local variables */
	double x, num, den;
	int s, t;


	cout << "s:"; cin >> s;
	cout << "t:"; cin >> t;
	cout << "x:"; cin >> x;

	if (x * s < 0 or t <= 0) {
		cout << "'x * s' cant be < 0 or/and 't' cant be <= 0";
		exit(0);
	}

	if (1 + pow(x, 3) == 0) {
		cout << "'1 + x^3' cant be <= 0";
		exit(0);
	}

	if (t % 2 == 0 and 1 + pow(x, 3) < 0) {
		cout << "'1 + x^3' cant be < 0 while 't % 2' = 0";
		exit(0);
	}

	num = 1 + pow(s * x, 1 / 2);
	den = pow(1 + pow(x, 3), t);

	cout << num / den;
}