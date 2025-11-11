#include "BitcoinExchange.hpp"

void BTC::setVal(std::string Value) {
	_value = Value;
}

void BTC::setDate(std::string Date) {
	_date = Date;
}

BTC::BTC(){
}

BTC::BTC(BTC const &copy){
	*this = copy;
}

float	Calculate(std::string _value, std::string _second){
	float val1 = std::atof(_value.c_str());
	float val2 = std::atof(_second.c_str());
	float _result = val1 * val2;

	return _result;
}

void print(std::map<std::string, std::string> &_map, std::string _date, std::string _value) {
    std::map<std::string, std::string>::iterator it = _map.find(_date);
	if (it != _map.end()){
		float CalculatedVal = Calculate(_value, it->second);
		std::cout << _date << " => " << _value << " = " << CalculatedVal << std::endl;
	}
	else{
		it = _map.lower_bound(_date);
		if (it == _map.begin()) {
			// No earlier date available
			std::cout << "Error: no available data for date => " << _date << std::endl;
			return;
		}
		else{
			--it;
			float CalculatedVal = Calculate(_value, it->second);
			std::cout << _date << " => " << _value << " = " << CalculatedVal << std::endl;
		}
	}
}

BTC::BTC(const char* in_file){
	std::fstream Input(in_file);
	std::fstream _db("data.csv");
	
	if (!_db.is_open())
		throw "Error: could not open database file";
	if (!Input.is_open())
		throw "Error: could not open file";
	
	std::string	InputContent;
	std::string	DataBase;
	std::string key, value;

	while(std::getline(_db, DataBase)){
		if (DataBase == "date,exchange_rate")
			continue;
		size_t comma_pos = DataBase.find(",");
		if (comma_pos == std::string::npos)
			continue;
			
		key = DataBase.substr(0, comma_pos);
		value = DataBase.substr(comma_pos + 1);
		_map[key] = value;
	}
	_db.close();

	std::getline(Input, InputContent);
	if (InputContent != "date | value")
		throw "Error: invalid file format - first line should be 'date | value'";

	while(std::getline(Input, InputContent)){
		if (InputContent.empty())
			continue;
			
		try{
			parseInput(InputContent);
			print(_map, _date, _value);
		}
		catch(const char *msg){
			std::cout << msg << std::endl;
		}
		catch(const std::string &msg){
			std::cout << msg << std::endl;
		}
	}
	Input.close();
}

BTC&	BTC::operator=(BTC const &copy){
	if (this == &copy)
		return *this;
	_date = copy._date;
	_value = copy._value;
	_map = copy._map;
	return *this;
}

BTC::~BTC(){
}

bool	parseDate(int Year, int Month, int Day){
	if (Year < 2009 || Year > 2022)
		return false;
    if (Month < 1 || Month > 12) 
    	return false; 
    if (Day < 1 || Day > 31)
    	return false;

    if (Month == 2){
		if (((Year % 4 == 0) && (Year % 100 != 0)) || (Year % 400 == 0))
        	return (Day <= 29); 
        else
        	return (Day <= 28); 
    }

	if (Month == 4 || Month == 6 || Month == 9 || Month == 11)
        return (Day <= 30);
        
	return true;
}