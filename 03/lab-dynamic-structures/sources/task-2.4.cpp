#include "../headers/config.h"

/*
 * Defines a function that generates a character list L2, including
 * those characters from L1 that enter it more than once.
 */



 // ─── TYPE AND FUNCTION INITIALIZATION ───────────────────────────────────────────

struct Char {
	string symbol = " ";
};

struct CharList {
	Char _symbol;
	CharList * _next = nullptr;
};


void printCharList(CharList * _list, size_t _list_size, string _list_name);

void addFrontCharElement(CharList ** _list, Char & _char);

// ────────────────────────────────────────────────────────────────────────────────



// ─── CORE FUNCTION ──────────────────────────────────────────────────────────────

void runBeta_2_4() {


	// ─── INITIALIZATION SECTION ─────────────────────────────────────────────────────

	const int CHAR_NUMBER = 128;

	int * chars_in_list = new int[CHAR_NUMBER];
	fill_n(chars_in_list, CHAR_NUMBER, 0);

	CharList * user_chars = NULL; user_chars = new CharList;


	CharList * repetetive_chars = NULL; user_chars = new CharList;


	string user_input;

	cout << "Enter chars (without indents): "; getline(cin, user_input);

	Char buffer;
	unsigned int counter {};


	// ─── PROGRAM HOOK ───────────────────────────────────────────────────────────────

	for (unsigned int i {}; i < user_input.length(); i++) {
		buffer.symbol = user_input[i];
		chars_in_list[user_input[i]]++;
		addFrontCharElement(&user_chars, buffer);
	}


	printCharList(user_chars, user_input.length(), "User input list");
	delete user_chars;


	for (unsigned int i {}; i < CHAR_NUMBER; i++) {
		if (chars_in_list[i] > 1) {

			buffer.symbol = i;
			cout << buffer.symbol << endl;
			addFrontCharElement(&repetetive_chars, buffer);
			counter++;
		}
	}

	printCharList(repetetive_chars, counter, "Repeating elements");


	// ─── CLEAR SECTION ──────────────────────────────────────────────────────────────

	delete & buffer, repetetive_chars;
	delete[] chars_in_list;

	cout << endl;
}

// ────────────────────────────────────────────────────────────────────────────────


// ─── FUNCTION DEFINITION ────────────────────────────────────────────────────────

void printCharList(CharList * _list, size_t _list_size, string _list_name) {

	CharList * iterator = _list;

	cout << "\n" << _list_name << ":" << endl;

	for (unsigned int i {}; i < _list_size; i++) {
		cout << iterator->_symbol.symbol[0] << " " << flush;

		iterator = iterator->_next;
	}

}

void addFrontCharElement(CharList ** _list, Char & _char) {

	CharList * iterator = new CharList;

	iterator->_symbol.symbol = _char.symbol;

	iterator->_next = *_list;

	*_list = iterator;

}

// ────────────────────────────────────────────────────────────────────────────────