#include "../headers/config.h"

auto beta_source_1_6_1() -> void {
	/* The number n is in unsigned char format. Output to the screen
	the values of bits 0 and 7 of the computer representation of this number.
	Explain the result. Invert bits 2 and 4. Print and explain the result. */

	/* Bits Check */
	uint8_t character;
	int32_t targeted_bit; // Aimed bit

	/* Initial values received from the user */
	std::cout << "[CHK]Target Bit: ";
	std::cin >> targeted_bit; // Bit position number

	std::cout << "Input a character: ";
	std::cin >> character; // Only a character [ASCII]


	/* Determining the bit value at a given position */
	targeted_bit = static_cast<int32_t>(pow(2, targeted_bit));// Transform 'chk_aim' to bin operation

	if ((character & targeted_bit) == targeted_bit) { // The condition starts counting on the right(starts from '0')!
		targeted_bit = static_cast<int32_t>(std::floor(log(targeted_bit) / log(2))); // Returns 'aim' to input value
		std::cout << "Bit" << targeted_bit << "is 1" << std::endl;
	}
	else {
		targeted_bit = static_cast<int32_t>(std::floor(log(targeted_bit) / log(2)));
		std::cout << "Bit" << targeted_bit << "is 0" << std::endl;
	}

	/* Bits Inversion */
	int64_t inversion_target;

	std::cout << "[INV]Target Bit: ";
	cin >> inversion_target;

	inversion_target = static_cast<int32_t>(std::floor(pow(2, inversion_target))); // Transform 'inv_aim' to bin operation

	cout << (((character ^ inversion_target) ^ (inversion_target / 2)) ^ (inversion_target / 2));

	/*
	Since the division is on the right side, using '^'
	we invert all the bits up to 'inv_aim - 1'. In order
	to get only one bit inverted as a result, we need
	to invert all the bits that come before the 'inv_aim - 1' bit.
	('inv_aim - 1' because {0, 1, 2, ..., 7})
	*/

}