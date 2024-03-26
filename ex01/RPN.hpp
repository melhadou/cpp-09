#pragma once

#include <stack>
#include <string>
class Rpn {
private:
  std::stack<int> resDb;

public:
  Rpn();
  Rpn(const Rpn &rhs);
  Rpn &operator=(const Rpn &rhs);
  ~Rpn();

  void parseAndCalc(std::string &input);
  std::stack<int> getResDb() const;
};
