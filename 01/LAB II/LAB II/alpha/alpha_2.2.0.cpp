#include "../headers/config.h"

double _SYSTEM(double arg) {
	double sys_result;

	// x < 1.4
	if ((arg < 1.4) && (arg != 0)) {
		sys_result = M_PI * pow(arg, 2) - (7 / pow(arg, 2));
		cout << "System 1: ";
		return sys_result;
	}
	// x = 1.4
	if (arg == 1.4) {
		sys_result = 1.65 * pow(arg, 3) + (7 * pow(arg, 1 / 2));
		cout << "System 2: ";
		return sys_result;
	}
	// x > 1.4
	if (arg > 1.4) {
		sys_result = M_PI * log(arg + 7 * pow(abs(arg + 1.65), 1 / 2));
		cout << "System 3: ";
		return sys_result;
	}
	
}

void alpha_2_2_0() {
	/* A program which calculates a conditional function in points 
	xi [x0; xn], xi = x0 + xx, i = 0,1, ... 
	Output the results as a table, indicating the number 
	of the branch for which it was obtained */

	/* Local variables */
	double x{}, i{1}; // i{1} because _SYSTEM() first statement has division by '0'

	for (i; x <= 3.0; i++) { 
		x = i / 10; // X0 = 0
		cout << _SYSTEM(x) << endl;
	}

	x = 0; i = 1;
	cout << "\n \n Using 'while': \n \n \n";

	while (x <= 3.0) {
		x = i / 10; // X0 = 0
		cout << _SYSTEM(x) << endl;
		i++;
	}

	x = 0; i = 1;
	cout << "\n \n Using 'do': \n \n \n";

	do {
		x = i / 10; // X0 = 0
		cout << _SYSTEM(x) << endl;
		i++;
	} while (x <= 3.0);

}