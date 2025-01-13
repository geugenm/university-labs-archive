#include <config.h>
#include <references.h>

INITIALIZE_EASYLOGGINGPP


int main(int argc, char * argv[]) {
	START_EASYLOGGINGPP(argc, argv);

	SetConsoleOutputCP(CP_UTF8);
	setvbuf(stdout, nullptr, _IOFBF, 1000);

	// Place executable function here
	TASK_4::calculateAlgebraicExpression();
	//TASK_5::lexicalAnalyzer_Test();

	CONSOLE::COLOR_OUT("Program successfully ended", "success");

	exit(0);
}