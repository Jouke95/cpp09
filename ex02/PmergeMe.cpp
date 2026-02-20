#include "PmergeMe.hpp"
#include <chrono>
#include <iostream>
#include <set>

static void printSequence(std::string label, const std::vector<int>& vec) {
	std::cout << label;
	int limit = std::min((int)vec.size(), PRINT_LIMIT);
	for (int i = 0; i < limit; i++)
		std::cout << vec[i] << " ";
	if (vec.size() > PRINT_LIMIT)
	std::cout << "[...]";
	std::cout << std::endl;
}

PmergeMe::PmergeMe(int argc, char **argv) {
	if (!parseInput(argc, argv)) {
		validInput = false;
		std::cerr << "Error" << std::endl;
		return;
	}

	validInput = true;
	original = vect;
}

PmergeMe::~PmergeMe() {}

bool PmergeMe::parseInput(int argc, char **argv) {
	if (argc < 2)
		return false;

	std::set<int> mySet;

	for (int i = 1; i < argc; i++) {
		int number;
		if (!parse(argv[i], number))
			return false;
		if (number <= 0)
			return false;
		if (mySet.count(number))
			return false;
		mySet.insert(number);
		vect.push_back(number);
		deq.push_back(number);
	}

	return true;
}

void PmergeMe::sort() {
	if (!validInput)
		return;

	std::chrono::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();
	sortVector();
	std::chrono::high_resolution_clock::time_point end = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double, std::micro> duration = end - start;
	vectorTime = duration.count();

	start = std::chrono::high_resolution_clock::now();
	sortDeque();
	end = std::chrono::high_resolution_clock::now();
	duration = end - start;
	dequeTime = duration.count();
}

void PmergeMe::displayResults() {
	if (!validInput)
		return;

	printSequence("Before\t", original);
	printSequence("After\t", vect);

	std::cout << "Time to process a range of " << vect.size() 
				<< " elements with std::vector : " << vectorTime << " us" << std::endl;

	std::cout << "Time to process a range of " << vect.size() 
				<< " elements with std::deque : " << dequeTime << " us" << std::endl;

	for (int i = 0; i < (int)vect.size() - 1; i++) {
		if (vect[i] > vect[i+1]) {
			std::cout << "NOT SORTED at index " << i << std::endl;
			return;
		}
	}
	std::cout << "SORTED!" << std::endl;
}

int PmergeMe::jacobsthal(int n) {
	if (n == 0) return 0;
	if (n == 1) return 1;
	return jacobsthal(n - 1) + 2 * jacobsthal(n - 2);
}

void PmergeMe::binaryInsertInt(std::vector<int>& chain, int val, int upperBound) {
	int low = 0;
	int high = upperBound;
	while (low < high) {
		int mid = (low + high) / 2;
		if (chain[mid] < val)
			low = mid + 1;
		else
			high = mid;
	}
	chain.insert(chain.begin() + low, val);
}

void PmergeMe::binaryInsertPair(PairVector& chain, CombinedPair val, int upperBound) {
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

void PmergeMe::insertLoserPairs(PairVector& sorted, PairVector& subWinners, PairVector& subLosers) {
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

void PmergeMe::insertPendChain(const PairVector& pairs, std::vector<int>& main, std::vector<int>& pend) {
	int pendSize = (int)pend.size();

	main.insert(main.begin(), pend[0]);

	int prev = 1;
	for (int k = 2; prev < pendSize; k++) {
		int jacob = jacobsthal(k);
		if (jacob > pendSize)
			jacob = pendSize;

		for (int i = jacob - 1; i >= prev; i--) {
			int upperBound = 0;
			for (int j = 0; j < (int)main.size(); j++) {
				if (main[j] == pairs[i].first) {
					upperBound = j;
					break;
				}
			}
			binaryInsertInt(main, pend[i], upperBound);
		}
		prev = jacob;
	}
}

void PmergeMe::sortPairsByWinners(PairVector& pairs) {
	if (pairs.size() == 1) return;

	bool hasOdd = (pairs.size() % 2 == 1);
	CombinedPair oddPair;
	if (hasOdd) {
		oddPair = pairs.back();
		pairs.pop_back();
	}

	PairOfPairsVector pairOfPairs;
	PairVector subWinners;
	for (int i = 0; i < (int)pairs.size() / 2; i++) {
		CombinedPair winner, loser;
		if (pairs[i*2].first > pairs[i*2+1].first) {
			winner = pairs[i*2];
			loser = pairs[i*2+1];
		}
		else {
			winner = pairs[i*2+1];
			loser = pairs[i*2];
		}
		pairOfPairs.push_back(std::make_pair(winner, loser));
		subWinners.push_back(winner);
	}

	sortPairsByWinners(subWinners);

	PairOfPairsVector reorderedPairs;
	for (int i = 0; i < (int)subWinners.size(); i++) {
		for (int j = 0; j < (int)pairOfPairs.size(); j++) {
			if (pairOfPairs[j].first.first == subWinners[i].first) {
				reorderedPairs.push_back(pairOfPairs[j]);
				break;
			}
		}
	}
	pairOfPairs = reorderedPairs;

	PairVector subLosers;
	for (int i = 0; i < (int)pairOfPairs.size(); i++)
		subLosers.push_back(pairOfPairs[i].second);

	PairVector result = subWinners;
	insertLoserPairs(result, subWinners, subLosers);

	if (hasOdd) 
		binaryInsertPair(result, oddPair, (int)result.size());

	pairs = result;
}

void PmergeMe::sortVector() {
	if (vect.size() <= 1)
		return;

	bool hasOdd = (vect.size() % 2 == 1);
	int straggler;
	if (hasOdd) {
		straggler = vect.back();
		vect.pop_back();
	}

	PairVector pairs;
	for (int i = 0; i < (int)vect.size() / 2; i++) {
		CombinedPair pair;
		pair.first = vect[i*2];
		pair.second = vect[i*2+1];
		pairs.push_back(pair);
	}
	for (int i = 0; i < (int)pairs.size(); i++) {
		if (pairs[i].second > pairs[i].first)
			std::swap(pairs[i].first, pairs[i].second);
	}

	sortPairsByWinners(pairs);

	std::vector<int> main;
	std::vector<int> pend;
	for (int i = 0; i < (int)pairs.size(); i++) {
		main.push_back(pairs[i].first);
		pend.push_back(pairs[i].second);
	}

	insertPendChain(pairs, main, pend);

	if (hasOdd)
		binaryInsertInt(main, straggler, (int)main.size());

	vect = main;
}

void PmergeMe::binaryInsertIntDeque(std::deque<int>& chain, int val, int upperBound) {
	int low = 0;
	int high = upperBound;
	while (low < high) {
		int mid = (low + high) / 2;
		if (chain[mid] < val)
			low = mid + 1;
		else
			high = mid;
	}
	chain.insert(chain.begin() + low, val);
}

void PmergeMe::insertPendChainDeque(const PairVector& pairs, std::deque<int>& main, std::deque<int>& pend) {
	int pendSize = (int)pend.size();

	main.insert(main.begin(), pend[0]);

	int prev = 1;
	for (int k = 2; prev < pendSize; k++) {
		int jacob = jacobsthal(k);
		if (jacob > pendSize)
			jacob = pendSize;

		for (int i = jacob - 1; i >= prev; i--) {
			int upperBound = 0;
			for (int j = 0; j < (int)main.size(); j++) {
				if (main[j] == pairs[i].first) {
					upperBound = j;
					break;
				}
			}
			binaryInsertIntDeque(main, pend[i], upperBound);
		}
		prev = jacob;
	}
}

void PmergeMe::sortDeque() {
	if (deq.size() <= 1)
		return;

	bool hasOdd = (deq.size() % 2 == 1);
	int straggler;
	if (hasOdd) {
		straggler = deq.back();
		deq.pop_back();
	}

	PairVector pairs;
	for (int i = 0; i < (int)deq.size() / 2; i++) {
		CombinedPair pair;
		pair.first = deq[i*2];
		pair.second = deq[i*2+1];
		pairs.push_back(pair);
	}
	for (int i = 0; i < (int)pairs.size(); i++) {
		if (pairs[i].second > pairs[i].first)
			std::swap(pairs[i].first, pairs[i].second);
	}

	sortPairsByWinners(pairs);

	std::deque<int> main;
	std::deque<int> pend;
	for (int i = 0; i < (int)pairs.size(); i++) {
		main.push_back(pairs[i].first);
		pend.push_back(pairs[i].second);
	}

	insertPendChainDeque(pairs, main, pend);

	if (hasOdd)
		binaryInsertIntDeque(main, straggler, (int)main.size());

	deq = main;
}
