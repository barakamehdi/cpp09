#include "RPN.hpp"

int main(int ac, char **av){
	if (ac != 2){
		std::cerr << "Error" << std::endl;
		return 1;
	}
	try{
		RPN _rpn(av[1]);
	}
	catch(const char *msg){
		std::cerr << msg << std::endl;
		return 1;
	}
	return 0;
}