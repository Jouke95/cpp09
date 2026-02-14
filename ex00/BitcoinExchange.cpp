#include "BitcoinExchange.hpp"
#include <fstream>
#include <iostream>
#include <sstream>

BitcoinExchange::BitcoinExchange() {
	loadDatabase("data.csv");
}

void BitcoinExchange::loadDatabase(const std::string& filename) {
	std::ifstream file(filename);
	if (!file.is_open()) {
		throw std::runtime_error("Error: could not open file.");
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

bool BitcoinExchange::parseDouble(const std::string& str, double& result) {
	std::stringstream ss(str);
	ss >> result;
	if (ss.fail() || !ss.eof())
		return false;

	return true;
}

bool BitcoinExchange::parseDatabaseLine(const std::string& line, std::string& date, double& exchangeRate) {
	size_t pos = line.find(',');
	if (pos == std::string::npos)
		return false;
	
	date = line.substr(0, pos);
	std::string exchangeRateString = line.substr(pos + 1);

	if (!parseDouble(exchangeRateString, exchangeRate))
		return false;

	if (!isValidDate(date))
		return false;

	if (exchangeRate < 0)
		return false;

	return true;
}

bool BitcoinExchange::isValidDate(const std::string& date) {
	if (!checkDateFormat(date))
		return false;

	int year = extractInt(date, 0, 4);
	int month = extractInt(date, 5, 2);
	int day = extractInt(date, 8, 2);

	return checkDateValues(year, month, day);
}

int BitcoinExchange::extractInt(const std::string& date, int start, int length) {
	std::string substring = date.substr(start, length);
	int value = stoi(substring);
	return value;
}

bool BitcoinExchange::checkDateFormat(const std::string& date) {
	if (date.size() != 10)
		return false;
	if (date[4] != '-' || date[7] != '-')
		return false;

	for (int i = 0; i < 10; i++) {
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


bool BitcoinExchange::isValidValue(double value) {
	return (value >= 0 && value <= 1000);
}

// double BitcoinExchange::getExchangeRate(const std::string& date) {

// }

// void BitcoinExchange::processInputFile(const std::string& filename) {

// }
























void BitcoinExchange::printDatabase() {
	for (std::map<std::string, double>::iterator it = _database.begin(); it != _database.end(); it++) {
		std::cout << it->first << " => " << it->second << std::endl;
	}
}

