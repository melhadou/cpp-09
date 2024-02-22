#pragma once

#include <map>
#include <string>

class BitcoinExchange {
private:
  std::map<std::string, float> btcDataMap;
  std::map<std::string, float> userInputMap;
  std::string database;
  std::string userInput;
  std::string result;

public:
  BitcoinExchange(std::string &database, std::string &userInput);
  BitcoinExchange(BitcoinExchange const &rhs); // copy constructor
  BitcoinExchange &operator=(BitcoinExchange const &rhs);
  ~BitcoinExchange();

  void extractAndFillData(void);
  void printData(void);
  void parseUserInput(void);
};

// file handlers
bool fileStream(std::string filename, std::string &data);
void printErr(std::string err);

// helpers for validating user input
bool validLine(std::string &userInput);
std::string trim(std::string &str);
