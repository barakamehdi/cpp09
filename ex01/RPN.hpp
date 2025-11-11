#pragma once

# include <iostream> 
# include <stack>
# include <iterator>
# include <algorithm>
# include <string>

class RPN{
	private:
		std::stack<int> _stack;
	public:
		RPN();
		RPN(std::string input);
		RPN(RPN const &copy);
		RPN&	operator=(RPN const &copy);
		~RPN();
};