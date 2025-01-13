#include <config.h>

namespace CONSOLE {
	const HANDLE h_console = GetStdHandle(STD_OUTPUT_HANDLE);
	const unsigned char DEFAULT_COLOR = 7;

	void COLOR_OUT(std::string _text, const unsigned char _COLOR) {
		SetConsoleTextAttribute(h_console, _COLOR);

		LOG(INFO) << _text;

		SetConsoleTextAttribute(h_console, DEFAULT_COLOR);
	}

	void COLOR_OUT(std::string _text, std::string _color) {
		if (_color == "success" || _color == "SUCCESS") {
			SetConsoleTextAttribute(h_console, 10);

			LOG(INFO) << _text;
		}

		if (_color == "error" || _color == "ERROR") {
			SetConsoleTextAttribute(h_console, 12);

			LOG(INFO) << _text;
		}

		if (_color == "warning" || _color == "WARNING") {
			SetConsoleTextAttribute(h_console, 14);

			LOG(INFO) << _text;
		}

		SetConsoleTextAttribute(h_console, DEFAULT_COLOR);
	}

	void LOADING(const unsigned short _symbol_change_delay) {
		Sleep(_symbol_change_delay);
		std::cout << "\b\\" << std::flush;

		Sleep(_symbol_change_delay);
		std::cout << "\b|" << std::flush;

		Sleep(_symbol_change_delay);
		std::cout << "\b/" << std::flush;

		Sleep(_symbol_change_delay);
		std::cout << "\b-" << std::flush;
	}
}