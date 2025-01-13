#pragma once

#include <string>

#ifndef CONSOLE_OUT_MACRO
#define CONSOLE_OUT_MACRO

namespace CONSOLE {
	void COLOR_OUT(const std::string &, const unsigned char);
	void COLOR_OUT(const std::string &, const std::string &);

	void LOADING(const unsigned short);
}

#endif