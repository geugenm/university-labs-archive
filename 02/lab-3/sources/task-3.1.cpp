#include <config.h>
#include <references.h>

namespace TASK_1 {
	//
	// ──────────────────────────────────────────────────────────────────────────────────────────── I ──────────
	//   :::::: D E C I M A L   T O   R O M A N   C O N V E R T E R : :  :   :    :     :        :          :
	// ──────────────────────────────────────────────────────────────────────────────────────────────────────
	//

	std::string decimalToRoman(short _item) {
		std::string M[] = { "", "M", "MM", "MMM" };

		std::string C[] = { "",  "C",  "CC",  "CCC",  "CD", "D", "DC", "DCC", "DCCC", "CM" };

		std::string X[] = { "",  "X",  "XX",  "XXX",  "XL", "L", "LX", "LXX", "LXXX", "XC" };

		std::string I[] = { "",  "I",  "II",  "III",  "IV", "V", "VI", "VII", "VIII", "IX" };

		std::string thousands = M[_item / 1000];
		std::string hundreds = C[(_item % 1000) / 100];
		std::string tens = X[(_item % 100) / 10];
		std::string ones = I[_item % 10];

		return (thousands + hundreds + tens + ones);
	}

	void romeConverter_Test() {
		unsigned short number_count;
		short random_min;
		short random_max;

		std::cout << "Random minimum: "; std::cin >> random_min;
		std::cout << "Random maximum: "; std::cin >> random_max;
		std::cout << "Number count: "; std::cin >> number_count;

		std::random_device device;
		std::mt19937 range(device());
		std::uniform_int_distribution<short> distribution(random_min, random_max);

		for (unsigned short i{}; i < number_count; i++) {
			short temp = distribution(range);
			std::cout << "Decimal: " << temp << " Roman: " << decimalToRoman(temp) << std::endl;
		}

		// Just opens a website in order to immediately check the output
		ShellExecute(0, 0, L"https://www.browserling.com/tools/decimal-to-roman", 0, 0, SW_SHOW);

		CONSOLE::COLOR_OUT("romeConverter Test : succesfully passed", "success");
	}


	//
	// ──────────────────────────────────────────────────────────────────────────────── II ──────────
	//   :::::: H E X   T O   B I N   C O N V E R T E R : :  :   :    :     :        :          :
	// ──────────────────────────────────────────────────────────────────────────────────────────
	//

	void outHexToBin(std::string _item) {
		for (unsigned long long i{}; i < _item.length(); i++) {
			switch (_item[i]) {
				case '0':
					std::cout << "0000";
					break;
				case '1':
					std::cout << "0001";
					break;
				case '2':
					std::cout << "0010";
					break;
				case '3':
					std::cout << "0011";
					break;
				case '4':
					std::cout << "0100";
					break;
				case '5':
					std::cout << "0101";
					break;
				case '6':
					std::cout << "0110";
					break;
				case '7':
					std::cout << "0111";
					break;
				case '8':
					std::cout << "1000";
					break;
				case '9':
					std::cout << "1001";
					break;
				case 'A':
				case 'a':
					std::cout << "1010";
					break;
				case 'B':
				case 'b':
					std::cout << "1011";
					break;
				case 'C':
				case 'c':
					std::cout << "1100";
					break;
				case 'D':
				case 'd':
					std::cout << "1101";
					break;
				case 'E':
				case 'e':
					std::cout << "1110";
					break;
				case 'F':
				case 'f':
					std::cout << "1111";
					break;
				default:
					std::cout << "<Unknown_symbol>" << _item[i];
					CONSOLE::COLOR_OUT("hexToBin() | Unknown_symbol" + _item[i], "warning");
			}
		}
	}

	// Randomly generates hex and converts, no user input required
	void hexToBin_Test() {
		unsigned short number_count;

		std::cout << "Input number count: "; std::cin >> number_count;

		// Random hex generator
		{
			std::random_device device;
			std::mt19937 range(device());
			std::uniform_int_distribution<unsigned short> hex_number_size(1, 5);

			std::uniform_int_distribution<unsigned long long> isLetter(0, 1);
			std::uniform_int_distribution<unsigned short> letter(65, 70);
			std::uniform_int_distribution<unsigned short> figure(49, 57);


			for (unsigned i{}; i < number_count; i++) {

				unsigned short size = hex_number_size(range);
				std::string random_hex(size, '0');

				for (unsigned j{}; j < size; j++) {
					bool symbol = isLetter(range);
					if (symbol == true) {
						random_hex[j] = letter(range);
					}
					else {
						random_hex[j] = figure(range);
					}

				}

				std::cout << "Hex: " << random_hex << " Bin: ";
				outHexToBin(random_hex);
				std::cout << std::endl;

			}

		}

		ShellExecute(0, 0, L"https://www.rapidtables.com/convert/number/hex-to-binary.html", 0, 0, SW_SHOW);

		CONSOLE::COLOR_OUT("hexToBin Test : succesfully passed", "success");
	}


	//
	// ──────────────────────────────────────────────────────────────────────────────────────────────────────── III ──────────
	//   :::::: F I N D   W O R D S   W I T H   T H E   S A M E   L E T T E R S : :  :   :    :     :        :          :
	// ──────────────────────────────────────────────────────────────────────────────────────────────────────────────────
	//

	std::string uniqueSymbols(std::string _word) {
		std::string result = "";
		std::vector<bool> containChar;

		for (char i{}; i < CHAR_MAX; i++) {
			containChar.push_back(false);
		}

		for (unsigned long long i{}; i < _word.length() + 1; i++) {
			containChar[_word[i]] = true;
		}

		for (char i{}; i < CHAR_MAX; i++) {
			if (containChar[i] == true) {
				result.push_back(i);
			}
		}

		return result;
	}

	bool isDelimiter(std::string _sentence, std::string _delimiter, long long & _iterator, bool _read_from_end) {
		bool gotDelimiter = false;
		for (unsigned long long j{}; j <= _delimiter.length(); j++) {
			if (_iterator >= 0 && _sentence[_iterator] == _delimiter[j]) {
				gotDelimiter = true;
				j = 0;
				if (_read_from_end == true) {
					_iterator--;
				}
				else {
					_iterator++;
				}

			}
		}
		return gotDelimiter;
	}

	std::string lastWord(std::string _sentence, std::string _delimiter) {
		long long i = _sentence.length();
		std::string last_word = "";

		bool hasEndDelimiter = (isDelimiter(_sentence, _delimiter, i, true));

		for (; i >= 0; i--) {
			if (isDelimiter(_sentence, _delimiter, i, true)) {
				return last_word;
			}
			last_word.push_back(_sentence[i]);
		}
		return last_word;
	}

	void wordsWithTheSameLetters(std::string _sentence) {
		std::string delimiter = " .,:;!?-()";
		std::string last_word = lastWord(_sentence, delimiter);

		std::string buffer = "";

		for (long long i{}; i <= _sentence.length() - last_word.length(); i++) {
			if (isDelimiter(_sentence, delimiter, i, false)) {
				if (uniqueSymbols(buffer) == uniqueSymbols(last_word)) {
					std::cout << buffer << std::endl;
				}

				buffer.clear();
			}

			buffer.push_back(_sentence[i]);
		}

	}

	void wordsWithTheSameLetters_Test() {
		std::string user_input;
		std::cout << "Input a sentence: "; std::cin >> user_input;

		wordsWithTheSameLetters(user_input);

		CONSOLE::COLOR_OUT("wordsWithTheSameLetters Test : succesfully passed", "success");
	}
}

