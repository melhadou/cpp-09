#include "BitcoinExchange.hpp"
#include <algorithm>
// #include <cstdio>
#include <cctype>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>

/* ---------- Start of BitcoinExchange Member Funcitons ----------*/

BitcoinExchange::BitcoinExchange(std::string &rawData, std::string &userdata)
    : database(rawData), userInput(userdata) {
  // should extract data and fill it;
  this->date = "";
  this->value = 0;

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
  this->btcDatabase = rhs.btcDatabase;
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
    this->btcDatabase[date] = price;
  }
}

void BitcoinExchange::printData() {
  std::map<std::string, float>::iterator it;
  for (it = this->btcDatabase.begin(); it != this->btcDatabase.end(); it++) {
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
    line = trim(line);
    try {
      if (!validLine(line)) {
        printErr("Error: bad input => " + line);
      } else {
        this->getRate(this->date, this->value);
      }
    } catch (std::exception &e) {
      std::cerr << e.what() << std::endl;
    }
  }
}

std::string BitcoinExchange::getRate(std::string const &date, float price) {
  BitcoinExchange::iterator it = this->btcDatabase.lower_bound(date);

  if (it == this->btcDatabase.end())
    throw std::runtime_error("Date Not in range");
  if (it->first != date && it != this->btcDatabase.begin())
    it--;

  std::cout << date << " => " << price << " = " << price * it->second
            << std::endl;

  return "";
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

bool BitcoinExchange::validLine(std::string &userInputLine) {
  /* Check for valid line. format is ->: "date | value" */
  std::string date;
  std::string price;
  std::stringstream line_stream(userInputLine);

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

  if (!validDate(date)) {
    throw std::runtime_error("Error: bad input =>" + date);
  } else if (!validValue(price)) {
    return false;
  }
  return true;
}

/* ---------- End of user Input parser Functions ----------*/
static bool checkHeader(std::string header, int type) {
  // type = 2. check for db file
  // type = 1. check for input file
  if (type == 1 && (header.find(" | ") == header.npos))
    return false;
  if (type == 2 && (header.find(",") == header.npos))
    return false;
  return true;
}

// file handlers
bool fileStream(std::string const &fileName, std::string &bufferData) {
  std::ifstream fs;
  std::stringstream ss;

  fs.open(fileName.c_str());
  if (!fs.is_open())
    return false;
  ss << fs.rdbuf();      // reading from file
  bufferData = ss.str(); // writing data to buffer
  fs.close();
  std::string firstLine;
  std::getline(ss, firstLine);
  if (!fileName.compare("data.csv")) {
    size_t count = std::count(firstLine.begin(), firstLine.end(), ',');
		if (firstLine.compare("date,exchange_rate")) 
			throw std::runtime_error("Error: Invalid Header in data.csv");
    if (count != 1 || !checkHeader(firstLine, 2)) {
      printErr("Envalid Header for Database");
      return false;
    }
  } else {
    size_t count = std::count(firstLine.begin(), firstLine.end(), '|');
		if (firstLine.compare("date | value")) 
			throw std::runtime_error("Error: Invalid Header in input file");
    if (count != 1 || !checkHeader(firstLine, 1)) {
      printErr("Envalid Header input file");
      return false;
    }
  }
  bufferData.erase(0, bufferData.find("\n") + 1);
  return true;
}

void printErr(std::string const &err) { std::cerr << err << std::endl; }

/* validate date and price functions */
bool BitcoinExchange::validDate(std::string &date) {
  std::stringstream ss(date);
  std::string year;
  std::getline(ss, year, '-');
  std::string month;
  std::getline(ss, month, '-');
  std::string day;
  std::getline(ss, day, '-');
  if (year.empty() || month.empty() || day.empty())
    return false;
  if (year.length() != 4 || month.length() != 2 || day.length() != 2)
    return false;
  if (!isStrNumber(year) || !isStrNumber(month) || !isStrNumber(day))
    return false;
  size_t nYear = atol(year.c_str());
  size_t nMonth = atol(month.c_str());
  size_t nDay = atol(day.c_str());
  if (!checkDate(nYear, nMonth, nDay))
    return false;
  this->date = year + "-" + month + "-" + day;

  return true;
}

bool BitcoinExchange::validValue(std::string &value) {
  if (!isStrNumber(value))
    throw std::runtime_error("Error: value is not valid");
  float nValue = atof(value.c_str()); // converting str to int
  if (nValue <= 0)
    throw std::runtime_error("Error: not a positive number");
  if (nValue > 1000)
    throw std::runtime_error("Error: too large a number");
  this->value = nValue;
  return true;
}

bool isStrNumber(std::string str) {
  for (size_t i = 0; i < str.length(); i++)
    if (isalpha(str.at(i)))
      return false;
  return true;
}

bool checkDate(size_t year, size_t month, size_t day) {
  if (month < 1 || month > 12)
    return false;
  if (day < 1 || day > 31)
    return false;
  if (month == 2) {
    if (isLeap(year))
      return (day <= 29);
    else
      return (day <= 28);
  }
  if (month == 4 || month == 6 || month == 9 || month == 11)
    return (day <= 30);

  return true;
}

bool isLeap(int year) {
  return (((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0));
}
