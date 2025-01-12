#include "../headers/config.h"

/*
	* Execute the tasks using functions. All necessary data for functions must
	* be passed as parameters. There are three ways to get the result of a function:
	* through the return mechanism, through a pointer parameter, through a reference parameter.
	*
	* A real number x is given (0 < x 1). Calculate the given sum with accuracy = 10e-6 and specify
	* the number of summands. It is considered that the precision required is attained if the next summand
	* is less by absolute value than.
	*
	* Note: Mathematical functions from <math.h> library are not used in the program.
	*
	*/


double factorial(double object) {
	double result{ 1 }, num{ object };

	while (num - 1) {
		result *= num;
		num -= 1;
	}

	return result;
}

double findSummation(int iterator, double argument) {
	double numerator, denominator;

	numerator = pow(-1, iterator) * pow(argument, 4 * iterator + 3);
	denominator = (4 * iterator + 3) * factorial(2 * iterator + 1);

	return numerator / denominator;
}


void runBeta_5_1_0() {
	int k{ 1 }, summand_counter{};
	double x, final_sum{};

	/*
		Alternative function calls:

		1. Using pointer:
			double (*summation)(double) = findSummation;
			(*summation)(k, x); 

		2. Using link:
			double findSummation(int iterator, double argument, double &numeartor, double &denominator) {
				...
				-return numerator / denominator;
				+ numerator = ...;
				+ denominator = ...;
			}

			int num, denom, result;

			findSummation(k, x, num, denom);

			result = num / denom;
	
	*/

	cout << "Input argument value(x):"; cin >> x;

	if (x <= 1 && x > 0) {
		while (abs(findSummation(k, x)) > pow(10, -6)) {
			final_sum += findSummation(k, x);
			summand_counter++; k++;
		}
		printf("The sum is %f. Totaly %d summands were calculated.\n", final_sum, summand_counter);
	}
	else {
		cout << "Incorrect argument given.";
	}
}