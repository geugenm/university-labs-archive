/*
 * Declare a class to solve the problem and define its methods.
 *
 * Implement:
 * - Three kinds of constructor (no arguments, initialize, copy),
 * - destructor,
 * - overload data input/output operations,
 * - Implement the operations specified in the task by overloading the operations.
 *
 * Place the class declaration in the header file, method definitions
 * in the second file, the definition of the main function of the program - in the third file.
 * Demonstrate the correct operation of all operations and methods of the implemented class.
 *
 *
 * 2. define a class to work with the "character string" object. Implement:
 * compare strings, remove a specified character from a string. Delete from the specified
 * all characters, which occur in the second specified string.
 */

#include "headers/config.h"
#include "classes/def_customString.h"

#include <easylogging++.h>

void runBeta_2_4() {
	cstr::customString user_string;
	cstr::customString symbols_to_delete;

	std::cin >> user_string;
	std::cin >> symbols_to_delete;

	for (unsigned long long i {}; i < symbols_to_delete.size(); i++) {
		user_string.deleteSymbol(symbols_to_delete.getElementByIndex(i));
	}

	user_string.print();
}