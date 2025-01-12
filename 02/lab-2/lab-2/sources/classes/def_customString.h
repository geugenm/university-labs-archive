#pragma once

#include "dec_customString.h"
#include "../../headers/config.h"
#include <easylogging++.h>

namespace cstr {
	class customString {
	private:
		std::vector<char> char_string;
		unsigned long long string_size = 0;
	public:
		explicit customString() noexcept {
			LOG(INFO) << "customString constructor : String successfully created";
		}

		explicit customString(char _symbol) noexcept {
			char_string.push_back(_symbol);
			string_size++;
			LOG(INFO) << "customString argument constructor : String successfully created";
		}

		~customString() {
			char_string.clear();
			string_size = 0;
			LOG(INFO) << "customString destructor : String successfully deleted";
		}

		//
		// ─── OPERATORS DEFINITION ────────────────────────────────────────
		//

		customString & operator = (customString _sample) noexcept {
			for (unsigned long long i {}; i < _sample.string_size; i++) {
				char_string.push_back(_sample.char_string[i]);
			}

			return *this;
		}

		friend std::istream & operator >> (std::istream & _in, customString & _object) {
			HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
			const unsigned char OUTPUT_COLOR = 13;
			SetConsoleTextAttribute(hConsole, OUTPUT_COLOR);

			std::cout << "Input a string (without spaces): ";

			std::string buffer;
			std::cin >> buffer;

			SetConsoleTextAttribute(hConsole, 7);

			for (unsigned long long i {}; i < buffer.length(); i++) {
				_object.char_string.push_back(buffer[i]);
				_object.string_size++;
			}

			return _in;
		}

		friend std::ostream & operator << (std::ostream & _out, const customString & _object) {
			const char delimiter = ' ';

			for (unsigned long long i {}; i < _object.string_size; i++) {
				_out << _object.char_string[i] << delimiter;
			}

			return _out;
		}

		friend bool operator == (const customString & _lhs, const customString & _rhs) {
			if (_lhs.string_size == _rhs.string_size) {
				for (unsigned long long i {}; i < _lhs.string_size; i++) {
					if (_lhs.char_string[i] != _rhs.char_string[i]) {
						return false;
					}
				}

				return true;
			}
			else {
				return false;
			}
		}

		//
		// ─── METHODS DECLARATION SECTION ─────────────────────────────────
		//

		void deleteSymbol(char _target_symbol);

		char getElementByIndex(unsigned long long _index);

		unsigned long long size() const;

		void print();

	};
}
