#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <map>
#include <string>

class BitcoinExchange {
	private:
		std::map<std::string, double> _database;

		void loadDatabase(const std::string& filename);
		bool parseDatabaseLine(const std::string& line, std::string& date, double& value);
		bool isValidDate(const std::string& date);
		bool isValidValue(double value);
		double getExchangeRate(const std::string& date);

	public:
		BitcoinExchange();
		void processInputFile(const std::string& filename);
};

#endif
