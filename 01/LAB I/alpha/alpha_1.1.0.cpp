#include "../headers/config.h"

void alpha_source_1_1_0() {
	/* A program that calculates the value of a function
	for various values of the argument x, specifying it as an integer,
	as a real number. */

	// M_E = e, M_PI = pi (if #define _USE_MATH_DEFINES)

	double argument;

	std::cout << "Input argument: ";
	std::cin >> argument;

	const double numerator = 1 / sqrt(argument) + cos(pow(M_E, argument)) + cos(pow(argument, 2));
	const double denominator_part = pow(M_E, cos(argument)) + sqrt(sin(M_PI * argument));
	const double final_denominator = pow(log(pow(1 + argument, 2)) + sqrt(denominator_part), 1 / 3);

	std::cout << "Final result is: " << numerator / final_denominator << std::endl;
}