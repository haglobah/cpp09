#pragma once

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

#include <map>
#include <list>

using std::string;
using std::cout;
using std::endl;
using std::map;

class BitcoinExchange 
{
	private:
		static string _input;
		static string _data;
		static map<string, double> _date_price;

		BitcoinExchange();
		BitcoinExchange(BitcoinExchange const &other);
		BitcoinExchange &operator=(BitcoinExchange const &other);

	public:
		~BitcoinExchange();

		static std::pair<string, double> parse_line(string &file);
		
		static void print_db();
		static void load_db();

		static void print_values(string &file);
};






class acessDenied : public std::exception {
	const char *what() const throw() {
		return ("Error: Access denied");
	}
};

class couldNotOpen : public std::exception {
	const char *what() const throw() {
		return ("Error: Could not open file");
	}
};

class fileIsEmpty : public std::exception {
	const char *what() const throw() {
		return ("Error: File is empty");
	}
};

class lineInWrongFormat : public std::exception {
	const char *what() const throw() {
		return ("Error: A line is in the wrong format");
	}
};

class invalidDate : public std::exception {
	const char *what() const throw() {
		return ("Error: A date is invalid");
	}
};