#include "../headers/config.h"

// Determine the sum of the first 'post_dot_count' digits of the 
// fractional part of a given positive real number.

void beta_2_1_2() {
	/* Local variables */
	double num;
	long long int post_dot_count, sum{}, i{}, size;

	cout << "number:"; cin >> num;
	cout << "post_dot_count:"; cin >> post_dot_count;

	size = trunc(log10(num)) + 1;

	num -= trunc(num);
	cout << num << endl;

	for (double i = 0; i <= post_dot_count - 1; i++) {
		num *= 10.0;
	}

	while (i <= size + 1) {
		sum = sum + int(num) % 10;
		num /= 10.0;
		i++;
	}

	cout << (sum) << endl;
}