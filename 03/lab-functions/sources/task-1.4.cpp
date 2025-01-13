/**
 * Calculate the root of the equation f (x) 0 on the interval [a; b] with accuracy eps=10^-6,
 * using the half division method for given functions. Calculate the root of the equation 
 * as a function with a functional parameter, the parameters a, b,eps, s - as arguments by default.
 * The result is presented as a table (s - value of the parameter, x - calculated root of the equation,
 * f(x) - value of the function at the found point x, k_iter - number of iterations of the cycle to get
 * the root with a given accuracy).
*/

#include "../headers/config.h"



double alphaFunction(double _argument, double _step) {
	return pow(_argument, 3) - 3;
}

double betaFunction(double _argument, double _step) {
	return pow(_argument, 1 / _step) - 2 * pow(cos(M_PI * _argument / 2), 2);
}

double calculateDichotomy(double (*_function)(double, double), double _segment_start, double _segment_end, double _bial, double _step) {
	while (fabs(_segment_start - _segment_end) >= _bial) {
		if ((_function(_segment_start, _step) > 0 && _function((_segment_start + _segment_end) / 2, _step) < 0) || (_function(_segment_start, _step) < 0 && _function((_segment_start + _segment_end) / 2, _step) > 0))
			_segment_end = (_segment_start + _segment_end) / 2;
		else
			if ((_function((_segment_start + _segment_end) / 2, _step) > 0 && _function(_segment_end, _step) < 0, _step) || (_function((_segment_start + _segment_end) / 2, _step) < 0 && _function(_segment_end, _step) > 0)) {
				_segment_start = (_segment_start + _segment_end) / 2;
			}
			else {
				cout << "No roots" << endl;
			}
	}
	return (_segment_start + _segment_end) / 2;
}

void runBeta_1_4() {
	double step_start = 0.5, step_end = 2.0, step = 0.5, bial = pow(10, -6);
	double segment_alpha_start = 1.0, segment_alpha_end = 4.0;
	double segment_beta_start = 0.0, segment_beta_end = 4.5;

	/* Proceeding with alphaFunction() */
	cout << calculateDichotomy(alphaFunction, segment_alpha_start, segment_alpha_end, bial, step) << endl;

	for (; step_start < step_end; step_start += step) {
		/* Proceeding with betaFunction() */
		cout << calculateDichotomy(betaFunction, segment_beta_start, segment_beta_end, bial, step_start) << " for " << step_start << endl;
	}

}
