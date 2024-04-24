// used container Vector
// #include "PmergeMe.hpp"

#include "PmergeMe.hpp"
#include <deque>
#include <iostream>
#include <utility>
#include <vector>

typedef std::vector<std::pair<int, int> >::size_type v_size;

int main(int ac, char *av[]) {

  if (ac <= 1) {
    std::cerr << "Error: bad arguments.(positive integer only)" << std::endl;
    return 1;
  }

	std::cout << "Before: ";
	int i = 1;
	while (i < ac) {
		std::cout << av[i] << " ";
		i++;
	}
	std::cout << std::endl;

	clock_t startTime;
	double timeTaken;

	startTime = clock();

	try {
		std::vector<int > pairs =
		 pMergeMe<std::vector<std::pair<int, int> >, std::vector<int> >(ac - 1, &av[1]);
		// use itterator to print the pairs
  	timeTaken = static_cast<double>(clock() - startTime) / CLOCKS_PER_SEC * 1000000;
	
		std::vector<int>::iterator it;
		it = pairs.begin();
   	std::cout << "After: ";
    while (it != pairs.end()) {
      std::cout << *it << " ";
      it++;
    }
		std::cout << std::endl;
  
		std::cout << "Time to process a range of " << ac - 1
            << " elements with std::vector : " << timeTaken << " us" << std::endl;

		startTime = clock();

		// Sorting using deque. no need to catch data. its the same
		pMergeMe<std::deque<std::pair<int, int> >, std::deque<int> >(ac - 1, &av[1]);
		timeTaken = static_cast<double>(clock() - startTime) / CLOCKS_PER_SEC * 1000000;

		std::cout << "Time to process a range of " << ac - 1
							<< " elements with std::deque : " << timeTaken << " us" << std::endl;
	} catch (std::runtime_error &e) {
		std::cerr << e.what() << std::endl;
	}

  return 0;
}
