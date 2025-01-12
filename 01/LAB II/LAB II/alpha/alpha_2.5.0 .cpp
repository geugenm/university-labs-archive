#include "../headers/config.h"

void alpha_2_5_0() {
	/* Enter a natural number n from the keyboard. 
	Determine all ways to pay out the sum n with bills
	of 1, 5, 10, 20 and 100 conventional units */

	/* Local variables */
	int n;

	cout << "n:"; cin >> n;

	while (n != 0) {
		if (n >= 100) {
			cout << "100 ";
			n -= 100;
		}
		else if (n >= 20) {
			cout << "20 ";
			n -= 20;
		}
		else if (n >= 10) {
			cout << "10 ";
			n -= 10;
		}
		else if (n >= 5) {
			cout << "5 ";
			n -= 5;
		}
		else if (n >= 1) {
			cout << "1 ";
			n -= 1;
		}
	}

}