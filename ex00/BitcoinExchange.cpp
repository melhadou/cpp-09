#include "BitcoinExchange.hpp"
// #include <algorithm>
#include <algorithm>
// #include <cstdio>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <pthread.h>
#include <sstream>
#include <string>

/* ---------- Start of BitcoinExchange Member Funcitons ----------*/

BitcoinExchange::BitcoinExchange(std::string &rawData, std::string &userdata)
    : database(rawData), userInput(userdata) {
  // should extract data and fill it;
  this->extractAndFillData();
  this->parseUserInput();
  // this->printData();
  // parse the user data, if there any prob, throw an apropriate error;
  try {
    // call apropriate function to parse the userInput
  } catch (std::exception &e) {
    printErr(e.what());
  }
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

// Parse the user given input
void BitcoinExchange::parseUserInput(void) {
  /* Check for valid line. format is ->: "date | value" */
  std::stringstream data_stream(this->userInput);
  std::string line;

  while (std::getline(data_stream, line)) {
    // should find a better solotion for this trim
    line = reduce(line);

    if (!validLine(line)) {
      printErr("Not valid line");
    }
  }
  /* Check for valid format "|"*/
}
std::string reduce(std::string &str) {
  // trim first
  const std::string &fill = " ";
  const std::string &whitespace = " \t";

  std::string result = trim(str);

  // replace sub ranges
  size_t beginSpace = result.find_first_of(whitespace);
  while (beginSpace != std::string::npos) {
    size_t endSpace = result.find_first_not_of(whitespace, beginSpace);
    size_t range = endSpace - beginSpace;

    result.replace(beginSpace, range, fill);

    size_t newStart = beginSpace + fill.length();
    beginSpace = result.find_first_of(whitespace, newStart);
  }

  return result;
}

/* ---------- End of BitcoinExchange Member Funcitons ----------*/

/* ---------- Start of user Input parser Functions ----------*/

std::string trim(std::string &str) {
  const std::string &whitespace = " \t";
  size_t strBegin = str.find_first_not_of(whitespace);
  if (strBegin == std::string::npos)
    return ""; // no content

  size_t strEnd = str.find_last_not_of(whitespace);
  size_t strRange = strEnd - strBegin + 1;

  return str.substr(strBegin, strRange);
}

bool validLine(std::string &userInputLine) {
  /* Check for valid line. format is ->: "date | value" */
  std::string date;
  std::string price;
  std::stringstream line_stream(userInputLine);

  std::cout << "=============================" << std::endl;

  if (userInputLine.find("|") == userInputLine.npos) {
    // means no occurrence was found of |
    return false;
  }
  // extracting the two parts
  std::getline(line_stream, date, '|');
  std::getline(line_stream, price);

  date = trim(date);   // space
  price = trim(price); // space

  std::cout << "Line after trim => '" << userInputLine << "' ." << std::endl;
  std::cout << "date => '" << date << "' ." << std::endl;
  std::cout << "price => '" << price << "' ." << std::endl;
  std::cout << "=============================" << std::endl;

  return true;
}

/* ---------- End of user Input parser Functions ----------*/

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
