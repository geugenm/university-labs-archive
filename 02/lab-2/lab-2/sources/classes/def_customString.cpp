#include "def_customString.h"
#include "../../headers/config.h"

//
// ─── CUSTOMSTRING METHODS ───────────────────────────────────────────────────────
//

void cstr::customString::deleteSymbol(char _target_symbol) {
	// Copying the initial string into buffer without '_target_symbol'
	customString buffer;
	for (unsigned long long i {}; i < customString::string_size; i++) {
		if (char_string[i] != _target_symbol) {
			buffer.char_string.push_back(char_string[i]);
			buffer.string_size++;
		}
	}

	if (buffer.string_size == string_size) {
		return;
	}

	char_string.clear();
	string_size = 0;

	// Replacing the initital with modified one, without '_target_symbol' (buffer)
	for (unsigned long long i {}; i < buffer.string_size; i++) {
		char_string.push_back(buffer.char_string[i]);
	}

	string_size = buffer.string_size;

	LOG(INFO) << "deleteSymbol() : Symbol '" << _target_symbol << "' successfully deleted";
}

char cstr::customString::getElementByIndex(unsigned long long _index) {
	return char_string[_index];
}

void cstr::customString::print() {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	const unsigned char OUTPUT_COLOR = 9;
	SetConsoleTextAttribute(hConsole, OUTPUT_COLOR);

	for (unsigned long long i {}; i < string_size; i++) {
		std::cout << char_string[i] << " ";
	}

	SetConsoleTextAttribute(hConsole, 7);
	std::cout << std::endl;
}

unsigned long long cstr::customString::size() const {
	return string_size;
}