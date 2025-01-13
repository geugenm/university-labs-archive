/*
 *
 * Perform the following task for the given text. Formulate the task as a
 * As a set of functions: function for creating an array of words, function 
 * for getting the resulting string.
 * 
 * Text is a non-empty sequence of characters.
 * 
 * Word - a non-empty sequence of any characters, except for delimiters.
 * 
 * Sentence - a sequence of words separated by one or more delimiter characters.
 * 
 * Separator characters: "space", ".", ",", ":", ";", "!", "?", "-", "(", ")".
 *
 */

#include "../headers/config.h"



string getSymbols(string word_buffer) {
	/* Alphabet includes all ASCII symbols */
	string result;
	for (int i = 0; i < 127; i++) {
		for (int j = 0; j < word_buffer.length(); j++) {
			if (word_buffer[j] == i) {
				result += i;
				break;
			}
		}
	}

	sort(result.begin(), result.end());
	return result;
}

string getNextWord(string _target, string _delimiter, int *_start_position) {
	string next_word;
	for (int i = *_start_position - 1; i < _target.length(); i++) {
		for (int j{}; j < _delimiter.length(); j++) {
			if (_target[i] == _delimiter[j]) {
				for (int m{}; m < _delimiter.length(); m++) {
					/* Going to the last delimiter before a letter */
					while (_target[i] == _delimiter[m]) {
						m = 0; i++;
					}
				}
				*_start_position = i;
				return next_word;
			}
		}
		next_word += _target[i];
	}
	// It's impossible to got here, just for debugging
	return "<getNextWord_function_error>";
}

void runBeta_1_2() {
	string delimiter = " .,:;!?-()";

	string user_input;
	getline(cin, user_input);
	user_input += " ";

	string result;
	int counter{};

	vector <int> storage;

	bool is_found_equal_word = 0;

	string word_buffer;

	for (int i{}; i < user_input.length(); i++) {
		counter = i;
		for (int j{}; j < delimiter.length(); j++) {
			if (user_input[i] == delimiter[j]) {
				/* If got a delimiter */
				int start_position{};

				for (int m{}; m < delimiter.length(); m++) {
					/* Going to the last delimiter before a letter */
					while (user_input[i] == delimiter[m]) {
						m = 0; i++;
					}
				}
				
				for (int k = i; k < user_input.length(); k++) {
					/* Comparing the word_buffer with other words from 'user_input' */
					start_position = k;
					string next_string = getNextWord(user_input, delimiter, &k);
					if (getSymbols(next_string) == getSymbols(word_buffer)) {
						is_found_equal_word = 1;
						for (int s{}; s < storage.size(); s++) {
							/* Checking if the word was already mentioned */
							if (storage[s] == start_position) {
								goto statement_end;
							}
						}
						result += next_string + " ";
					statement_end:;
						storage.push_back(start_position);
					}
				}

				/* A whole block of adding 'word_buffer' */
				for (int s{}; s < storage.size(); s++) {
					if (storage[s] == counter - word_buffer.length() + 1) {
						goto clear;
					}
				}
				if (is_found_equal_word) {
					/* Insetring 'word_buffer' in 'result' if it was not proceed before */
					result += word_buffer + " ";
				}
			clear:;
				is_found_equal_word = 0;
				word_buffer.clear();
			}
		}
		word_buffer += user_input[i];
	}

	cout << endl << result << endl;

}