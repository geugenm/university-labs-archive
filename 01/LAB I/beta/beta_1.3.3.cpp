#include "../headers/config.h"

void beta_source_1_3_3() {
	/* Execute the task in two ways:
	using the if statement and using the conditional operator ? */

	/* Local variables */
	double x, y, z, min_var, max_var, mid_var;

	cout << "x:"; cin >> x;
	cout << "y:"; cin >> y;
	cout << "z:"; cin >> z;

	max_var = max(y, z) <= x ? x : max(y, z);
	min_var = min(y, z) >= x ? x : min(y, z);
	mid_var = min(x, y) <= z && z <= max(x, y) ? z : max(min_var, max(x, y));

	cout << "x: " << min_var << endl;
	cout << "y: " << mid_var << endl;
	cout << "z: " << max_var << endl;

}