#include "../headers/config.h"

/*
 * Perform task 2.4 using linked dynamic data structure "list" in the
 * form of arrays. Estimate asymptotic complexity of the algorithm.
 */

 // ─── TYPE AND FUNCTION INITIALIZATION ───────────────────────────────────────────

struct Char {
	string symbol = " ";
};

struct CharList {
	Char _data;
	CharList * _next = nullptr;
};


void printCharList_(CharList * _list, size_t _list_size, string _list_name);

void addFrontCharElement_(CharList ** _list, Char & _char);

// ────────────────────────────────────────────────────────────────────────────────


// ─── CORE FUNCTION ──────────────────────────────────────────────────────────────

void runBeta_2_5() {


	// ─── INITIALIZATION SECTION ─────────────────────────────────────────────────────

	const int CHAR_NUMBER = 128;

	int * chars_in_list = new int[CHAR_NUMBER];
	fill_n(chars_in_list, CHAR_NUMBER, 0);

	CharList * user_chars = NULL; user_chars = new CharList;


	CharList * repetetive_chars = NULL; user_chars = new CharList;


	CharList ** list_array = new CharList * [2];


	string user_input;

	cout << "Enter chars (without indents): "; getline(cin, user_input);

	Char buffer;
	unsigned int counter {};


	// ─── PROGRAM HOOK ───────────────────────────────────────────────────────────────

	for (unsigned int i {}; i < user_input.length(); i++) {
		buffer.symbol = user_input[i];
		chars_in_list[user_input[i]]++;
		addFrontCharElement_(&user_chars, buffer);
	}

	list_array[0] = user_chars;

	printCharList_(list_array[0], user_input.length(), "User input list");



	for (unsigned int i {}; i < CHAR_NUMBER; i++) {
		if (chars_in_list[i] > 1) {
			buffer.symbol = i;
			addFrontCharElement_(&repetetive_chars, buffer);
			counter++;
		}
	}

	list_array[1] = repetetive_chars;

	printCharList_(list_array[1], counter, "Repeating elements");


	// ─── CLEAR SECTION ──────────────────────────────────────────────────────────────

	delete[] chars_in_list;
	delete repetetive_chars, user_chars;

	cout << endl;
}

// ────────────────────────────────────────────────────────────────────────────────


// ─── FUNCTION DEFINITION ────────────────────────────────────────────────────────

void printCharList_(CharList * _list, size_t _list_size, string _list_name) {

	CharList * iterator = _list;

	cout << "\n" << _list_name << ":" << endl;

	for (unsigned int i {}; i < _list_size; i++) {
		cout << iterator->_data.symbol[0] << " " << flush;

		iterator = iterator->_next;
	}

}

void addFrontCharElement_(CharList ** _list, Char & _char) {

	CharList * iterator = new CharList;

	iterator->_data.symbol = _char.symbol;

	iterator->_next = *_list;

	*_list = iterator;

}

// ────────────────────────────────────────────────────────────────────────────────
