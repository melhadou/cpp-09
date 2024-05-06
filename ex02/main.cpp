// used container Vector
// used container Deque

#include "PmergeMe.hpp"
#include <deque>
#include <iostream>
#include <utility>
#include <vector>
#include <sys/time.h>

typedef std::vector<std::pair<int, int> >::size_type v_size;

int main(int ac, char *av[]) {

	// add checking for positive
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

	double timeTaken;
	
	size_t startTime;
	size_t timeEnd;

	struct timeval timeCount;

	try {
		gettimeofday(&timeCount, NULL);
		 startTime = (timeCount.tv_sec * 1000000 + timeCount.tv_usec);

		std::vector<int > pairs =
		 merge_insert<std::vector<std::pair<int, int> >, std::vector<int> >(ac - 1, &av[1]);
		
		gettimeofday(&timeCount, NULL);
		 timeEnd = (timeCount.tv_sec * 1000000 + timeCount.tv_usec);

		timeTaken = timeEnd - startTime;
		// use itterator to print the pairs
		
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

		startTime = (timeCount.tv_sec * 1000000 + timeCount.tv_usec);

		// Sorting using deque. no need to catch data. its the same
		merge_insert<std::deque<std::pair<int, int> >, std::deque<int> >(ac - 1, &av[1]);
		
		gettimeofday(&timeCount, NULL);
		timeEnd = (timeCount.tv_sec * 1000000 + timeCount.tv_usec);

		timeTaken = timeEnd - startTime;

		std::cout << "Time to process a range of " << ac - 1
							<< " elements with std::deque : " << timeTaken << " us" << std::endl;
	} catch (std::runtime_error &e) {
		std::cerr << e.what() << std::endl;
	}

  return 0;
}
