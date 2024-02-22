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
    line = trim(line);

    if (!validLine(line)) {
      printErr("Not valid line");
    }
  }
  /* Check for valid format "|"*/
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

  if (userInputLine.find(" | ") == userInputLine.npos)
    return false;
  // extracting the two parts
  std::getline(line_stream, date, '|');
  std::getline(line_stream, price);

  /* Checking line for specefique format "date | price"*/
  if (date.find_first_of(" ") != date.find_last_of(" "))
    return false;
  if (price.find_first_of(" ") != price.find_last_of(" "))
    return false;

  date = trim(date);   // space
  price = trim(price); // space

  // std::cout << "Line after trim => '" << userInputLine << "' ." << std::endl;
  // std::cout << "date => '" << date << "' ." << std::endl;
  // std::cout << "price => '" << price << "' ." << std::endl;
  // std::cout << "=============================" << std::endl;

  if (!validDate(date)) {
    printErr("Not a valid date");
    return false;
  }

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

/* validate date and price functions */
bool validDate(std::string &date) {
  (void)date;
  // check the format of the date is valid YYYY-MM-DD YYYY-MM-DD
  std::stringstream ss(date);

  std::string year;
  std::getline(ss, year, '-');

  std::string month;
  std::getline(ss, month, '-');

  std::string day;
  std::getline(ss, day, '-');

  /* first check if all element are full. and in the sepcifque length*/
  if (year.empty() || month.empty() || day.empty())
    return false;
  if (year.length() != 4 || month.length() != 2 || day.length() != 2)
    return false;

  /* validate the date in numbers*/
  std::stringstream converter;

  size_t nYear;
  size_t nMonth;
  size_t nDay;

  nDay = atol(day.c_str());
  nMonth = atol(month.c_str());
  nYear = atol(year.c_str());

  /* check range of year and day and month*/
  if (!(nMonth > 0 && nMonth <= 12)) {
    printErr("Error in month");
    return false;
  }
  /* need to validate day based on the month 2 . and the year if it accepts / on
   * 4 */

  std::cout << "year => '" << year << "' month => '" << month << "' day -> '"
            << day << "' ." << std::endl;

  std::cout << "As intergers -< year => '" << nYear << "' month => '" << nMonth
            << "' day -> '" << nDay << "' ." << std::endl;
  return true;
}

bool validPrice(std::string &price) {
  (void)price;
  // check the format of the price is valid
  return true;
}
