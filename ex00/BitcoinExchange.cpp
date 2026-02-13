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
		double value;

		if (!parseDatabaseLine(line, date, value)) {
			std::cerr << "Warning: skipping invalid line in database\n";
			continue;
		}
		_database[date] = value;
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

	if (!isValidValue(value))
		return false;

	return true;
}

bool BitcoinExchange::isValidDate(const std::string& date) {

}

bool BitcoinExchange::isValidValue(double value) {

}

double BitcoinExchange::getExchangeRate(const std::string& date) {

}

void BitcoinExchange::processInputFile(const std::string& filename) {

}
