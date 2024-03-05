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
    // should find a better solotion for this trim
    line = trim(line);

    if (!validLine(line)) {
      printErr("\tNot valid lin");
      // throw runtime_error("Error: not valid line");
    } else {
      this->getRate(this->date, this->value);
    }
    // std::cout << "date ->> " << this->date << " value of ->> " << this->value
    //           << std::endl;
  }
  /* Check for valid format "|"*/
}

std::string BitcoinExchange::getRate(std::string const &date, float price) {
  // date type => '2012-11-02'
  // look for date in the db, if not found look for nearby -1,
  // after that return the price on bined with the date.
  // calculate the rate of the btc needed, and contruct a proper string to be
  // returned.
  // else if date was not found throw of date not in range.
  // std::cout << "date ->> " << date << " value of ->> " << price << std::endl;

  BitcoinExchange::iterator it = this->btcDatabase.lower_bound(date);

  if (it == this->btcDatabase.end())
    throw std::runtime_error("Date Not in range");
  if (it->first != date && it != this->btcDatabase.begin())
    it--;

  std::cout << "date-> '" << it->first << "', price -> '" << it->second * price
            << "' ." << std::endl;

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

  // std::cout << "Line after trim => '" << userInputLine << "' ." << std::endl;
  // std::cout << "date => '" << date << "' ." << std::endl;
  // std::cout << "price => '" << price << "' ." << std::endl;
  // std::cout << "=============================" << std::endl;

  std::cout << "=============================" << std::endl;
  if (!validDate(date)) {
    printErr("Not a valid date");
    return false;
  }
  std::cout << "=============================" << std::endl;
  if (!validValue(price)) {
    printErr("Not a valid price");
    return false;
  }

  // store the required price and date to acces them later

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

  /* TODO: check first line is there and number of colomns */
  std::string firstLine;
  std::getline(ss, firstLine);
  // type = 2. check for db file
  // type = 1. check for input file
  // std::cout << fileName << std::endl;
  if (!fileName.compare("data.csv")) {
    size_t count = std::count(firstLine.begin(), firstLine.end(), ',');
    // std::cout << count << " of ," << std::endl;
    if (count != 1 || !checkHeader(firstLine, 2)) {
      printErr("Envalid Header for Database");
      return false;
    }
  } else {
    size_t count = std::count(firstLine.begin(), firstLine.end(), '|');
    // std::cout << count << " of |" << std::endl;
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
  if (!isStrNumber(year) || !isStrNumber(month) || !isStrNumber(day))
    return false;

  // as a string. check day if its valid based on the given month
  size_t nYear = atol(year.c_str());
  size_t nMonth = atol(month.c_str());
  size_t nDay = atol(day.c_str());

  /* check range of year and day and month*/

  /* need to validate day based on the month 2 .
   * and the year if it accepts / on
   * 4 */
  if (!checkDate(nYear, nMonth, nDay))
    return false;

  // std::cout << "year => '" << year << "' month => '" << month << "' day -> '"
  //           << day << "' ." << std::endl;

  // store the date as a string
  this->date = year + "-" + month + "-" + day;

  return true;
}

bool BitcoinExchange::validValue(std::string &value) {
  float nValue = atof(value.c_str()); // converting str to int
  //
  if (nValue <= 0 || nValue > 1000)
    return false;

  // std::cout << "As intergers -< price => '" << nValue << "' str -> price ->
  // '"
  //           << value << "' ." << std::endl;

  // storing the value
  this->value = nValue;
  return true;
}

bool isStrNumber(std::string str) {
  for (size_t i = 0; i < str.length(); i++)
    if (!isdigit(str.at(i)))
      return false;
  return true;
}

bool checkDate(size_t year, size_t month, size_t day) {
  if (month < 1 || month > 12)
    return false;
  if (day < 1 || day > 31)
    return false;

  // Handle February month
  // with leap year
  if (month == 2) {
    if (isLeap(year))
      return (day <= 29);
    else
      return (day <= 28);
  }

  // Months of April, June,
  // Sept and Nov must have
  // number of days less than
  // or equal to 30.
  if (month == 4 || month == 6 || month == 9 || month == 11)
    return (day <= 30);

  return true;
}

bool isLeap(int year) {
  // Return true if year
  // is a multiple of 4 and
  // not multiple of 100.
  // OR year is multiple of 400.
  return (((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0));
}
