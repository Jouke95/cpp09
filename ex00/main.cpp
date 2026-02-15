#include "BitcoinExchange.hpp"
#include <iostream>
#include <exception>

int main(int argc, char *argv[]) {
	if (argc != 2) {
		std::cout << "Usage: ./bitcoin <filename>" << std::endl;
		return 1;
	}

	try {
		BitcoinExchange btc;
		btc.processInputFile(argv[1]);
	}
	catch (std::exception& e) {
		std::cerr << e.what() << std::endl;
		return 1;
	}



	return 0;
}
