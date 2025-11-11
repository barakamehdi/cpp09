#include "RPN.hpp"
#include <cctype>

RPN::RPN(){}

static bool is_op(char op) {
	return (op == '+' || op == '/' || op == '*' || op == '-');
}

RPN::RPN(std::string input) {
	size_t i = 0;
	while (i < input.size()) {
		unsigned char ch = static_cast<unsigned char>(input[i]);
		if (std::isspace(ch)) {
			++i;
			continue;
		}

		if (std::isdigit(ch)) {
			_stack.push(static_cast<int>(ch - '0'));
			++i;
			if (i < input.size() && std::isdigit(static_cast<unsigned char>(input[i])))
				throw "Error";
			continue;
		}

		if (is_op(ch)) {
			if (_stack.size() < 2)
				throw "Error";
			int b = _stack.top(); _stack.pop();
			int a = _stack.top(); _stack.pop();
			int res = 0;
			switch (ch) {
				case '+': res = a + b; break;
				case '-': res = a - b; break;
				case '*': res = a * b; break;
				case '/':
					if (b == 0) throw "Error";
					res = a / b; break;
				default:
					throw "Error";
			}
			_stack.push(res);
			++i;
			continue;
		}
		throw "Error";
	}
	
	if (_stack.size() != 1)
		throw "Error";

	std::cout << _stack.top() << std::endl;
}

RPN::RPN(RPN const &copy){
	*this = copy;
}

RPN&	RPN::operator=(RPN const &copy){
	if (this != &copy){
		_stack = copy._stack;
	}
	return *this;	
}

RPN::~RPN() {}