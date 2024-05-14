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

  try {
    // reading data from file
    if (!fileStream("data.csv", btcData)) {
      printErr("Error: could not open the Database file");
      return 1;
    }
    if (!fileStream(av[1], userData)) {
      printErr("Error: could not open the user input file");
      return 1;
    }

    BitcoinExchange btc(btcData, userData);
  } catch (std::exception &e) {
    printErr(e.what());
  }

  return 0;
}
