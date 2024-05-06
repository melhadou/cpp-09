#include "PmergeMe.hpp"
#include <cctype>

// ortodox canonical form
PmergeMe::PmergeMe() {
}

PmergeMe::PmergeMe(const PmergeMe &other) {
	*this = other;
}

PmergeMe &PmergeMe::operator=(const PmergeMe &other) {
	(void)other; // avoid warning
	return *this;
}

PmergeMe::~PmergeMe() {
}
// ----- end of ortodox canonical form ------

bool checkArgs(int ac, char **av) {
	// check if args are positive integers
	for (int i = 0; i < ac; i++) {
		for (int j = 0; av[i][j] != '\0'; j++) {
			if (!isdigit(av[i][j])) {
				return false;
			}
		}
	}
	return true;
}
