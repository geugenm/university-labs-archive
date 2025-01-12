#include "../headers/config.h"
#include <list>

void beta_source_1_3_1() {
	/* Execute the task in two ways:
	using the if statement and using the conditional operator ? */

	/* Local variables */
	double x, y, z;

	cout << "x:"; cin >> x;
	cout << "y:"; cin >> y;
	cout << "z:"; cin >> z;


	std::list <double> sort_list = { x, y, z };

	sort_list.sort();

	x = sort_list.front(); sort_list.pop_front();
	y = sort_list.front();
	z = sort_list.back();

	cout << "x: " << x << endl;
	cout << "y: " << y << endl;
	cout << "z: " << z << endl;
}