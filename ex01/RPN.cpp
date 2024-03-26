#include "RPN.hpp"
#include <cctype>
#include <cstdlib>
#include <iostream>
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
  std::string::size_type i = 0;
  char currChar;
  char mOperator;

  while (i < input.length()) {
    currChar = input.at(i);

    switch (currChar) {
    case '+':
    case '-':
    case '*':
    case '/':
      mOperator = currChar;
      break;
    }
    if (isdigit(currChar))
      this->resDb.push(currChar - '0');
    else if (!isOperator(currChar) && !isspace(currChar))
      throw std::runtime_error("Error");

    if (currChar == mOperator && this->resDb.size() >= 2) {
      int first = this->resDb.top();
      this->resDb.pop();
      int second = this->resDb.top();
      this->resDb.pop();

      switch (mOperator) {
      case '+':
        this->resDb.push(second + first);
        break;
      case '-':
        this->resDb.push(second - first);
        break;
      case '*':
        this->resDb.push(second * first);
        break;
      case '/':
        this->resDb.push(second / first);
        break;
      }
    }
    i++;
  }
}

std::stack<int> Rpn::getResDb() const { return this->resDb; }
