#include "../Headers/InitPythonScript.h"

void Execute(const std::filesystem::path &pythonScriptPath) {
    if (is_empty(pythonScriptPath)) {
        throw std::invalid_argument("Wrong script file path given");
    }

    if (pythonScriptPath.extension() != ".py") {
        throw std::invalid_argument("Python script expected");
    }

    std::string command("../venv/Scripts/python.exe ");
    command.append(pythonScriptPath);

    system(command.c_str());
}

std::string ReadConsoleOutput(const char *cmd) {
    std::array<char, 128> buffer{};
    std::string result;

    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd, "r"), &pclose);

    if (!pipe) {
        throw std::invalid_argument("popen() profiling failed!");
    }

    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }

    return result;
}
