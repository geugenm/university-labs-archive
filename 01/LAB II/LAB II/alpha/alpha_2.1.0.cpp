#include "../headers/config.h"

void alpha_2_1_0() {
	/* Find the sum of the first n natural numbers that are divisible by 3 */

	/* Local variables */
	int num_count, sum{};

	cout << "n:"; cin >> num_count;

	for (int i{}; i <= num_count; i++) {
		switch (i % 3) {
		case 0:
			sum += i;
		}
			
	}

	printf("The sum is %d", sum);

}