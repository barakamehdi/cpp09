#ifndef BITCOINEXCHANGE_HPP
# define BITCOINEXCHANGE_HPP

#include <map>
#include <cfloat>
#include <string>
#include <sstream>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <stdlib.h>
#include <algorithm>
#include <sys/stat.h>
#include <sys/types.h>

class BitcoinExchange
{
	private:
		std::string _filename;
		std::map<std::string, float> _values;

	public:
		BitcoinExchange();
		BitcoinExchange(std::string filename);
		BitcoinExchange(BitcoinExchange const &obj);
		BitcoinExchange& operator=(BitcoinExchange const &rhs);
		~BitcoinExchange();

		std::string getFilename(char *filename);
		void		openfile();
		bool		checkValue(std::string str);
		bool		dateFormat(std::string year, std::string month, std::string date);
		bool		checkDate(std::string str);
		bool		checkLine(std::string str);
		std::string	debug(std::string &date);
		std::string	fileParse(std::string const filename);
		void		calculate(std::string &rate);

	class FileIssues: public std::exception
	{
		private:
			std::string errorFault;
		public:
			FileIssues(std::string error);
			const char *what() const throw() ;
			virtual ~FileIssues() throw();
	};
};

#endif
