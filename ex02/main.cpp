#include "PmergeMe.hpp"

// command to use: ./PmergeMe `shuf -i 1-10000 -n 3000 | tr "\n" " "`

int main(int argc, char **argv) {
	PmergeMe PM(argc, argv);
	PM.sort();
	PM.displayResults();

	return (0);
}
