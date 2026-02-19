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

	std::cout << "\n\nParsed " << vect.size() << " numbers:" << std::endl;
	for (size_t i = 0; i < vect.size(); i++)
		std::cout << vect[i] << " ";
	std::cout << std::endl;
}

int PmergeMe::jacobsthal(int n) {
	if (n == 0) return 0;
	if (n == 1) return 1;
	return jacobsthal(n - 1) + 2 * jacobsthal(n - 2);
}

void PmergeMe::binaryInsertPair(std::vector<std::pair<int,int>>& chain, std::pair<int,int> val, int upperBound) {
	int low = 0;
	int high = upperBound;
	while (low < high) {
		int mid = (low + high) / 2;
		if (chain[mid].first < val.first)
			low = mid + 1;
		else
			high = mid;
	}
	chain.insert(chain.begin() + low, val);
}

void PmergeMe::insertLoserPairs(std::vector<std::pair<int,int>>& sorted, std::vector<std::pair<int,int>>& subWinners, std::vector<std::pair<int,int>>& subLosers) {
	int pendSize = (int)subLosers.size();

	sorted.insert(sorted.begin(), subLosers[0]);

	int prev = 1;
	for (int k = 2; prev < pendSize; k++) {
		int jacob = jacobsthal(k);
		if (jacob > pendSize)
			jacob = pendSize;

		for (int i = jacob -1; i >= prev; i--) {
			int upperBound = 0;
			for (int j = 0; j < (int)sorted.size(); j++) {
				if (subWinners[i].first == sorted[j].first) {
					upperBound = j;
					break;
				}
			}
			binaryInsertPair(sorted, subLosers[i], upperBound);
		}
		prev = jacob;
	}
}

void PmergeMe::sortPairsByWinners(std::vector<std::pair<int, int>> &pairs) {
	if (pairs.size() == 1) return;

	bool hasOdd = (pairs.size() % 2 == 1);
	std::pair<int,int> oddPair;
	if (hasOdd) {
		oddPair = pairs.back();
		pairs.pop_back();
	}

	std::vector<std::pair<int, int>> subWinners;
	std::vector<std::pair<int, int>> subLosers;

	for (int i = 0; i < (int)pairs.size() / 2; i++) {
		if (pairs[i*2].first > pairs[i*2+1].first) {
			subWinners.push_back(pairs[i*2]);
			subLosers.push_back(pairs[i*2+1]);
		}
		else {
			subWinners.push_back(pairs[i*2+1]);
			subLosers.push_back(pairs[i*2]);
		}
	}

	sortPairsByWinners(subWinners);

	std::vector<std::pair<int, int>> sorted = subWinners;
	insertLoserPairs(sorted, subWinners, subLosers);

	if (hasOdd) 
		binaryInsertPair(sorted, oddPair, (int)sorted.size());

	pairs = sorted;
}

void PmergeMe::sortVector() {

	std::vector<std::pair<int, int>> pairs;
	for (int i = 0; i < (int)vect.size() / 2; i++) {
		std::pair<int, int> pair;
		pair.first = vect[i*2];
		pair.second = vect[i*2+1];
		pairs.push_back(pair);
	}
	for (int i = 0; i < (int)pairs.size(); i++) {
		if (pairs[i].second > pairs[i].first)
			std::swap(pairs[i].first, pairs[i].second);
	}

	std::cout << "Voor sorteren: \n";
	for (size_t i = 0; i < pairs.size(); i++) {
		std::cout << "pair[" << i << "] = (" << pairs[i].first << ", " << pairs[i].second << ")" << std::endl;
	}

	sortPairsByWinners(pairs);

	std::cout << "\nNa sorteren: \n";
	for (size_t i = 0; i < pairs.size(); i++) {
		std::cout << "pair[" << i << "] = (" << pairs[i].first << ", " << pairs[i].second << ")" << std::endl;
	}
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
		bool isDuplicate = false;
		for (size_t j = 0; j < vect.size(); j++) {
			if (vect[j] == number) {
				isDuplicate = true;
				break;
			}
		}
		if (!isDuplicate) {
			vect.push_back(number);
			lst.push_back(number);
		}
	}

	return true;
}

