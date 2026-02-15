#include "BitcoinExchange.hpp"
#include <fstream>
#include <iostream>

BitcoinExchange::BitcoinExchange() {
	loadDatabase("data.csv");
}

void BitcoinExchange::loadDatabase(const std::string& filename) {
	std::ifstream file(filename);
	if (!file.is_open()) {
		throw std::runtime_error("Error: could not open file (data.csv).");
	}

	// skip header line in database
	std::string line;
	std::getline(file, line);

	while (std::getline(file, line)) {
		std::string date;
		double exchangeRate;

		if (!parseDatabaseLine(line, date, exchangeRate))
			continue;

		_database[date] = exchangeRate;
	}
}

bool BitcoinExchange::parseDatabaseLine(const std::string& line, std::string& date, double& exchangeRate) {
	size_t pos = line.find(',');
	if (pos == std::string::npos)
		return false;
	
	date = line.substr(0, pos);
	std::string exchangeRateString = line.substr(pos + 1);

	if (!isValidDate(date))
		return false;

	if (!parse(exchangeRateString, exchangeRate))
		return false;
		
	if (exchangeRate < 0)
		return false;

	return true;
}

bool BitcoinExchange::isValidDate(const std::string& date) {
	if (!checkDateFormat(date))
		return false;

	int year, month, day;
	if (!extractInt(date, 0, 4, year))
		return false;
	if (!extractInt(date, 5, 2, month))
		return false;
	if (!extractInt(date, 8, 2, day))
		return false;

	return checkDateValues(year, month, day);
}

bool BitcoinExchange::extractInt(const std::string& date, int start, int length, int& result) {
	std::string substring = date.substr(start, length);
	if (!parse(substring, result))
		return false;
	return true;
}

bool BitcoinExchange::checkDateFormat(const std::string& date) {
	if (date.size() != 10)
		return false;
	if (date[4] != '-' || date[7] != '-')
		return false;

	for (size_t i = 0; i < date.size(); i++) {
		if (i == 4 || i == 7)
			continue;
		if (!isdigit(date[i]))
			return false;
	}

	return true;
}

bool BitcoinExchange::checkDateValues(int year, int month, int day) {
	if (year < 1900 || year > 2100)
		return false;
	if (month < 1 || month > 12)
		return false;
	if (day < 1 || day > 31)
		return false;

	int daysInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

	// leap year
	if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))
		daysInMonth[1] = 29;

	if (day > daysInMonth[month - 1])
		return false;

	return true;
}

void BitcoinExchange::processInputFile(const std::string& filename) {
	std::ifstream file(filename);
	if (!file.is_open()) {
		throw std::runtime_error("Error: could not open input file.");
	}

	// skip header line in inputfile
	std::string line;
	std::getline(file, line);

	while(std::getline(file, line)) {
		std::string date;
		std::string valueStr;

		if (!parseInputFileLine(line, date, valueStr)) {
			std::cout << "Error: bad input => " << line << std::endl;
			continue;
		}

		double value;
		if (!parse(valueStr, value)) {
			std::cout << "Error: bad input => " << line << std::endl;
			continue;
		}

		if (!isValidDate(date)) {
			std::cout << "Error: bad input => " << line << std::endl;
			continue;
		}

		if (value < 0) {
			std::cout << "Error: not a positive number." << std::endl;
			continue;
		}
		if (value > 1000) {
			std::cout << "Error: too large a number." << std::endl;
			continue;
		}

		double exchangeRate;
		if (!searchExchangeRate(date, exchangeRate)) {
			std::cout << "Error: date is from before bitcoin existed" << std::endl;
			continue;
		}

		double result = exchangeRate * value;
		std::cout << date << " => " << value << " = " << result << std::endl;
	}
}

std::string BitcoinExchange::trimWhitespaces(const std::string& str) {
	size_t start = str.find_first_not_of(" \t");
	size_t end = str.find_last_not_of(" \t");

	if (start == std::string::npos)
		return "";

	return str.substr(start, end - start + 1);
}

bool BitcoinExchange::parseInputFileLine(const std::string& line, std::string& date, std::string& valueStr) {
	size_t pos = line.find('|');
	if (pos == std::string::npos)
		return false;

	date = line.substr(0, pos);
	valueStr = line.substr(pos + 1);

	date = trimWhitespaces(date);
	valueStr = trimWhitespaces(valueStr);

	return true;
}

bool BitcoinExchange::searchExchangeRate(const std::string& date, double& rate) {
	std::map<std::string, double>::iterator it = _database.lower_bound(date);

	if (it != _database.end() && it->first == date) {
		rate = it->second;
		return true;
	}
	if (it == _database.begin()) {
		return false;
	}

	--it;
	rate = it->second;
	return true;
}
