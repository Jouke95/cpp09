#include "PmergeMe.hpp"
#include <iostream>

PmergeMe::PmergeMe(int argc, char **argv) {
	if (!parseInput(argc, argv)) {
		validInput = false;
		std::cerr << "Error" << std::endl;
		return;
	}

	validInput = true;
}

PmergeMe::~PmergeMe() {}

void PmergeMe::sort() {
	if (!validInput)
		return;

	sortVector();
	sortList();
}

void PmergeMe::displayResults() {
	if (!validInput)
		return;

	std::cout << "Parsed " << vect.size() << " numbers" << std::endl;
	for (size_t i = 0; i < vect.size(); i++)
		std::cout << vect[i] << " ";
	std::cout << std::endl;
}

void PmergeMe::sortVector() {
	
}

void PmergeMe::sortList() {

}

bool PmergeMe::parseInput(int argc, char **argv) {
	if (argc < 2)
		return false;

	for (int i = 1; i < argc; i++) {
		int number;
		if (!parse(argv[i], number))
			return false;
		if (number < 0)
			return false;
		vect.push_back(number);
		lst.push_back(number);
	}

	return true;
}

