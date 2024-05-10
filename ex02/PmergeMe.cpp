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
