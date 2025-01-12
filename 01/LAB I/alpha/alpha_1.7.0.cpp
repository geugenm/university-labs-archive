#include "../headers/config.h"

void alpha_source_1_7_0() {
	/* The field of a chessboard is determined by a pair of natural numbers,
	each of which does not exceed 8: the first is the number of the vertical,
	the second is the number of the horizontal.
	Natural numbers bishop_x, bishop_y, potential_x, potential_y are given. */

	/* Local variables */
	short int bishop_x, bishop_y, potential_x, potential_y;
	bool check_size;

	cout << "bishop x:"; cin >> bishop_x;
	cout << "bishop y:"; cin >> bishop_y;

	cout << "m:"; cin >> potential_x;
	cout << "n:"; cin >> potential_y;

	check_size = ((max(bishop_x, bishop_y) <= 8 && max(potential_x, potential_y) <= 8) && (min(bishop_x, bishop_y) >= 0)) && (min(potential_x, potential_y) >= 0);

	if (check_size == true) {
		if (bishop_x - (2 * bishop_x - potential_x) == bishop_y - (2 * bishop_y - potential_y)) { // positions differ by the same constant (e.g. (5,5) & (2,2), diff is 3)
			cout << "Alert! A piece threatened by a bishop!";
		}
		else {
			cout << "The piece is not in danger.";
		}
	}
	else {
		cout << "Wrong table size";
	}

}