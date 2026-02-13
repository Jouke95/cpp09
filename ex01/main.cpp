#include "RPN.hpp"
#include <iostream>

int main(int argc, char *argv[]) {
	if (argc != 2) {
		std::cerr << "Usage: ./rpn <expression>" << std::endl;
		return 1;
	}

	RPN rpn;
	int result;
	if (rpn.calculate(argv[1], result)) {
		std::cout << result << std::endl;
	}
	else {
		std::cerr << "Error" << std::endl;
	}

	return 0;
}
