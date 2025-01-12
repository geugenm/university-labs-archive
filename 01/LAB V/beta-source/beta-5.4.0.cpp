/*
 * Here we write a function to replace a substring S1 
 * (given by the position of the first character and the number of characters) 
 * with a substring S2 in the string S.
 * Using this function, we compress a given string, i.e. we replace any series of
 * consecutive characters by (k)s, where s is a repeated character, and k is the number of its repetitions.
 */

/// \TODO:
/// 1. Refactor the code
/// (Additional): 2. Support for space delimiters


#define _CRT_SECURE_NO_WARNINGS 1

#include "../headers/config.h"


void replaceChar(char* source, char target[], char substitution[], char buffer[]) {
	int i, j, position = 0;
	for (i = 0; source[i]; i++) {
		for (j = 0; source[i + j] && target[j]; j++) {   //начинается ли с i-ой позиции строка a
			if (source[i + j] != target[j]) {
				break;
			}
		}
		if (!target[j]) {
			i += j - 1;  //в j у нас длина стоки a, которую мы перепрыгиваем
			for (j = 0; substitution[j]; j++) {
				buffer[position++] = substitution[j]; //на место стоки a ставим строку b
			}
		}
		else {
			buffer[position++] = source[i];   //просто копируем символ
		}
		buffer[position] = '\0';  //ставим конец строки
	}
	strcpy(source, buffer);  //копируем в первоначальную строку
}

void runBeta_5_4_0() {
	int max_input_len = 128, char_counter{};
	
	char* temp = new char[max_input_len];

	char* buffer = new char[max_input_len];

	char* user_string = new char[max_input_len];

	cin >> user_string;

	for (int i{}; user_string[i] != '\0'; i++) {

		// Template for replacement
		char quantity_template[] = "(<amount>)<symbol>";
		char amount[] = "<amount>";
		char symbol[] = "<symbol>";

		if (user_string[i] == user_string[i + 1]) {
			// Add all the repeating elements to the temporary char
			temp[char_counter] = user_string[i];
			char_counter++;

			if (user_string[i + 1] != user_string[i + 2]) {

				temp[char_counter] = user_string[i];
				temp[char_counter + 1] = '\0';
 
				char* insert_amount = new char[2]; {
					// Converts the number of repetitions from 'int' to 'char'
					insert_amount[0] = char_counter + 49;
					insert_amount[1] = '\0';
					replaceChar(quantity_template, amount, insert_amount, buffer);
				}
				
				
				char* insert_symbol = new char[2]; {
					// Converts a single character into a single line
					insert_symbol[0] = user_string[i];
					insert_symbol[1] = '\0';
					replaceChar(quantity_template, symbol, insert_symbol, buffer);
				}

				replaceChar(user_string, temp, quantity_template, buffer);

				char_counter = 0;
			}
		}
		
	}

	printf("%s", user_string);

	exit(0);
}