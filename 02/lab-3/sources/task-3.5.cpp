#include <config.h>
#include <references.h>
using namespace std;

namespace TASK_5 {
	//
	// ────────────────────────────────────────────────────────────────────────────── I ──────────
	//   :::::: A U X I L I A R Y   F U N C T I O N S : :  :   :    :     :        :          :
	// ────────────────────────────────────────────────────────────────────────────────────────
	//

	void replaceSymbol(std::string & _text, char _target, char _replacement) {
		std::ranges::replace(_text.begin(), _text.end(), _target, _replacement);
	}

	void removeComment(std::string & _target) {
		std::size_t comment_position = _target.find("//");
		if (comment_position != std::string::npos) {
			_target.erase(comment_position, _target.length() - comment_position);
		}
	}

	void eraseAllSubStrings(std::string & _text, const std::string_view & _target) {
		size_t target_position = std::string::npos;

		while ((target_position = _text.find(_target)) != std::string::npos) {
			std::size_t next_target_mention = _text.find(_target, target_position + 1);

			if (target_position != std::string::npos && next_target_mention != std::string::npos) {
				_text.erase(target_position, next_target_mention - target_position + 1);
			}
		}
	}

	void eraseMiscellaneous(std::string & _string) {
		const std::string SPECIALS = "*,:#!&?(){}=+-;|<>[]\t";

		for (unsigned i{}; i <= SPECIALS.length(); i++) {
			replaceSymbol(_string, SPECIALS[i], ' ');
		}

		eraseAllSubStrings(_string, "\"");
		eraseAllSubStrings(_string, "'");
		removeComment(_string);
	}

	//
	// ────────────────────────────────────────────────────────────────────────────────────── II ──────────
	//   :::::: R E G E X   V A R I A B L E   A N A L Y Z E R : :  :   :    :     :        :          :
	// ────────────────────────────────────────────────────────────────────────────────────────────────
	//

	std::string verifyIdentifier(std::string const & _identifier) {
		std::string prerequisite = "\\b[_a-z]+[[:alnum:]]*\\b";
		std::regex reg(prerequisite, std::regex::icase);
		std::smatch sm;

		const std::string FILE_NAME = "lexer/excluded_words.txt";
		std::ifstream file(FILE_NAME);

		std::string excluded_word_buffer;
		if (std::regex_search(_identifier, sm, reg)) {
			while (file >> excluded_word_buffer) {
				if (excluded_word_buffer == _identifier) {
					return "";
				}
			}
			return sm.str();
		}

		return "";
	}

	//
	// ────────────────────────────────────────────────────────────────── III ──────────
	//   :::::: S T I T C H   P A R S E R : :  :   :    :     :        :          :
	// ────────────────────────────────────────────────────────────────────────────
	//

	void getLineWords(std::ifstream & _current_file, std::map<std::string, std::string, std::less<>> & _map) {
		std::string code_line;
		unsigned current_line{};

		while (std::getline(_current_file, code_line)) {
			eraseMiscellaneous(code_line);
			std::cout << code_line << std::endl;

			istringstream filling_stream(code_line);
			std::string word_buffer;

			while (filling_stream >> word_buffer) {
				_map[verifyIdentifier(word_buffer)].append(std::to_string(current_line) + " ");
			}

			current_line++;
		}
	}

	//
	// ────────────────────────────────────────────────────────────────────────────────────────────── IV ──────────
	//   :::::: P R O G R A M   H O O K   A N D   U N I T   T E S T S : :  :   :    :     :        :          :
	// ────────────────────────────────────────────────────────────────────────────────────────────────────────
	//

	void analyzeCode(const std::string & _file_name) {
		std::ifstream file(_file_name);

		if (file.is_open()) {
			std::map<std::string, std::string, std::less<>> variables_map;

			getLineWords(file, variables_map);

			file.close();

			variables_map.erase("");

			for (auto it = variables_map.begin(); it != variables_map.end(); ++it) {
				std::cout << it->first << " => " << it->second << '\n';
			}
		}
		else {
			CONSOLE::COLOR_OUT("analyzeCode() : File " + _file_name + " is not opened", "ERROR");
		}
	}


	void lexicalAnalyzer_Test() {
		const std::string FILE_NAME = "lexer/source.cpp";

		analyzeCode(FILE_NAME);
		std::cout << std::endl;

		CONSOLE::COLOR_OUT("lexicalAnalyzer Test : successfully passed", "SUCCESS");
	}
}