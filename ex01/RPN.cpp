#include "RPN.hpp"
#include <cctype>
#include <stdexcept>

Rpn::Rpn() {}

Rpn::Rpn(const Rpn &rhs) { *this = rhs; }

Rpn &Rpn::operator=(const Rpn &rhs) {
  if (this == &rhs)
    return *this;
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
  // std::string::size_type i = 0;
  // char currChar;
  // char mOperator;

  // while (i < input.length()) {
  //   currChar = input.at(i);

  //   switch (currChar) {
  //   case '+':
  //   case '-':
  //   case '*':
  //   case '/':
  //     mOperator = currChar;
  //     break;
  //   }
  //   if (isdigit(currChar))
  //     this->resDb.push(currChar - '0');
  //   else if (!isOperator(currChar) && !isspace(currChar))
  //     throw std::runtime_error("Error");

  //   if (currChar == mOperator && this->resDb.size() >= 2) {
  //     int first = this->resDb.top();
  //     this->resDb.pop();
  //     int second = this->resDb.top();
  //     this->resDb.pop();

  //     switch (mOperator) {
  //     case '+':
  //       this->resDb.push(second + first);
  //       break;
  //     case '-':
  //       this->resDb.push(second - first);
  //       break;
  //     case '*':
  //       this->resDb.push(second * first);
  //       break;
  //     case '/':
  //       this->resDb.push(second / first);
  //       break;
  //     }
  //   } else if (this->resDb.size() < 2 && currChar == mOperator) {
  //     throw std::runtime_error("Error: invalid size");
  //   }
  //   i++;
  // }
  // if (!mOperator)
  //   throw std::runtime_error("Error: no operator were found");
  char mOperator = 0;

  for (size_t i = 0; i < input.length(); ++i) {
    char currChar = input.at(i);

    if (isdigit(currChar)) {
      resDb.push(currChar - '0');
    } else if (mOperator == 0 && isOperator(currChar)) {
      mOperator = currChar;
    } else if (!isspace(currChar)) {
      throw std::runtime_error("Error");
    }
    // }
    // else {
    //   throw std::runtime_error("Error: invalid character in input.");
    // }
    // if (!isspace(currChar)) {

    //   if (isdigit(currChar)) {
    //     resDb.push(currChar - '0');
    //   } else if (!isspace(currChar)) {
    //     if (mOperator == 0 && isOperator(currChar)) {
    //       mOperator = currChar;
    //     }
    //   }
    // else {
    //       throw std::runtime_error("Error: invalid character in input.");
    //    }

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
        if (first == 0) {
          throw std::runtime_error("Error: division by zero.");
        }
        resDb.push(second / first);
        break;
      }
      mOperator = 0; // Reset the operator
    }
    // test case "1 -"
    if (mOperator != 0) {
      throw std::runtime_error("Error: operator without sufficient operands.");
    }
  }

  if (resDb.size() != 1) {
    throw std::runtime_error("Error: invalid expression.");
  }
}

std::stack<int> Rpn::getResDb() const { return this->resDb; }
