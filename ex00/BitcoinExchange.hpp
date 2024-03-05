#pragma once

#include <map>
#include <string>

class BitcoinExchange {
private:
  std::map<std::string, float> btcDatabase;
  std::map<std::string, float> userInputMap;
  std::string database;
  std::string userInput;
  std::string date;
  float value;

public:
  BitcoinExchange(std::string &database, std::string &userInput);
  BitcoinExchange(BitcoinExchange const &rhs); // copy constructor
  BitcoinExchange &operator=(BitcoinExchange const &rhs);
  ~BitcoinExchange();

  void extractAndFillData(void);
  void printData(void);
  void parseUserInput(void);

  bool validDate(std::string &date);
  bool validValue(std::string &value);
  bool validLine(std::string &userInput);

  std::string getRate(std::string const &date, float price); // getting data

  // iterator for BitcoinExchange
  typedef std::map<std::string, float>::iterator iterator;
};

// file handlers
bool fileStream(std::string const &filename, std::string &data);
void printErr(std::string const &err);

// helpers for validating user input
std::string trim(std::string &str);

// validate date and price functions
bool isStrNumber(std::string str);
bool checkDate(size_t year, size_t month, size_t day);
bool isLeap(int year);
