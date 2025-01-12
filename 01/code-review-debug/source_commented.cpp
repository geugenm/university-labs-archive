#include <iostream>
#include <iomanip>
#include <time.h>
#include <stdlib.h>

using namespace std;

/*
 * This code zeroes all repeated elements from the two-dimensional array, 
 * moving them to the end, while the unique elements are shifted to the 
 * positions of the zeroed elements
 * 
 * NOTE:
 * 	Matrices are set statically, which was one of the reasons for the
 * 	complete redesign of the program architecture
 */

int main() {
	setlocale(LC_ALL, "en_US.UTF-8");

	srand(time(NULL));

	int a[50][50], b[50][50] = { 0 }; // Two matrices are set, matrix 'b' is zeroed. 

	int n; // Initialization of the variable responsible for the matrix size

	cout << "Input matrix size:";
	cin >> n;

	for (int i = 0; i < n; i++) {
		// Filling the matrix with random numbers from '0' to '19'
		for (int j = 0; j < n; j++) {
			a[i][j] = rand() % 20; 
		}
	}
		
	for (int i = 0; i < n; i++) {
		// Duplication of matrix a by b
		for (int j = 0; j < n; j++) {
			b[i][j] = a[i][j];
		}
	}

	for (int i = 0; i < n; i++) {
		// Replacing the originally generated zeros (if any) with a number 
		// that cannot be in the matrix due to generation limitations
		for (int j = 0; j < n; j++) {
			if (b[i][j] == 0) {
				b[i][j] = 21;
			}
		}
	}

	int l = 0; // Replacement counter

	for (int i = 0; i < n; i++) {
		// Latching repetitive elements
		for (int j = 0; j < n - 1; j++) {
			for (int q = j + 1; q <= n; q++) {
				// Checking the row for repetition and zeros in caught elements
				if (b[i][j] == b[i][q]) {
					b[i][q] = 0; ;
					l++;
				}
			}
			if (l != 0) {
				// Zeroing the object to which we were comparing 
				b[i][j] = 0;
			}
			l = 0;
		}
		l = 0;
	}

	int e; // Zero counter

	for (int i = 0; i < n; i++) {
		// Dragging the zeroed element to the end
		for (int j = 0; j < n; j++) {
			if (b[i][j] == 0) {
				e = j;
				while (b[i][e] == 0) {
					// We stop at an element that is not equal to zero
					e++;
				}
				if (e > n) {
					e = n;
				}
				// Substitution of zero for a non-zero element
				b[i][j] = b[i][e]; 
				b[i][e] = 0;
			}
		}
	}

	for (int i = 0; i < n; i++) {
		// Outputs the initial matrix
		for (int j = 0; j < n; j++) {
			if (a[i][j] == 21) {
				// The replacement of initital '0' occurred in the matrix 'b'
				a[i][j] = 0;
			}
			cout << setw(3) << a[i][j];
		}
		cout << endl;
	}

	cout << "New matrix:" << endl;

	for (int i = 0; i < n; i++) {
		// Output of the modified matrix
		for (int j = 0; j < n; j++) {
			if (b[i][j] == 21) {
				b[i][j] = 0;
			}
			cout << setw(3) << b[i][j];
		}
		cout << endl;
	}
}

/* 
Brief conclusions about the code:
	1. Unintelligible variable names.

	2. The initial code had almost no indents which made it difficult to read the code itself, 
	so I had to perform partial refactoring even at the source.

	3. A lot of variables are defined outside the loop. We can insert variables into the loop itself and 
	just redefine them each iteration, instead of a separate zeroing operation.

	4. Memory handling. Arrays are statically defined + a large zeroed array is stored from the beginning,
	so we had to almost completely change the architecture of the program.

	5. Array output, even with substitutions, could be defined in one function.
	

	P.S. Code quality is too high, lower it to meet the industry standard =)
*/