#include "../headers/config.h"

void alpha_source_1_2_1() {
	/* Assign the integer variable 'sum' to the sum
	of the digits of a natural number 'num'. */

	int64_t user_number;

	std::cout << "Input any integer: ";
	std::cin >> user_number;

	const uint64_t number_size = static_cast<uint64_t>(trunc(log10(user_number))) + 1;

	uint64_t digit_amount = 0;
	uint64_t number_bit_sum = 0;

	while (digit_amount <= number_size) {
		constexpr uint64_t notation_base = 10;

		number_bit_sum = number_bit_sum + user_number % 10;
		user_number = user_number / static_cast<int64_t>(notation_base);
		digit_amount++;
	}

	cout << "The result is: " << number_bit_sum << std::endl;
}