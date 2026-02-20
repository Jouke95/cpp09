#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <deque>
#include <sstream>
#include <string>
#include <vector>

#define PRINT_LIMIT 5

typedef std::pair<int,int> CombinedPair;
typedef std::vector<CombinedPair> PairVector;
typedef std::pair<CombinedPair, CombinedPair> PairOfPairs;
typedef std::vector<PairOfPairs> PairOfPairsVector;

class PmergeMe {
	private:
		std::vector<int> vect;
		std::deque<int> deq;

		std::vector<int> original;
		bool validInput;
		double vectorTime;
		double dequeTime;

		PmergeMe(const PmergeMe& other) = delete;
		PmergeMe& operator=(const PmergeMe& other) = delete;

		bool parseInput(int argc, char **argv);
		void sortVector();
		void sortDeque();

		int jacobsthal(int n);
		void binaryInsertPair(PairVector& chain, CombinedPair val, int upperBound);
		void binaryInsertInt(std::vector<int>& chain, int val, int upperBound);
		void binaryInsertIntDeque(std::deque<int>& chain, int val, int upperBound);
		void sortPairsByWinners(PairVector& pairs);
		void insertLoserPairs(PairVector& sorted, PairVector& subWinners, PairVector& subLosers);
		void insertPendChain(const PairVector& pairs, std::vector<int>& main, std::vector<int>& pend);
		void insertPendChainDeque(const PairVector& pairs, std::deque<int>& main, std::deque<int>& pend);

		template <typename T>
		bool parse(const std::string& str, T& result) {
			std::stringstream ss(str);
			ss >> result;
			if (ss.fail() || !ss.eof())
				return false;
			return true;
		}

	public:
		PmergeMe(int argc, char **argv);
		~PmergeMe();

		void sort();
		void displayResults();
};

#endif
