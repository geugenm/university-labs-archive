#pragma once

#ifndef _PROJECT_REFERENCES
#define _PROJECT_REFERENCES

namespace CONSOLE {
	void COLOR_OUT(std::string, const unsigned char);
	void COLOR_OUT(std::string, std::string);
	void LOADING(const unsigned short);
}

namespace TASK_1 {
	void romeConverter_Test();
	void hexToBin_Test();
	void wordsWithTheSameLetters_Test();
}

namespace TASK_2 {
	void matrixOperations_Test();
	void sortByDecrease_Test();
}

namespace TASK_3 {
	void calculateExpression_Test();
}

namespace TASK_4 {
	void calculateAlgebraicExpression();
}

namespace TASK_5 {
	void lexicalAnalyzer_Test();
}

#endif