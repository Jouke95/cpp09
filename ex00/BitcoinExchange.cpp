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

	int line_counter = 2;
	while (std::getline(file, line)) {
		std::string date;
		double value;

		if (!parseDatabaseLine(line, date, value)) {
			std::cerr << "Warning: skipping invalid line number " << line_counter << " in database\n";
			continue;
		}
		_database[date] = value;
		line_counter++;
	}
}

bool BitcoinExchange::parseDatabaseLine(const std::string& line, std::string& date, double& value) {
	size_t pos = line.find(',');
	if (pos == std::string::npos)
		return false;
	
	date = line.substr(0, pos);
	std::string valueString = line.substr(pos + 1);
	std::stringstream ss(valueString);
	ss >> value;
	if (ss.fail() || !ss.eof())
		return false;

	if (!isValidDate(date))
		return false;

	if (value < 0)
		return false;

	return true;
}

bool BitcoinExchange::isValidDate(const std::string& date) {
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

	std::string year = date.substr(0, 4);
	std::string month = date.substr(5, 2);
	std::string day = date.substr(8, 2);

	int _year = std::stoi(year);
	int _month = std::stoi(month);
	int _day = std::stoi(day);

	if (_year < 1900 || _year > 2100)
		return false;
	if (_month < 1 || _month > 12)
		return false;
	if (_day < 1 || _day > 31)
		return false;

	int daysInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

	if ((_year % 4 == 0 && _year % 100 != 0) || (_year % 400 == 0))
		daysInMonth[1] = 29;

	if (_day > daysInMonth[_month - 1])
		return false;

	return true;
}

bool BitcoinExchange::isValidValue(double value) {
	return (value >= 0 && value <= 1000);
}

double BitcoinExchange::getExchangeRate(const std::string& date) {

}

void BitcoinExchange::processInputFile(const std::string& filename) {

}


























