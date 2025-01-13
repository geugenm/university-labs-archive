#include <config.h>
#include <references.h>
#include <stack>

namespace TASK_4 {
	void closingBracketCase(std::stack<std::pair<char, int>> & _operators, std::stack<double> & _operands, unsigned & _brackets) {
		double temp_result{};
		double temp_mult;
		bool is_multiplication_operator = false;
		while (!_operators.empty() && _operators.top().second >= _brackets) {
			switch (_operators.top().first) {
				case '+':
					if (is_multiplication_operator) {
						temp_mult *= _operands.top();
						temp_result += temp_mult;
						is_multiplication_operator = false;
					}
					else
						temp_result = temp_result + _operands.top();
					break;

				case '-':
					if (is_multiplication_operator) {
						temp_mult *= _operands.top();
						temp_result -= temp_mult;
						is_multiplication_operator = false;
					}
					else
						temp_result = -_operands.top() + temp_result;
					break;
				case '*':
					if (is_multiplication_operator)
						temp_mult *= _operands.top();
					else
						temp_mult = _operands.top();
					is_multiplication_operator = true;
					break;
				case '/':
					if (is_multiplication_operator)
						temp_mult /= _operands.top();
					else
						temp_mult = 1 / _operands.top();
					is_multiplication_operator = true;
					break;
				case '(':
					if (is_multiplication_operator) {
						temp_mult *= _operands.top();
						temp_result += temp_mult;
					}
					else
						temp_result += _operands.top();
					break;
				default:
					CONSOLE::COLOR_OUT("Got unexpected symbol, skipping...", "WARNING");
					break;
			}
			_operands.pop();
			_operators.pop();
		}
		_operands.push(temp_result);
		_brackets--;
	}

	void calculateAlgebraicExpression() {
		std::string user_expression;
		std::string operator_list = "+-*/()";

		std::cout << "Input expression: ";
		std::getline(std::cin, user_expression);

		user_expression = "(" + user_expression + ")";
		std::erase(user_expression, ' ');

		std::stack<std::pair<char, int>> operators;
		std::stack<double> operands;

		std::string::size_type next{};

		unsigned brackets{};
		for (unsigned i{}; i < user_expression.length(); i++) {
			if (operator_list.find(user_expression[i]) == std::string::npos) {
				operands.push(stod(user_expression.substr(i), &next));

				i = max((int) next - 1 + i, i);
			}
			else {
				switch (user_expression[i]) {
					case '+':
						operators.push({ user_expression[i], brackets });
						break;
					case '-':
						operators.push({ user_expression[i], brackets });
						break;

					case '*':
						operators.push({ user_expression[i], brackets });
						break;

					case '/':
						operators.push({ user_expression[i], brackets });
						break;

					case '(':
						operators.push({ user_expression[i], ++brackets });
						break;

					case ')':
						closingBracketCase(operators, operands, brackets);
						break;
					default:
						CONSOLE::COLOR_OUT("Got unexpected symbol, skipping...", "WARNING");
						break;
				}
			}
		}

		std::cout << operands.top() << std::endl;

	}

}
