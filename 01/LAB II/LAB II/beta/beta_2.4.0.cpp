#include "../headers/config.h"

/*
	* A sequence of integers is entered. Determine the 
	* number of elements in the longest subsequence of 
	* consecutive numbers ordered in ascending order.
	*/


void beta_2_4_0() {
	/* Local variables */
	long long sequence, sequence_size, repeat_coefficient{}, local_max{};

	cout << "Enter a sequence(Without Spaces):"; cin >> sequence;

	sequence_size = trunc(log10(sequence));

	auto sequence_elements = make_unique<int[]>(sequence_size);

	for (int i{}; i <= sequence_size; i++) { 
		/* Partitioning the sequence by elements into an array */
		sequence_elements[i] = sequence % 10;
		sequence /= 10;
	} /* The sequence is reversed into an array */

	for (int i{}, j{1}; i <= sequence_size; j++, i++) {
		if (sequence_elements[i] >= sequence_elements[j]) {
			repeat_coefficient += 1;
			local_max = max(local_max, repeat_coefficient + 1);
		} 
		else {
			if (sequence_elements[i] < sequence_elements[j]) {
				repeat_coefficient = 0;
			}	
		}
	}

	printf("Maximum number of increases or repetitions of the sequence is %d", int(local_max));

	
	exit(0);
}
