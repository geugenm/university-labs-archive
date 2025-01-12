#include "../headers/config.h"

void beta_source_1_2_1() {
	/* Real numbers x, y are given. Determine if the x, y point belongs to
	the shaded part of the plane, including the boundaries.
	The numbers R, x, y are entered */

	/* Local variables */
	double x, y, R;
	bool out_up, out_bot, range_out, range_bot;


	cout << "R:"; cin >> R;
	cout << "x:"; cin >> x;
	cout << "y:"; cin >> y;

	out_up = pow(x + R, 2) + pow(y - R, 2) >= pow(R, 2);
	out_bot = pow(x - R, 2) + pow(y + R, 2) >= pow(R, 2);

	range_out = (x <= R && x >= 0) and (y <= 0 && y >= -R);
	range_bot = (y <= R && y >= 0) and (x <= 0 && x >= -R);

	if (out_up == true && range_out == true) {
		cout << "Argument is a part of RVV";
	}
	else {
		if (out_bot == true && range_bot == true) {
			cout << "Argument is a part of RVV";
		}
		else {
			cout << "Argument is not part of RVV";
		}
	}

}