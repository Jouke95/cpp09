#include "PmergeMe.hpp"

int main(int argc, char **argv) {
	PmergeMe PM(argc, argv);
	PM.sort();
	PM.displayResults();

	return (0);
}
