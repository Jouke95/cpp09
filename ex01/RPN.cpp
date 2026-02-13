#include "RPN.hpp"
#include <sstream>

RPN::RPN() {}

RPN::~RPN() {}

RPN::RPN(const RPN& other) { (void)other; }

RPN& RPN::operator=(const RPN& other) { (void)other; return *this; }

bool RPN::isOperator(const std::string& input) {
	return (input == "+" || input == "-" || input == "*" || input == "/");
}

bool RPN::isNumber(const std::string& input) {
	if (input.length() != 1)
		return false;
	return (input[0] >= '0' && input[0] <= '9');
}

int RPN::performOperation(int a, int b, const std::string& op) {
	if (op == "+")
		return a + b;
	if (op == "-")
		return a - b;
	if (op == "/")
		return a / b;
	if (op == "*")
		return a * b;
	return 0;
}

int RPN::popValue(std::stack<int>& stack) {
	int value = stack.top();
	stack.pop();
	return value;
}

bool RPN::calculate(const std::string& input, int& result) {
	std::stack<int> stack;
	std::istringstream iss(input);
	std::string token;

	while (iss >> token) {
		if (isNumber(token)) {
			int number = token[0] - '0';
			stack.push(number);
		}
		else if (isOperator(token)) {
			if (stack.size() < 2)
				return false;
			int right = popValue(stack);
			int left = popValue(stack);
			if (right == 0 && token == "/")
				return false;
			stack.push(performOperation(left, right, token));
		}
		else
			return false;
	}
	if (stack.size() != 1)
		return false;
	result = stack.top();
	return true;
}
