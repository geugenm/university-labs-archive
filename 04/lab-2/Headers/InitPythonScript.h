#pragma once

#include <filesystem>
#include <string>

#include <iostream>
#include <stdexcept>

#include <cstdio>


void Execute(const std::filesystem::path & pythonScriptPath = "../Sources/NewtonsMethod.py");

[[nodiscard]] std::string ReadConsoleOutput(const char* cmd);
