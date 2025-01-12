#include "../headers/config.h"

void alpha_source_1_6_0() {
	/* Given real x, y, z. Calculate the ingestion using max() function */

	/* Local variables */
	double x, y, z, num, den;

	cout << "x:"; cin >> x;
	cout << "y:"; cin >> y;
	cout << "z:"; cin >> z;

	num = pow(max(max(x, y), z), 2) - pow(2, x) * min(min(x, y), z); // max() has only 2 args
	den = sin(2) + max(x, y) / min(y, z);

	cout << num / den;

}