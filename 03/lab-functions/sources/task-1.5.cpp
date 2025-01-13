/**
* Calculate the following integrals by the given method (M = 1 - left rectangle method
* rectangles, M = 2 - the method of right rectangles, M = 3 - the method of average
* rectangles, M = 4 - trapezoid method, M = 5 - Simpson method), using the double 
* recalculation criterion, with accuracy eps = 10-6.
* 
* Values of the parameter s: si[s1; s2], si = s1 + is, i = 0, 1, ... .
* Values of the parameter t: ti[t1; t2], ti = t1 + it, i = 0, 1, ... .
* 
* The procedures are formatted as a separate file.
* 
* Present the results as a table (s, t - the corresponding values of
* parameters, Int - calculated integral value, k_iter - number of recalculations
* values of the integral to get a given accuracy)
*/


#include "../headers/config.h"


double primordial_function(double _argument, double _summation, double _degree) {
    return (pow(_summation + pow(_argument, 3), 1 / _degree));
}

double rectangle_integral(double _lower_lim, double _upper_lim, int _rect_num, double _func_summation, double _func_degree) {
    double argument, rect_length;
    double area_sum{};
    double fx;
    rect_length = (_upper_lim - _lower_lim) / _rect_num;

    for (int i{}; i < _rect_num; i++) {
        argument = _lower_lim + i * rect_length;
        fx = primordial_function(argument, _func_summation, _func_degree);
        area_sum += fx;
    }

    return (area_sum * rect_length);
}


void runBeta_1_5() {
    double lower_lim = 0.81, upper_lim = 1.762, bias = pow(10, -6);
    double integral_value;

    for (double s = 1.5; s <= 2.5; s += 0.5) {
        for (double t = 0; t <= 4; t++) {
            int n = 1, k_iter{};

            integral_value = rectangle_integral(lower_lim, upper_lim, n, t, s);

            while (fabs(integral_value - rectangle_integral(lower_lim, upper_lim, n + 1, t, s)) > bias) {
                // We turn to the recalculation of the integral to the desired accuracy
                integral_value = rectangle_integral(lower_lim, upper_lim, n, t, s);
                n *= 2;
                k_iter++;
            }

            printf("Integral value: %.6f, 'k_iter': %d, s: %.2f, t: %.2f \n", integral_value, k_iter, s, t);

        }
    }



}
