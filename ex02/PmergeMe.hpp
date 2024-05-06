#pragma once
#include <algorithm>
#include <cstdlib>
#include <stdexcept>
#include <utility>

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

template <typename Container>
void insertFromPendToMainchain(Container &pend, Container &mainchain) {
 for (typename Container::iterator it = pend.begin(); it != pend.end(); ++it) {
    int element = *it; // Dereference iterator to get the element

    // Find insertion position using a linear search
	 typename Container::iterator insertIt = std::lower_bound(mainchain.begin(), mainchain.end(), element);

    // Insert element at the iterator's position
    mainchain.insert(insertIt, element);
  }
}

template <typename Pair> Pair makePairs(int ac, char *av[]) {
  int nb1 = 0;
  int nb2 = 0;

  Pair pairs;
  for (int i = 0; i + 1 < ac;) {
    nb1 = atoi(av[i]);
    nb2 = atoi(av[i + 1]);
		if (nb1 < nb2)
			pairs.push_back(std::make_pair(nb2, nb1));
		else pairs.push_back(std::make_pair(nb1, nb2));
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
		// std::cout << "pair[" << i << "]: " << input[i].first << " " << input[i].second << std::endl;
    i++;
  }

  return res;
}

template <typename Container, typename InputContainer>
Container extractPendChain(const InputContainer &input) {
  Container res(input.size());
  typename InputContainer::size_type i = 0;

  while (i < input.size()) {
    res[i] = input[i].second;
    i++;
  }

  return res;
}

template<typename Container>
void swapPair(Container &pairs){
	// define itterator
	typename Container::size_type i = 0;

	while(i < pairs.size())
	{
		if (pairs[i].first < pairs[i].second )
			std::swap(pairs[i].first, pairs[i].second);
		i++;
	}

}


template<typename Container>
void merge(typename Container::iterator begin, typename Container::iterator middle, typename Container::iterator end)
{
		Container result;
    typename Container::iterator left = begin;
    typename Container::iterator right = middle;

    // Merge the two halves into the result vector
    while (left != middle && right != end) {
        if (left->first < right->first)
            result.push_back(*left++);
        else
            result.push_back(*right++);
    }

    // Copy any remaining elements from the left half
    while (left != middle) {
        result.push_back(*left++);
    }

    // Copy any remaining elements from the right half
    while (right != end) {
        result.push_back(*right++);
    }

    // Copy the merged elements back to the original container
    std::copy(result.begin(), result.end(), begin);

	// // save the middle and begin. so we can recopy the array back to original
	// typename Container::iterator oriBegin = begin;
	// typename Container::iterator oriMiddle = middle;
	// 
	// typename Container::iterator tmp;

	// Container result;
	// // loop over until middle or begin are exhausted
	// while((begin != oriMiddle) || (middle != end))
	// {
	// 	if (begin == oriMiddle)
	// 		tmp = middle++;
	// 	else if (middle == end)
	// 		tmp = begin++;
	// 	else {
	// 		// element are in both. so we compare
	// 		if (begin->first < middle->first)
	// 			tmp = begin++;
	// 		else
	// 			tmp = middle++;
	// 		// std::cout << tmp->first << std::endl;
	// 		// saving
	// 	}
	// 	result.push_back(*tmp);
	// }
	// // loop over res. and copy back to original begin
	// for (size_t i = 0; i < result.size(); i++)
	// {
	// 	// start copying to original
	// 	*oriBegin = result[i];
	// 	oriBegin++;
	// }
}

template < typename Container>
void mergeRecursive(typename Container::iterator begin,
										typename Container::iterator end)
{

	typename Container::iterator middle = begin + (end - begin) / 2;
	if (end - begin > 1 && begin != end)
	{
		mergeRecursive<Container>(begin, middle);
		mergeRecursive<Container>(middle, end);
	}

	merge<Container>(begin, middle, end);
}

template <typename PairedVec, typename Type> Type merge_insert(int ac, char *av[]) {
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

	// sorting the pairs based on the first element using recursive merge sort
	mergeRecursive<PairedVec>(pairs.begin(), pairs.end());

	Type mainChain = extractMainChain<Type>(pairs);
	Type pendChain = extractPendChain<Type>(pairs);

	insertFromPendToMainchain<Type>(pendChain, mainChain);

	if(odd){
		typename Type::iterator insertIt = std::lower_bound(mainChain.begin(), mainChain.end(), last);

    // Insert element at the iterator's position
    mainChain.insert(insertIt, last);
	}
  // start sorting
  return mainChain;
}
