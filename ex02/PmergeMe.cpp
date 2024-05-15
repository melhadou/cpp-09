#include "PmergeMe.hpp"
#include <vector>

// ortodox canonical form
PmergeMe::PmergeMe() {}

PmergeMe::PmergeMe(const PmergeMe &other) { *this = other; }

PmergeMe &PmergeMe::operator=(const PmergeMe &other) {
  (void)other;  // avoid warning
  return *this;
}

PmergeMe::~PmergeMe() {}
// ----- end of ortodox canonical form ------


void insertFromPendToMainchain(std::vector<int> &pend, std::vector<int> &mainchain) {
  for (std::vector<int>::iterator ite = pend.begin(); ite != pend.end(); ++ite) {
    int element = *ite;  // Dereference iterator to get the element

    // Find insertion position using a linear search
    std::vector<int>::iterator insertIt =
       std::lower_bound(mainchain.begin(), mainchain.end(), element);

    // Insert element at the iterator's position
    mainchain.insert(insertIt, element);
  }
}

std::vector<int> extractMainChain(Container &input) {
  std::vector<int> res(input.size());
  Container::size_type i = 0;

  while (i < input.size()) {
    res[i] = input[i].first;
    i++;
  }

  return res;
}

std::vector<int> extractPendChain(const Container &input) {
	std::vector<int> res(input.size());
  Container::size_type i = 0;

  while (i < input.size()) {
    res[i] = input[i].second;
    i++;
  }

  return res;
}

void merge(it begin,
           it middle,
           it end) {
  Container result;
  it left = begin;
  it right = middle;

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
}

void mergeRecursive(it begin,
                    it end) {
  it middle = begin + (end - begin) / 2;
  if (end - begin > 1 && begin != end) {
    mergeRecursive(begin, middle);
    mergeRecursive(middle, end);
  }

  merge(begin, middle, end);
}

std::vector<std::pair<int, int> > makePairs(int ac, char *av[]) {
  int nb1 = 0;
  int nb2 = 0;

  std::vector<std::pair<int, int> > pairs;
  for (int i = 0; i + 1 < ac;) {
    nb1 = atoi(av[i]);
    nb2 = atoi(av[i + 1]);
    if (nb1 < nb2)
      pairs.push_back(std::make_pair(nb2, nb1));
    else
      pairs.push_back(std::make_pair(nb1, nb2));
    i += 2;
  }

  return pairs;
}

std::vector<int> merge_insert(int ac, char *av[]) {
  // check if the number of arguments is even
  bool odd = ((ac) % 2 == 0) ? false : true;

  int last;

  if (odd) last = atoi(av[ac - 1]);

  std::vector<std::pair<int, int> > pairs = makePairs(ac, av);

  // sorting the pairs based on the first element using recursive merge sort
  mergeRecursive(pairs.begin(), pairs.end());

  std::vector<int> mainChain = extractMainChain(pairs);
  std::vector<int> pendChain = extractPendChain(pairs);

  insertFromPendToMainchain(pendChain, mainChain);

  if (odd) {
    typename std::vector<int>::iterator insertIt =
        std::lower_bound(mainChain.begin(), mainChain.end(), last);

    // Insert element at the iterator's position
    mainChain.insert(insertIt, last);
  }
  // start sorting
  return mainChain;
}
