#include "BitcoinExchange.hpp"
// #include <iostream>

int main(int ac, char *av[]) {

  std::string btcData;
  std::string userData;

  // handle file inpute
  if (ac != 2) {
    printErr("Error: couldn't open the file, Try ./btc filename.");
    return 1;
  }

  // reading data from file
  if (!fileStream("mini_data.csv", btcData)) {
    printErr("Error: could not open the Database file");
    return 1;
  }
  if (!fileStream(av[1], userData)) {
    printErr("Error: could not open the user input file");
    return 1;
  }

  BitcoinExchange btc(btcData);

  return 0;
}
