#include "BitcoinExchange.hpp"

using std::string;
using std::cout;
using std::cerr;
using std::endl;
using std::getline;

using std::list;

string BitcoinExchange::_input;
string BitcoinExchange::_data;
map<string, double> BitcoinExchange::_date_price;

namespace {
	string const data_path = "data.csv";
}

BitcoinExchange::~BitcoinExchange()
{

}

// HELPERS
bool contains(string &haystack, string const &needles)
{
	for (uint32_t i = 0; i < needles.length(); i++)
	{
		if (haystack.find(needles[i]) != string::npos)
			return (true);
	}
	return (false);
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

string	trim(string &s)
{
	size_t 	front_pos;
	size_t 	back_pos;

	if (s.empty())
		return ("");
	front_pos = s.find_first_not_of(" ");
	if (front_pos == string::npos)
		return (s);
	back_pos = s.find_last_not_of(" ");
	if (front_pos != back_pos)
		s = s.substr(front_pos, back_pos + 1);
	return (s);
}

list<string>	split(string str, char delim)
{
	list<string>	strList;
	string			u;

	std::istringstream sstream(str);
    while (getline(sstream, u, delim))
	{
		strList.push_back(trim(u));
	}
	return (strList);
}

int 	s_to_i(string s)
{
	int num;

	std::istringstream ss(s);
	ss >> num;
	return num;
}

double 	s_to_d(string s)
{
	double num;

	std::istringstream ss(s);
	ss >> num;
	return num;
}

void printerr(string msg)
{
	cerr << "Error: " << msg << endl << endl;
}

void printquery(int i, string &date, string &amount, double quantity, std::pair<string, double> nearest)
{
	cout << "Query " << std::setw(2) << i << ": " << date << " | " << amount << "\n        > "
		<< nearest.first << " | " << nearest.second << " => " << quantity * nearest.second << endl << endl;
}

bool validate_date(int year, int month, int day) {
	if (year < 2009 || year > 2023 || month < 1 || month > 12 || day < 1)
		return false;
	if (month == 2) {
		if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))
			return day <= 29;
		else
			return day <= 28;
	}
	else if (month == 4 || month == 6 || month == 9 || month == 11)
		return day <= 30;
	else
		return day <= 31;
}

bool	date_valid(string date)
{
	if (!is_only(date, "-0123456789"))	return (false);

	list<string> yyyymmdd = split(date, '-');

	if (yyyymmdd.size() != 3)
	{
		cout << date << endl;
		return (false);
	}

	int year = s_to_i(yyyymmdd.front());
	yyyymmdd.pop_front();
	int month = s_to_i(yyyymmdd.front());
	int day = s_to_i(yyyymmdd.back());
	// cout << year << "-" << month << "-" << day << endl;
	return (validate_date(year, month, day));
}

std::pair<string, double> BitcoinExchange::parse_line(string &line, char delim)
{
	list<string> fields = split(line, delim);

	if (fields.size() != 2)
	{
		throw lineInWrongFormat();
	}
	string date = fields.front();
	string price = fields.back();

	if (!date_valid(date))				throw invalidDate();
	if (!is_only(price, ".0123456789"))	throw invalidNumber();

	double	val = s_to_d(price);
	std::pair<string, double> ret(date, val);
	return (ret);
}

void BitcoinExchange::load_db()
{
	std::ifstream data_csv(data_path.c_str());
	
	if (!data_csv.good())		throw couldNotOpen();
	if (data_csv.eof())			throw fileIsEmpty();

	string line;

	getline(data_csv, line);
	while (getline(data_csv, line))
	{
		std::pair<string, double> parsed = parse_line(line, ',');
		_date_price.insert(parsed);
	}

	data_csv.close();
}

void BitcoinExchange::print_db()
{
	cout << "[ ";
	for (map<string, double>::iterator it = _date_price.begin(); it != _date_price.end(); it++)
	{
		cout << it->first << " : " << it->second << endl;
	}
	cout << "]" << endl;
}

void printlist(list<string> l)
{
	cout << "[ ";
	for (list<string>::iterator it = l.begin(); it != l.end(); it++)
	{
		cout << *it << " "; 
	}
	cout << "]" << endl;
}

std::pair<string, double> BitcoinExchange::find_date(string &date)
{
	map<string, double>::iterator it = _date_price.begin();
	for (; it != _date_price.end(); it++)
	{
		if (it->first > date)
			return ((it == _date_price.begin()) ? *it : *--it);
	}
	return (*it);
}

void BitcoinExchange::parse_input_line(string &line, char delim, int i)
{
	list<string> fields = split(line, delim);

	if (fields.size() != 2) return (printerr("Line is invalid: " + line));

	string date = fields.front();
	string amount = fields.back();

	if (!date_valid(date)) return (printerr("Date is invalid: " + date));
	if (!is_only(amount, "-.0123456789"))	return (printerr("Number is invalid: " + amount));

	if (!(amount.find(".") != std::string::npos))
	{
		int	val = s_to_i(amount);
		if (val < 0 || val > 1000)
			return (printerr("Amount not in the specified range [0, 1000]: " + amount));
	}
	double	quantity = s_to_d(amount);
	std::pair<string, double> nearest = find_date(date);
	printquery(i, date, amount, quantity, nearest);
}

void BitcoinExchange::calculate_valuations(string &input_path)
{
	std::ifstream input_txt(input_path.c_str());
	
	if (!input_txt.good())		throw couldNotOpen();
	if (input_txt.eof())		throw fileIsEmpty();

	string line;
	int i = 0;

	getline(input_txt, line);
	while (getline(input_txt, line))
	{
		i++;
		parse_input_line(line, '|', i);
	}

	input_txt.close();
}

void BitcoinExchange::print_values(string &input_path)
{
	load_db();
	calculate_valuations(input_path);
	
}
