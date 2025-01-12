#include "../headers/config.h"

void alpha_source_1_3_1() {
	/* Assign a boolean variable the value of a boolean expression,
	true if the following condition is met and false otherwise. */

	/* Local variables */
	int64_t numerator;
	int64_t denominator;

	std::cout << "Input numerator: ";
	std::cin >> numerator;

	std::cout << "Input denominator:";
	std::cin >> denominator;

	const bool status = (numerator % denominator == 0);

	std::cout << "Result: " << status << std::endl;
}