#pragma once

#include <iostream>

#include <stack>

using std::string;
using std::cout;
using std::endl;
using std::stack;

class RPN 
{
	private:
		static string _input;
		static string _data;
		static stack<int64_t> _ops;

		RPN();
		RPN(RPN const &other);
		RPN &operator=(RPN const &other);

	public:
		~RPN();

		static void eval_char(char c);
		static void calculate(string &input);
};





class inputTooShort : public std::exception {
	const char *what() const throw() {
		return ("Error: The input is too short");
	}
};

class invalidChars : public std::exception {
	const char *what() const throw() {
		return ("Error: The input contains invalid chars");
	}
};

class outOfRange : public std::exception {
	const char *what() const throw() {
		return ("Error: The result is out of the integer range");
	}
};

class invalidNumber : public std::exception {
	const char *what() const throw() {
		return ("Error: A number is invalid");
	}
};

class notEnoughElements : public std::exception {
	const char *what() const throw() {
		return ("Error: Not enough elements on the stack");
	}
};

class tooManyLeft : public std::exception {
	const char *what() const throw() {
		return ("Error: Too many elements left on the stack");
	}
};