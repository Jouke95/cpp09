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

void PmergeMe::sortVector(std::vector<std::pair<int,int> > &pairs) {
	if (pairs.size() == 1) {
		if (pairs[0].first < pairs[0].second)
			std::swap(pairs[0].first, pairs[0].second);
		return;
	}
	for (size_t i = 0; i < pairs.size(); i++) {
		if (pairs[i].first < pairs[i].second)
			std::swap(pairs[i].first, pairs[i].second);
	}
	std::vector<std::pair<int, int> > winners;
	std::vector<std::pair<int, int> > losers;
	for (size_t i = 0; i < pairs.size() / 2; i++) {
		if (pairs[i*2].first > pairs[i*2+1].first) {
			winners.push_back(pairs[i*2]);
			losers.push_back(pairs[i*2+1]);
		}
		else {
			winners.push_back(pairs[i*2+1]);
			losers.push_back(pairs[i*2]);
		}
	}
	sortVector(winners);
	std::vector<int> mainChain;
	std::vector<int> pend;
	for (size_t i = 0; i < winners.size(); i++) {
		mainChain.push_back(winners[i].first);
		pend.push_back(losers[i].second);
	}
	mainChain.insert(pend.begin(), 1);
}

void PmergeMe::sortVector() {
	if (vect.size() == 1)
		return;
	std::vector<std::pair<int, int> > pairs;
	for (size_t i = 0; i < vect.size() / 2; i++) {
		std::pair<int, int> pair;
		pair.first = vect[i*2];
		pair.second = vect[i*2+1];
		pairs.push_back(pair);
	}
	sortVector(pairs);



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
