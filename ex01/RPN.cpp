#include "RPN.hpp"

#include <cctype>
#include <stdexcept>

Rpn::Rpn() {}

Rpn::Rpn(const Rpn &rhs) { *this = rhs; }

Rpn &Rpn::operator=(const Rpn &rhs) {
  if (this == &rhs) return *this;
  this->resDb = rhs.resDb;
  return *this;
}

Rpn::~Rpn() {}

/* Calc:
 * parse the input,
 * insert number and calculate based on what's on the stack
 * algo => if number push to stack. if operand pop from the stack and do
 * operand;
 * */

static int isOperator(char currChar) {
  switch (currChar) {
    case '+':
    case '-':
    case '*':
    case '/':
      return true;
      break;
  }
  return false;
}

void Rpn::parseAndCalc(std::string &input) {
  char mOperator = 0;

  for (size_t i = 0; i < input.length(); ++i) {
    char currChar = input.at(i);

    if (isdigit(currChar)) {
      resDb.push(currChar - '0');
      if (i + 1 < input.length() &&
          (isdigit(input.at(i + 1)) || !isspace(input.at(i + 1))))
        throw std::runtime_error("Error");
    } else if (mOperator == 0 && isOperator(currChar)) {
      if (i + 1 < input.length() && !isspace(input.at(i + 1)))
        throw std::runtime_error("Error");
      mOperator = currChar;
    } else if (!isspace(currChar)) {
      throw std::runtime_error("Error");
    }

    if (mOperator && resDb.size() >= 2) {
      int first = resDb.top();
      resDb.pop();
      int second = resDb.top();
      resDb.pop();

      switch (mOperator) {
        case '+':
          resDb.push(second + first);
          break;
        case '-':
          resDb.push(second - first);
          break;
        case '*':
          resDb.push(second * first);
          break;
        case '/':
          first == 0 ? throw std::runtime_error("Error: division by zero.")
                     : resDb.push(second / first);
          break;
      }
      mOperator = 0;  // Reset the operator
    }

    // test case "1 -"
    if (mOperator != 0) {
      throw std::runtime_error("Error");
    }
  }

  if (resDb.size() != 1) {
    throw std::runtime_error("Error");
  }
}

std::stack<int> Rpn::getResDb() const { return this->resDb; }
