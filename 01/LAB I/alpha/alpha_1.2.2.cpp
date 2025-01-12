#include <string>

#include "../headers/config.h"

void alpha_source_1_2_2() {
	/* Determine if there is a digit 5 among the first four digits
	of the fractional part of a given positive real number. */

	constexpr uint64_t digits_amount = 4;
	constexpr uint64_t notation_base = 10;

	constexpr uint64_t target_digit = 5;

	double user_number;

	std::cout << "Input number: ";
	std::cin >> user_number;

	const double fractional_part = user_number - std::floor(user_number);
	uint64_t powered_fractal_part = static_cast<int64_t>(fractional_part * pow(notation_base, digits_amount));

	for (uint64_t i = 0; i <= digits_amount; i++) {
		if (powered_fractal_part % notation_base == target_digit) {
			std::cout << std::to_string(target_digit) + " is found" << std::endl;
			break;
		}
		else {
			powered_fractal_part = powered_fractal_part / notation_base;
		}
	}
}