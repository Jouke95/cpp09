#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <map>
#include <string>

class BitcoinExchange {
	private:
		std::map<std::string, double> _database;

		void	loadDatabase(const std::string& filename);
		bool	parseDatabaseLine(const std::string& line, std::string& date, double& value);
		double	getExchangeRate(const std::string& date);

		bool	isValidDate(const std::string& date);
		bool 	checkDateFormat(const std::string& date);
		bool	checkDateValues(int year, int month, int day);

		bool	isValidValue(double value);
		int		extractInt(const std::string& date, int start, int length);
		bool	parseDouble(const std::string& str, double& result);

		
		public:
		BitcoinExchange();
		void processInputFile(const std::string& filename);
		void printDatabase();
};

#endif
