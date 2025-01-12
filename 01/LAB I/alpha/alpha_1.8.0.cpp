#include "../headers/config.h"

void alpha_source_1_8_0() {
	/* Calculate, explain the result of an expression using bitwise
	operations, for the given values of integer variables a, b, c. */

	/* Example(OR):

	0 1 0 1 // 5
	0 1 1 0 // 6
	-------
	0 1 1 1 // 7 */

	/* Local variables */
	int a, b, c, res;

	cout << "a:"; cin >> a;
	cout << "b:"; cin >> b;
	cout << "c:"; cin >> c;

	res = a | b & c; // (b & c) | a

	cout << res;

}