#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <map>
#include <string>
#include <sstream>

class BitcoinExchange {
	private:
		std::map<std::string, double> _database;

		void	loadDatabase(const std::string& filename);
		bool	parseDatabaseLine(const std::string& line, std::string& date, double& value);
		bool	searchExchangeRate(const std::string& date, double& rate);
		bool	parseInputFileLine(const std::string& line, std::string& date, std::string& value);

		bool	isValidDate(const std::string& date);
		bool 	checkDateFormat(const std::string& date);
		bool	checkDateValues(int year, int month, int day);

		bool	extractInt(const std::string& date, int start, int length, int& result);
		std::string	trimWhitespaces(const std::string& str);

		template <typename T>
		bool parse(const std::string& str, T& result) {
			std::stringstream ss(str);
			ss >> result;
			if (ss.fail() || !ss.eof())
				return false;
			return true;
		}

		BitcoinExchange(const BitcoinExchange& other);
		BitcoinExchange& operator=(const BitcoinExchange& other);

	public:
		BitcoinExchange();
		~BitcoinExchange();
		void processInputFile(const std::string& filename);
};

#endif
