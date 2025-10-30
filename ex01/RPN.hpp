
#ifndef RPN_HPP
# define RPN_HPP

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

class	RPN
{
	private:
		std::stack<int> _number;

	public:
		RPN ();
		RPN (RPN const &object);
		RPN &operator=(RPN const &rhs);
		~RPN();

		int		calculate(int c, int c2, int flag);
		void	exec(char *str);
};

class	Errorclass: public std::exception
{
	public:
		const char *what() const throw();
};

enum	flag
{
	e_plus = '+',
	e_minus = '-',
	e_divide = '/',
	e_multiply = '*'
};

#endif
