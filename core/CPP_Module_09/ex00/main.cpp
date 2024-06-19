#include "BitcoinExchange.hpp"

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cout << "./btc <file>\n";
        return 1;
    }

    try {
        BitcoinExchange btcExchange;
        btcExchange.loadPriceData("data.csv");
        btcExchange.printResults(argv[1]);
    } catch (const std::exception& e) {
        std::cout << "Error: " << e.what() << "\n";
        return 1;
    }

    return 0;
}
