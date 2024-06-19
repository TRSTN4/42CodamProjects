#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange() {}

BitcoinExchange::BitcoinExchange(const BitcoinExchange& src) {
    *this = src;
}

BitcoinExchange& BitcoinExchange::operator=(const BitcoinExchange& src) {
    if (this != &src)
        priceData = src.priceData;
    return *this;
}

BitcoinExchange::~BitcoinExchange() {}

void BitcoinExchange::loadPriceData(const std::string& fileName) {
    std::ifstream file(fileName);
    if (!file.is_open())
        throw std::runtime_error("Error: could not open price data file.");

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string date;
        float price;
        // saves date and extracts price
        if (std::getline(iss, date, ',') && iss >> price)
            priceData.push_back({date, price});
    }

    // sort the entries by date. low to high
    std::sort(priceData.begin(), priceData.end(), [](const PriceEntry& a, const PriceEntry& b) {
        return a.date < b.date;
    });
}

int BitcoinExchange::findClosestDateIndex(const std::string& date) const {
    for (size_t i = 0; i < priceData.size(); ++i) {
        if (priceData[i].date > date) {
            if (i > 0)
                return i - 1;
            else
                return 0;
        }
    }
    return priceData.size() - 1;
}

float BitcoinExchange::getValueOnDate(const std::string& date) const {
    if (priceData.empty())
        throw std::runtime_error("Error: no price data loaded.");

    // gets closest price data
    int index = findClosestDateIndex(date);
    // if not exact date is found, then prevent from returning a upper date (like requested in subject)
    if (priceData[index].date > date)
        throw std::runtime_error("Error: date not found");

    return priceData[index].price;
}

bool BitcoinExchange::isDateValid(const std::string& date) {
    // check if date is YYYY-MM-DD format
    std::regex dateRegex(R"(^\d{4}-\d{2}-\d{2}$)");
    if (!std::regex_match(date, dateRegex))
        return false;

    int year, month, day;
    char delim1, delim2;
    std::istringstream iss(date);
    // splits on '-' chars and saves delims, the year, month and day
    iss >> year >> delim1 >> month >> delim2 >> day;
    
    if (delim1 != '-' || delim2 != '-' || year < 2009 || year > 2024 || month < 1 || month > 12 || day < 1 || day > 31)
        return false;

    static const int daysInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (month == 2) {
        // rule 1: a year is a leap year if it is divisible by 4.
        // rule 2: if the year is also divisible by 100, it is not a leap year (overriding rule 1).
        // rule 3: exception to rule 2: if the year is divisible by 400, it is a leap year (overriding Rule 2).
        bool isLeapYear = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);

        int maxDay;
        if (isLeapYear)
            maxDay = 29;
        else
            maxDay = 28;
        if (day > maxDay)
            return false;
        
    } else if (day > daysInMonth[month - 1])
        return false;

    return true;
}

std::string BitcoinExchange::trim(const std::string& str) {
    size_t first = str.find_first_not_of(" \t");
    // if all spaces then just return empty str
    if (first == std::string::npos)
        return "";
    size_t last = str.find_last_not_of(" \t");
    // returns str with removed spaces
    return str.substr(first, (last - first + 1));
}

bool BitcoinExchange::isValueValid(const std::string& valueStr, float &value) {
    try {
        size_t len;
        value = std::stof(valueStr, &len);
        if (len != valueStr.length()) {
            std::cout << "Error: not a number => " << valueStr << "\n";
            return false;
        }
        if (value < 0) {
            std::cout << "Error: not a positive number" << "\n";
            return false;
        }
        if (value > 1000) {
            std::cout << "Error: too large a number\n";
            return false;
        }
        return true;
    } catch (const std::invalid_argument&) {
        std::cout << "Error: not a number => " << valueStr << "\n";
        return false;
    } catch (const std::out_of_range&) {
        std::cout << "Error: too large a number\n";
        return false;
    }
}

void BitcoinExchange::printResults(std::string filePath) {
    std::ifstream inputFile(filePath);

    if (!inputFile.is_open()) {
        std::cout << "Error: could not open file." << "\n";
        return;
    }

    std::string line;
    int lineNum = 0;
    while (std::getline(inputFile, line)) {
        ++lineNum;

        // check header
        if (lineNum == 1 && line != "date | value") {
            std::cout << "Error: invalid input file" << "\n";
            return;
        }
        if (lineNum == 1 && line == "date | value")
            continue;

        std::istringstream iss(line);
        std::string date;
        std::string valueStr;
        
        // saves date and value from input.txt
        if (std::getline(iss, date, '|') && std::getline(iss, valueStr)) {
            date = trim(date);
            valueStr = trim(valueStr);

            if (date.empty() && valueStr.empty()) {
                std::cout << "Error: bad input => " << line << "\n";
                continue;
            }

            if (date.empty()) {
                std::cout << "Error: invalid date: ''" << "\n";
                continue;
            }

            if (valueStr.empty()) {
                std::cout << "Error: invalid value: \"\"" << "\n";
                continue;
            }

            if (!isDateValid(date)) {
                std::cout << "Error: invalid date: '" << date << "'" << "\n";
                continue;
            }

            float value;
            // gets value and more error checks
            if (!isValueValid(valueStr, value))
                continue;

            try {
                float btcValue = getValueOnDate(date);
                std::cout << date << " => " << value << " = " << (value * btcValue) << "\n";
            } catch (const std::exception& e) {
                std::cout << "Error: " << e.what() << "\n";
            }
        } else
            std::cout << "Error: bad input => " << line << "\n";
    }
}
