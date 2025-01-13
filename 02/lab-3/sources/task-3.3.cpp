#include <config.h>
#include <references.h>

namespace TASK_3 {
	void calculateExpression_Test() {
		unsigned long long argument_number;
		std::cout << "Input a number of variables: "; std::cin >> argument_number;

		std::list<double> user_list;

		std::random_device random_figure;
		std::mt19937 generate_figure(random_figure());
		std::uniform_real_distribution<double> distr(1.0, 12.0);


		for (unsigned long long i{}; i < argument_number; i++) {
			double a = distr(generate_figure);
			std::cout << a << std::endl;
			user_list.push_back(a);
		}

		std::cout << "-----------------" << std::endl;

		double result = 1;
		auto j = user_list.rbegin();

		for (auto i = user_list.begin(); i != user_list.end(); i++, j++) {
			std::cout << (*i + *j) << std::endl;
			result *= (*i + *j);
		}

		std::cout << "-----------------" << std::endl;

		std::cout << result << std::endl;

		CONSOLE::COLOR_OUT("calcualteExpresiion Test succesfully passed", "success");
	}
}
