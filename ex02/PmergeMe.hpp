#pragma once
#include <cstdlib>
#include <stdexcept>
#include <utility>
#include <iostream>

class PmergeMe {
private:
public:
  PmergeMe();
  PmergeMe(const PmergeMe &other);
  PmergeMe &operator=(const PmergeMe &other);
  ~PmergeMe();
};

// utils
//
bool checkArgs(int argc, char **argv);

template <typename Pair> Pair makePairs(int ac, char *av[]) {
  int nb1 = 0;
  int nb2 = 0;

  Pair pairs;
  for (int i = 0; i + 1 < ac;) {
    nb1 = atoi(av[i]);
    nb2 = atoi(av[i + 1]);
		if (nb1 > nb2)
			pairs.push_back(std::make_pair(nb1, nb2));
		else
			pairs.push_back(std::make_pair(nb2, nb1));
		// sorting the pairs
		i += 2;
  }

  return pairs;
}

template <typename Container, typename InputContainer>
Container extractMainChain(const InputContainer &input) {
  Container res(input.size());
  typename InputContainer::size_type i = 0;

  while (i < input.size()) {
    res[i] = input[i].first;
    i++;
  }

  return res;
}

template <typename PairedVec, typename Type> PairedVec pMergeMe(int ac, char *av[]) {
  // check if all arguments are positive integers
  if (!checkArgs(ac, av)) {
		throw std::runtime_error("Error: bad arguments.(positive integer only)");
  }

	// check if the number of arguments is even
  bool odd = ((ac) % 2 == 0) ? false : true;

	int last;
	if(odd) 
		last = atoi(av[ac - 1]);
	
	PairedVec pairs = makePairs<PairedVec>(ac, av);
	// Type mainChain = extractMainChain<Type>(pairs);

	if(odd){
		std::cout << "odd" << std::endl;
		// mainChain.insert(mainChain.begin(), last);
		// should add it to proper place after parsing
		std::cout << last << "\n";
	}
  // start sorting
  return pairs;
}
