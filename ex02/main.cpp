// used container Vector
// #include "PmergeMe.hpp"

#include "PmergeMe.hpp"
#include <iostream>
#include <utility>
#include <vector>

typedef std::vector<std::pair<int, int> >::size_type v_size;

int main(int ac, char *av[]) {

  if (ac <= 1) {
    std::cerr << "Error: bad arguments.(positive integer only)" << std::endl;
    return 1;
  }

	try {
  std::vector<int > pairs =
      pMergeMe<std::vector<std::pair<int, int> >, std::vector<int> >(ac - 1, &av[1]);
		// use itterator to print the pairs
		std::vector<int>::iterator it;
		it = pairs.begin();
		while (it != pairs.end()) {
			std::cout << *it << std::endl;
			it++;
		}
	} catch (std::runtime_error &e) {
		std::cerr << e.what() << std::endl;
	}

  return 0;
}
