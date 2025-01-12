#include "../headers/config.h"

void beta_source_1_5_1() {
	/* Execute the task in two ways:
	using the if statement and using the conditional operator ? */

	/* Local variables */
	double x, y, a_1, b_1, c_1, a_2, b_2, c_2;
	double a_fin, b_fin, c_fin;

	cout << "a1:"; cin >> a_1;
	cout << "b1:"; cin >> b_1;
	cout << "c1:"; cin >> c_1;
	cout << "a2:"; cin >> a_2;
	cout << "b2:"; cin >> b_2;
	cout << "c2:"; cin >> c_2;

	a_fin = (a_1 * b_2 - a_2 * b_1 != 0) ? b_1 * c_2 - b_2 * c_1 : 1;
	b_fin = (a_1 * b_2 - a_2 * b_1 != 0) ? a_2 * c_1 - a_1 * c_2 : 1;
	c_fin = (a_1 * b_2 - a_2 * b_1 != 0) ? a_1 * b_2 - a_2 * b_1 : 1;

	cout << a_fin << endl;
	cout << b_fin << endl;
	cout << c_fin << endl;

}