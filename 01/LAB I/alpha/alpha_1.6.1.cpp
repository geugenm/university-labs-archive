#include "../headers/config.h"

void alpha_source_1_6_1() {
	/* Given real x, y, z. Calculate the ingestion using conditional operator */

	/* Local variables */
	double x, y, z, max_var, min_var, num, den;

	cout << "x:"; cin >> x;
	cout << "y:"; cin >> y;
	cout << "z:"; cin >> z;

	max_var = max(y, z) > x ? max(y, z) : x;
	min_var = min(y, z) > x ? x : min(y, z);

	num = pow(max_var, 2) - pow(2, x) * min_var;
	den = sin(2) + max_var / min_var;

	cout << num / den;

}