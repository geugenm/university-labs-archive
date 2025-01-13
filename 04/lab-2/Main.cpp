#include <iostream>
#include "Headers/InitPythonScript.h"

int main(const int argc, char* argv[]) {
    setvbuf(stdout, nullptr, _IOFBF, 1024);

    Execute();
    return 0;
}
