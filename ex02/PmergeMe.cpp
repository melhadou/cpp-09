#include "PmergeMe.hpp"
#include <cctype>

bool checkArgs(int ac, char **av) {
  for (int i = 1; i < ac; i++) {
    if (av[i][0] == '\0')
      return false;

    for (int j = 0; av[i][j]; j++) {
      if (!std::isdigit(av[i][j])) {
        return false;
      }
    }
  }
  return true;
}
