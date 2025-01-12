#include "../headers/config.h"

/*
	* That is a program that outputs all supersimple
	* numbers in the range from a to b.
	*
	* NOTE: A number is called supersimple if it is prime,
	* and the number obtained from the original number by
	* writing the digits of the original number in
	* reverse order("flip") will also be prime.
	*/


void beta_2_2_0() {
	/* Local variables */
	double zero_x{ -0.8 }, delta_x{ 0.1 }, max_x{ 1 }, current_x{ -0.8 }, seq, y;
	double epsilan = pow(10, -6);
	double alpha, beta;


	class {
	public:
		double operator()(double _x, double _iterator) {
			return pow(_x, _iterator) / _iterator;
		}
	} taylor_sequence;


	class {
	public:
		double operator()(double _x) {
			return log(1 - _x) + _x;
		}
	} function_sequence;


	for (double i{ 2 }, j{}; current_x <= max_x; i++, j++) {
		current_x = zero_x + j * delta_x;

		alpha = taylor_sequence(current_x, (i - 1));
		beta = taylor_sequence(current_x, i);

		if (abs(alpha - beta) < epsilan) {
			cout << "x: " << current_x;
			cout << "y(t): " << taylor_sequence(current_x, i);
			cout << "y(f): " << function_sequence(current_x) << endl;
		}
	}

	exit(0); // Fixes the console freeze
}