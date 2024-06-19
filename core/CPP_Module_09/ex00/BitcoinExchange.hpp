#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <string>
#include <stdexcept>
#include <algorithm>
#include <deque>
#include <iostream>
#include <fstream>
#include <sstream>
#include <regex>

struct PriceEntry {
    std::string date;
    float price;
};

class BitcoinExchange {
    private:
        std::deque<PriceEntry> priceData;

        int findClosestDateIndex(const std::string& date) const;
        std::string trim(const std::string& str);
        bool isValueValid(const std::string& valueStr, float &value);
        bool isDateValid(const std::string& date);
    public:
        BitcoinExchange();
        BitcoinExchange(const BitcoinExchange&);
        BitcoinExchange& operator=(const BitcoinExchange&);
        ~BitcoinExchange();

        void loadPriceData(const std::string& fileName);
        float getValueOnDate(const std::string& date) const;
        void printResults(std::string filePath);
};

#endif
