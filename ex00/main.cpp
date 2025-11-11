#include "BitcoinExchange.hpp"
#include <sstream>
#include <cctype>
#include <cstdio>

void	BTC::parseInput(std::string InputContent){

	size_t pipe_pos = InputContent.find("|");
	if (pipe_pos == std::string::npos) {
		throw std::string("Error: bad input => ") + InputContent;
	}

	_date = InputContent.substr(0, pipe_pos);

	size_t start = _date.find_first_not_of(" \t");
	size_t end = _date.find_last_not_of(" \t");
	
	if (start == std::string::npos) {
		throw std::string("Error: bad input => ") + InputContent;
	}
	
	_date = _date.substr(start, end - start + 1);

	for(size_t i = 0; i < _date.length(); i++){
		if (std::isspace(static_cast<unsigned char>(_date[i])))
			throw std::string("Error: bad input => ") + InputContent;
	}

	int Year, Month, Day;
	if (sscanf(_date.c_str(), "%d-%d-%d", &Year, &Month, &Day) != 3) {
		throw std::string("Error: bad input => ") + InputContent;
	}
	
	if (!parseDate(Year, Month, Day)) {
		throw std::string("Error: bad input => ") + InputContent;
	}

	_value = InputContent.substr(pipe_pos + 1);
	start = _value.find_first_not_of(" \t");
	end = _value.find_last_not_of(" \t");
	
	if (start == std::string::npos) {
		throw std::string("Error: bad input => ") + InputContent;
	}
	
	_value = _value.substr(start, end - start + 1);

	char* endptr;
    float Val = std::strtof(_value.c_str(), &endptr);
    if (endptr == _value.c_str() || (*endptr != '\0' && !std::isspace(static_cast<unsigned char>(*endptr)))) {
		throw std::string("Error: bad input => ") + InputContent;
    }
	
	if (Val < 0) {
		throw std::string("Error: not a positive number.");
	}
	else if (Val > 1000) {
		throw std::string("Error: too large a number.");
	}
}

int main(int ac, char **av){
	if (ac != 2){
		std::cout << "Error: could not open file." << std::endl;
		return 1;
	}
	else{
		try{
			BTC _btc(av[1]);
		}
		catch(const char *msg){
			std::cout << msg << std::endl;
			return 1;
		}
		catch(const std::string &msg) {
			std::cout << msg << std::endl;
			return 1;
		}
	}
	return 0;
}