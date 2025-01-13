#include <config.h>
#include <references.h>

#define VAR_NAME(name) #name

namespace TASK_2 {
	//
	// ────────────────────────────────────────────────────────────────────────── I ──────────
	//   :::::: M A T R I X   O P E R A T I O N S : :  :   :    :     :        :          :
	// ────────────────────────────────────────────────────────────────────────────────────
	//

	//! Matrix sum operation
	std::vector<std::vector<int>> matrixSum(std::vector<std::vector<int>> _matrix_A, std::vector<std::vector<int>> _matrix_B) {
		bool is_same_dimension = (_matrix_A.size() == _matrix_B.size()) && (_matrix_A[0].size() == _matrix_B[0].size());

		if (is_same_dimension) {
			std::vector<std::vector<int>> result(_matrix_A.size(), std::vector<int>(_matrix_A.size(), 0));

			for (unsigned long long i{}; i < _matrix_A.size(); i++) {
				for (unsigned long long j{}; j < _matrix_A[0].size(); j++) {
					result[i][j] = _matrix_A[i][j] + _matrix_B[i][j];
				}
			}
			return result;
		}
		else {
			return _matrix_A;
		}
	}

	//! Matrix multiplication operation
	std::vector<std::vector<int>> matrixMultiplication(std::vector<std::vector<int>> _matrix_A, std::vector<std::vector<int>> _matrix_B) {
		if (_matrix_A[0].size() == _matrix_B.size()) {
			std::vector<std::vector<int>> result(_matrix_A.size(), std::vector<int>(_matrix_A.size(), 0));

			for (unsigned long long i{}; i < _matrix_A.size(); i++) {
				for (unsigned long long j{}; j < _matrix_B[0].size(); j++) {
					for (unsigned long long k{}; k < _matrix_A[0].size(); k++) {
						result[i][j] += _matrix_A[i][k] * _matrix_B[k][j];
					}
				}
			}
			return result;
		}
		else {
			return _matrix_A;
		}
	}

	void showMatrix(std::vector <std::vector<int>> _matrix, std::string _matrix_name) {
		std::cout << "\n" << _matrix_name << std::endl;
		for (unsigned long long i{}; i < _matrix.size(); i++) {
			for (unsigned long long j{}; j < _matrix[0].size(); j++) {
				std::cout << _matrix[i][j] << " ";
			}
			std::cout << std::endl;
		}
		std::cout << std::endl;
	}

	//
	// ─── MATRIX OPERATIONS TEST ─────────────────────────────────────────────────────
	//

	void matrixOperations_Test() {
		unsigned long long user_matrix_size;
		std::cout << "Input matrix size: "; std::cin >> user_matrix_size;

		std::vector<std::vector<int>> matrix_A(user_matrix_size, std::vector<int>(user_matrix_size, 0));
		std::vector<std::vector<int>> matrix_B(user_matrix_size, std::vector<int>(user_matrix_size, 0));
		std::vector<std::vector<int>> matrix_C(user_matrix_size, std::vector<int>(user_matrix_size, 0));

		// Random matrix filling
		{
			std::random_device device;
			std::mt19937 range(device());
			std::uniform_int_distribution<int> distribution(0, 100);

			for (unsigned long long i{}; i < user_matrix_size; i++) {
				for (unsigned long long j{}; j < user_matrix_size; j++) {
					matrix_A[i][j] = distribution(range);
					matrix_B[i][j] = distribution(range);
					matrix_C[i][j] = distribution(range);
				}
			}
		}

		// Summation test
		showMatrix(matrix_A, VAR_NAME(matrix_A));
		showMatrix(matrix_B, VAR_NAME(matrix_B));

		std::vector<std::vector<int>> A_plus_B = matrixSum(matrix_A, matrix_B);
		showMatrix(A_plus_B, VAR_NAME(A_plus_B));

		CONSOLE::COLOR_OUT("Matrix summation test successfuly passed", "success");



		// Multiplication test
		showMatrix(matrix_C, VAR_NAME(matrix_C));
		std::vector<std::vector<int>> final_result = matrixMultiplication(matrix_C, A_plus_B);
		showMatrix(final_result, VAR_NAME(final_result));

		CONSOLE::COLOR_OUT("Matrix multiplication test successfuly passed", "success");



		ShellExecute(0, 0, L"https://matrixcalc.org/en/", 0, 0, SW_SHOW);

		CONSOLE::COLOR_OUT("Matrix Operations Test succesfully passed", "success");
	}


	//
	// ────────────────────────────────────────────────────────────────────────────────────────── II ──────────
	//   :::::: D Y N A M I C   M E M O R Y   A L L O C A T I O N : :  :   :    :     :        :          :
	// ────────────────────────────────────────────────────────────────────────────────────────────────────
	//

	void createFile(std::string _file_name, const int _max_array_number) {
		const unsigned long long GENERATED_INTEGERS_NUMBER = INT_MAX;

		std::random_device random_figure;
		std::mt19937 generate_figure(random_figure());
		std::uniform_int_distribution<int> distr(1, _max_array_number);

		std::ofstream UserFile(_file_name);

		std::cout << "Creating file. Please wait... " << '-' << std::flush;

		for (unsigned long long i{}; i < GENERATED_INTEGERS_NUMBER; i++) {
			// Ensures that application is active
			CONSOLE::LOADING(100);

			UserFile << distr(generate_figure) << " ";
		}

		UserFile.close();
	}

	void sortByDecrease_Test() {
		std::string file_name = "filename.txt";
		const unsigned short MAX_NUMBER = 10000;

		createFile(file_name, MAX_NUMBER); // Creates a file (already created 2.2 GB file)

		std::vector<bool> is_present(MAX_NUMBER + 1, false);

		// Reading file section
		std::ifstream UserFile(file_name, std::ios_base::in);

		for (unsigned short i{}, element; i < MAX_NUMBER; i++) {
			UserFile >> element;
			is_present[element] = true;
		}

		UserFile.close();


		// Array output section
		printf("Sorted part:\n");

		for (unsigned short j = MAX_NUMBER - 1; j > 0; j--) {
			if (is_present[j] == true) {
				std::cout << j << " ";
			}
		}

		std::cout << std::endl;
	}


}
