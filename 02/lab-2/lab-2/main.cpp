#include <headers/references.h>
#include <headers/config.h>

#include <easylogging++.h>

INITIALIZE_EASYLOGGINGPP


int main(int argc, char * argv[]) {
	START_EASYLOGGINGPP(argc, argv);

	SetConsoleOutputCP(CP_UTF8);
	setvbuf(stdout, nullptr, _IOFBF, 1000);

	// Place execute function here
	runBeta_2_3();


	LOG(INFO) << "Program successfully ended";

	exit(0);
}