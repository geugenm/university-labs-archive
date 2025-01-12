#include "../headers/config.h"

/**
	* Calculate the value of a polynomial for a given n 
	* at the points xi [x0; xm] (xi = x0 + idx, i = 0, 1, ...) 
	* in two ways: by summing the elements in increasing degree x 
	* and by the Gorner scheme. Count the number of addition 
	* and multiplication operations in both cases.
	*/

void beta_2_6_0() {
	/* Local variables */
	double delta_x{ 0.5 }, zero_x{ 1.0 }, current_x{}, max_x{ 5.0 }, n, local_sum{}, global_sum{};
	int multi_amount{}, sum_amount{};

	cout << "n:"; cin >> n;


	for (double i{}; current_x < max_x; i++) {
		current_x = zero_x + i * delta_x;

		for (double j{ 1.0 }; j <= n; j++) {
			local_sum += j * pow(current_x, 2 * j - 1);
			multi_amount += 2 * j - 1; // Degrading and multiplication by a factor
			sum_amount += 2; // Subtraction as a special case of the sum
		}

		sum_amount++; // '+ 5' int the end
		global_sum += local_sum + 5;
		printf("The local sum is %d for x = %d.%d \n", int(local_sum + 5), int(current_x), int(current_x * 10.0) % 10);
		local_sum = 0.0;
	}
	cout << "Global sum is " << global_sum << endl;
	printf("Total sum operations: %d, total multiplication operations: %d", multi_amount, sum_amount);
	
}

void beta_2_6_0_gorner() {
	/* Local variables */
	double delta_x{ 0.5 }, zero_x{ 1.0 }, current_x{}, max_x{ 5.0 }, n, local_sum{}, global_sum{};
	int multi_amount{}, sum_amount{};

	cout << "n:"; cin >> n;

	for (double i{}; current_x < max_x; i++) {
		current_x = zero_x + i * delta_x;

		for (double j{}, k{2 * n}; j <= (n); j++, k -= 2) {
			local_sum += 1 / current_x * ((n - j) * pow(current_x, k));
			multi_amount += k + 2; // Degrading and multiplication by a factor
			sum_amount += 1; // Subtraction as a special case of the sum
		}

		sum_amount++; // '+ 5' int the end
		global_sum += local_sum + 5.0;
		printf("The local sum is %d for x = %d.%d \n", int(local_sum + 5), int(current_x), int(current_x * 10.0) % 10);
		local_sum = 0.0;
	}

	cout << "Global sum is " << global_sum << endl;
	printf("Total sum operations: %d, total multiplication operations: %d", multi_amount, sum_amount);
}
