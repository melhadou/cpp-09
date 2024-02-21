#pragma once

#include <map>
#include <string>

class BitcoinExchange {
private:
  std::map<std::string, float> btcDataMap;
  std::string database;

public:
  BitcoinExchange(std::string &database);
  BitcoinExchange(BitcoinExchange const &rhs); // copy constructor
  BitcoinExchange &operator=(BitcoinExchange const &rhs);
  ~BitcoinExchange();

  void extractAndFillData(void);
  void printData(void);
};

// file handlers
bool fileStream(std::string filename, std::string &data);
void printErr(std::string err);

// not used
bool checkFileExtention(std::string fileName, std::string extention);
