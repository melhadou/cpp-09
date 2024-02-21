#include "BitcoinExchange.hpp"
// #include <algorithm>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

/* ---------- Start of BitcoinExchange Member Funcitons ----------*/

BitcoinExchange::BitcoinExchange(std::string &rawData) : database(rawData) {
  // should extract data and fill it;
  this->extractAndFillData();
  this->printData();
}

BitcoinExchange::BitcoinExchange(BitcoinExchange const &rhs) { *this = rhs; }

BitcoinExchange &BitcoinExchange::operator=(BitcoinExchange const &rhs) {
  if (this == &rhs)
    return *this;
  this->database = rhs.database;
  this->btcDataMap = rhs.btcDataMap;
  return *this;
}

BitcoinExchange::~BitcoinExchange() {}

void BitcoinExchange::extractAndFillData() {
  /* Should parse the data. and fill the date and price*/
  std::stringstream data_stream(this->database);
  std::string date;
  std::string line;

  float price = 0;
  while (std::getline(data_stream, line)) {
    std::stringstream line_stream(line);
    std::string price_str;

    // Use comma as delimiter to extract date and price
    std::getline(line_stream, date, ',');
    std::getline(line_stream, price_str);

    price = atof(price_str.c_str());
    this->btcDataMap[date] = price;
  }
}

void BitcoinExchange::printData() {
  std::map<std::string, float>::iterator it;
  for (it = this->btcDataMap.begin(); it != this->btcDataMap.end(); it++) {
    std::cout << "Date: => '" << it->first << "' : price => '" << it->second
              << "' ." << std::endl;
  }
}

/* ---------- End of BitcoinExchange Member Funcitons ----------*/

// file handlers
bool fileStream(std::string fileName, std::string &bufferData) {
  std::ifstream fs;
  std::stringstream ss;

  fs.open(fileName.c_str());
  if (!fs.is_open())
    return false;
  ss << fs.rdbuf();      // reading from file
  bufferData = ss.str(); // writing data to buffer

  /* TODO: check first line is there and number of colomns */
  bufferData.erase(0, bufferData.find("\n") + 1);
  return true;
}

void printErr(std::string err) { std::cerr << err << std::endl; }

// not used for now
bool checkFileExtention(std::string &fileName, std::string &extension) {
  int len;

  len = fileName.length();
  try {

    std::string checkAgainst(fileName.substr(len - 4));

    if (len > 4) {
      if (!extension.compare(checkAgainst)) {
        return (0);
      }
    }
    printErr("invalid file extension");
  } catch (std::exception &e) {
    printErr("invalid file extension");
    return 1;
  }
  return true;
}
