#include "../headers/config.h"

// A natural number n is given. Is it true that 
// this number contains exactly three identical digits.

void beta_2_1_1() {
	/* Local variables */
	int num, digit_repeat{}, num_size;

	cout << "n:"; cin >> num;

	num_size = trunc(log10(num)) + 1; // 'trunc' function is available from c++11

	// In order not to cause stack overflow, we create a dynamic array
	auto num_digits = make_unique<int[]>(num_size);
	
	for (int i{}; i <= num_size; i++) {
		num_digits[i] = num % 10;
		num /= 10;
	}

	for (int i{}; i < num_size; i++) {
		if (digit_repeat <= 3) {
			digit_repeat = 0;
		}
		for (int j{}; j <= i; j++) {
			if (num_digits[i] = num_digits[j]) {
				digit_repeat++;
			}
		}
	}

	if (digit_repeat >= 3) {
		cout << "There are 3 repeating digits in 'num'";
	}
	else { 
		cout << "There are no 3 repeating digits in 'num'"; 
	}
}
