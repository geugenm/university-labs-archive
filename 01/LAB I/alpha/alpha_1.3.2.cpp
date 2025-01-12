#include "../headers/config.h"

void alpha_source_1_3_2() {
	/* Explain the result and display the result of the logical expression T = S
	for the given values of the logical variables a, b, c. */

	/* Local variables */
	bool a;
	bool b;
	bool c;

	/* Only '1' or '0' */
	std::cout << "a_status:";
	std::cin >> a;

	std::cout << "b_status:";
	std::cin >> b;

	std::cout << "c_status:";
	std::cin >> c;

	const bool t = a || !b && !c;
	const bool s = a || !(b || c);

	cout << "Result: " << (t == s) << std::endl;

}