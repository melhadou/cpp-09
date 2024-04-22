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
	clock_t then;
	double elapsed;

	then = clock();

	try {
		std::vector<int > pairs =
		 pMergeMe<std::vector<std::pair<int, int> >, std::vector<int> >(ac - 1, &av[1]);
		// use itterator to print the pairs
  	elapsed = static_cast<double>(clock() - then) / CLOCKS_PER_SEC * 1000000;
	
		std::vector<int>::iterator it;
		it = pairs.begin();
   	std::cout << "After: ";
    while (it != pairs.end()) {
      std::cout << *it << " ";
      it++;
    }
		std::cout << std::endl;
  
		std::cout << "Time to process a range of " << ac - 1
            << " elements with std::vector : " << elapsed << " us" << std::endl;

		then = clock();

		// Sorting using deque. no need to catch data. its the same
		pMergeMe<std::deque<std::pair<int, int> >, std::deque<int> >(ac - 1, &av[1]);
		elapsed = static_cast<double>(clock() - then) / CLOCKS_PER_SEC * 1000000;

		std::cout << "Time to process a range of " << ac - 1
							<< " elements with std::deque : " << elapsed << " us" << std::endl;
	} catch (std::runtime_error &e) {
		std::cerr << e.what() << std::endl;
	}

  return 0;
}
