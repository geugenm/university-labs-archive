#include "../headers/config.h"


int _SUM_ACCUMULATION(int iterator) {
	int input_x;
	int sum_accumulation{};
	for (int j{0}; j <= iterator - 1; j++) {
		printf("Enter x%d value:", iterator + j); cin >> input_x;
		sum_accumulation += input_x;
	}
	cout << sum_accumulation << endl; // Debugging cout of sum
	return sum_accumulation;
}

void alpha_2_7_0() {
	/* Enter a natural number n, integers x1, x2, ..., xn. */

	/* Local variables */
	int n, interim_sum{}, expression_value{1};

	cout << "n:"; cin >> n;
	n -= 1; // Calculating starts from zero-element

	for (int i{1}; i <= n; i++) {
		expression_value = expression_value * _SUM_ACCUMULATION(i);
	}

	cout << expression_value;

}