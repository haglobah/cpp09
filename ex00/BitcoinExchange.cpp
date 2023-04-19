#include "BitcoinExchange.hpp"

using std::string;
using std::cout;
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

list<string>	split(string str, char delim)
{
	list<string>	strList;
	string			u;

	std::istringstream sstream(str);
    while (getline(sstream, u, delim))
		strList.push_back(u);
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

bool validate_date(int year, int month, int day) {
	if (year < 2009 || year > 2023 || month < 1 || month > 12 || day < 1)
		return false;
	if (month == 2) {
		if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) //calculating leap year
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
	list<string> yyyymmdd = split(date, '-');

	if (yyyymmdd.size() != 3)
		return (false);

	int year = s_to_i(yyyymmdd.front());
	yyyymmdd.pop_front();
	int month = s_to_i(yyyymmdd.front());
	int day = s_to_i(yyyymmdd.back());
	return (validate_date(year, month, day));
}

std::pair<string, double> BitcoinExchange::parse_line(string &line)
{
	list<string> fields = split(line, ',');

	if (fields.size() != 2)
		throw lineInWrongFormat();
	string date = fields.front();
	string value = fields.back();

	if (!date_valid(date))		throw invalidDate();

	double	val = s_to_d(value);
	std::pair<string, double> ret(date, val);
	return (ret);
}

void BitcoinExchange::load_db()
{
	std::ifstream data_csv(data_path);
	
	if (!data_csv.good())		throw couldNotOpen();
	if (data_csv.eof())			throw fileIsEmpty();

	string line;

	getline(data_csv, line);
	while (getline(data_csv, line))
	{
		std::pair<string, double> parsed = parse_line(line);
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

void BitcoinExchange::print_values(string &file_path)
{
	(void)file_path;

	BitcoinExchange::load_db();
	BitcoinExchange::print_db();
}
