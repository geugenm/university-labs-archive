#include "../headers/config.h"

void beta_source_1_5_0() {
	/* Execute the task in two ways:
	using the if statement and using the conditional operator ? */

	/* Local variables */
	double a_1;
	double b_1;
	double c_1;
	double a_2;
	double b_2;
	double c_2;

	cout << "a1:";
	cin >> a_1;

	cout << "b1:";
	cin >> b_1;

	cout << "c1:";
	cin >> c_1;

	cout << "a2:";
	cin >> a_2;

	cout << "b2:";
	cin >> b_2;

	cout << "c2:";
	cin >> c_2;

	/* We can transform points in 2-dimensional space into
	homogeneous coordinates by equating the third coordinate to one */

	if (a_1 * b_2 - a_2 * b_1 != 0) {  // TODO Add Nonexistance Branch

		cout << "Intersection found: \n";
		cout << "P = (" << b_1 * c_2 - b_2 * c_1 << ", ";
		cout << a_2 * c_1 - a_1 * c_2 << ", ";
		cout << a_1 * b_2 - a_2 * b_1 << ")";

		if (a_1 == a_2 && b_1 == b_2 && c_1 == c_2) {
			cout << "The lines match";
		}
	}
	else {
		cout << "Lines do not cross each other (c = 0)";
	}

}