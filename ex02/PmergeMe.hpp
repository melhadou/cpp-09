#pragma once
#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <utility>
#include <vector>

typedef std::vector<std::pair<int, int> >::iterator it;
typedef std::vector<std::pair<int, int> > Container;

class PmergeMe {
 private:
 public:
  PmergeMe();
  PmergeMe(const PmergeMe &other);
  PmergeMe &operator=(const PmergeMe &other);
  ~PmergeMe();

};

void insertFromPendToMainchain(std::vector<int> &pend, std::vector<int> &mainchain);
std::vector<int> extractMainChain(Container &input);
std::vector<int> extractPendChain(const Container &input);

void merge(it begin, it middle, it end);

void mergeRecursive(it begin, it end);
std::vector<std::pair<int, int> > makePairs(int ac, char *av[]);

std::vector<int> merge_insert(int ac, char *av[]);

// utils
//
// bool checkArgs(int argc, char **argv);

// template <typename Container>
// void insertFromPendToMainchain(Container &pend, Container &mainchain) {
//   for (typename Container::iterator it = pend.begin(); it != pend.end(); ++it) {
//     int element = *it;  // Dereference iterator to get the element

//     // Find insertion position using a linear search
//     typename Container::iterator insertIt =
//         std::lower_bound(mainchain.begin(), mainchain.end(), element);

//     // Insert element at the iterator's position
//     mainchain.insert(insertIt, element);
//   }
// }

// template <typename Pair>
// Pair makePairs(int ac, char *av[]) {
//   int nb1 = 0;
//   int nb2 = 0;

//   Pair pairs;
//   for (int i = 0; i + 1 < ac;) {
//     nb1 = atoi(av[i]);
//     nb2 = atoi(av[i + 1]);
//     if (nb1 < nb2)
//       pairs.push_back(std::make_pair(nb2, nb1));
//     else
//       pairs.push_back(std::make_pair(nb1, nb2));
//     // sorting the pairs
//     i += 2;
//   }

//   return pairs;
// }

// template <typename Container, typename InputContainer>
// Container extractMainChain(const InputContainer &input) {
//   Container res(input.size());
//   typename InputContainer::size_type i = 0;

//   while (i < input.size()) {
//     res[i] = input[i].first;
//     // std::cout << "pair[" << i << "]: " << input[i].first << " " <<
//     // input[i].second << std::endl;
//     i++;
//   }

//   return res;
// }

// template <typename Container, typename InputContainer>
// Container extractPendChain(const InputContainer &input) {
//   Container res(input.size());
//   typename InputContainer::size_type i = 0;

//   while (i < input.size()) {
//     res[i] = input[i].second;
//     i++;
//   }

//   return res;
// }

// template <typename Container>
// void swapPair(Container &pairs) {
//   // define itterator
//   typename Container::size_type i = 0;

//   while (i < pairs.size()) {
//     if (pairs[i].first < pairs[i].second)
//       std::swap(pairs[i].first, pairs[i].second);
//     i++;
//   }
// }

// template <typename Container>
// void merge(typename Container::iterator begin,
//            typename Container::iterator middle,
//            typename Container::iterator end) {
//   Container result;
//   typename Container::iterator left = begin;
//   typename Container::iterator right = middle;

//   // Merge the two halves into the result vector
//   while (left != middle && right != end) {
//     if (left->first < right->first)
//       result.push_back(*left++);
//     else
//       result.push_back(*right++);
//   }

//   // Copy any remaining elements from the left half
//   while (left != middle) {
//     result.push_back(*left++);
//   }

//   // Copy any remaining elements from the right half
//   while (right != end) {
//     result.push_back(*right++);
//   }

//   // Copy the merged elements back to the original container
//   std::copy(result.begin(), result.end(), begin);
// }

// template <typename Container>
// void mergeRecursive(typename Container::iterator begin,
//                     typename Container::iterator end) {
//   typename Container::iterator middle = begin + (end - begin) / 2;
//   if (end - begin > 1 && begin != end) {
//     mergeRecursive<Container>(begin, middle);
//     mergeRecursive<Container>(middle, end);
//   }

//   merge<Container>(begin, middle, end);
// }

// template <typename PairedVec, typename Type>
// Type merge_insert(int ac, char *av[]) {
//   // check if the number of arguments is even
//   bool odd = ((ac) % 2 == 0) ? false : true;

//   int last;

//   if (odd) last = atoi(av[ac - 1]);

//   PairedVec pairs = makePairs<PairedVec>(ac, av);

//   // sorting the pairs based on the first element using recursive merge sort
//   mergeRecursive<PairedVec>(pairs.begin(), pairs.end());

//   Type mainChain = extractMainChain<Type>(pairs);
//   Type pendChain = extractPendChain<Type>(pairs);

//   insertFromPendToMainchain<Type>(pendChain, mainChain);

//   if (odd) {
//     typename Type::iterator insertIt =
//         std::lower_bound(mainChain.begin(), mainChain.end(), last);

//     // Insert element at the iterator's position
//     mainChain.insert(insertIt, last);
//   }
//   // start sorting
//   return mainChain;
// }
