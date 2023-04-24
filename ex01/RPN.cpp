#include "RPN.hpp"

using std::string;
using std::cout;
using std::endl;

stack<int64_t> RPN::_ops;

RPN::~RPN()
{

}

std::string trim(const std::string &s)
{
	if (s.empty())
		return "";
	size_t front_pos = s.find_first_not_of(" \t\r\n");
	size_t back_pos = s.find_last_not_of(" \t\r\n");

	if (front_pos == std::string::npos || back_pos == std::string::npos)
		return "";

	return s.substr(front_pos, back_pos - front_pos + 1);
}

bool	is_only(string s, string chars)
{
	for (uint32_t i = 0; i < s.length(); i++)
	{
		if (chars.find(s[i]) == string::npos)
			return (false);
	}
	return (true);
}

void RPN::eval_char(char c)
{
	if (isdigit(c))
		_ops.push(c - '0');
	else if (_ops.size() < 2)
		throw notEnoughElements();
	else
	{
		int_fast64_t left = _ops.top();
		_ops.pop();
		int_fast64_t right = _ops.top();
		_ops.pop();
		if 		(c == '+') _ops.push(right + left);
		else if (c == '-') _ops.push(right - left);
		else if (c == '*') _ops.push(right * left);
		else if (c == '/') _ops.push(right / left);
		else
			throw invalidChars();
	}
}

void RPN::calculate(string &input)
{
	string trimmed = trim(input);

	if (trimmed.size() < 3) throw inputTooShort();
	if (!is_only(input, " -+/*0123456789")) throw invalidChars();
	
	for (string::iterator it = input.begin(); it != input.end(); it++)
	{
		if (*it == ' ') continue;

		eval_char(*it);
	}

	if (_ops.size() != 1) throw tooManyLeft();

	int64_t res = _ops.top();
	if (res < INT_MIN || res > INT_MAX) throw outOfRange();

	cout << res << endl;
}