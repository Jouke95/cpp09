#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <vector>
#include <list>
#include <string>
#include <sstream>

class PmergeMe {
	private:
		std::vector<int> vect;
		std::list<int> lst;

		bool validInput;
		long vectorTime;
		long listTime;

		// copy constructor and assignment operator - no implementation
		PmergeMe(const PmergeMe& other);
		PmergeMe& operator=(const PmergeMe& other);

		void sortVector();

		void sortList();

		bool parseInput(int argc, char **argv);

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
