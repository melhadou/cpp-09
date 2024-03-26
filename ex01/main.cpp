#include "RPN.hpp"
#include <iostream>
#include <stdexcept>
int main(int ac, char *av[]) {
  //
  if (ac != 2) {
    std::cerr << "Usage: ./RPN \"8 9 *\"" << std::endl;
    return 1;
  }

  std::string input = av[1];

  // create instance of RPN core
  try {
    Rpn rpn;
    rpn.parseAndCalc(input);

    if (rpn.getResDb().empty())
      throw std::runtime_error("error: stack is empty.");

    // print result
    std::cout << rpn.getResDb().top() << std::endl;
  } catch (std::exception &e) {
    std::cerr << e.what() << std::endl;
  }

  return 0;
}
