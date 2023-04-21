#pragma once

#include <iostream>
#include <sstream>
#include <time.h>

#include <vector>
#include <set>

using std::string;
using std::cout;
using std::endl;
using std::vector;
using std::set;
using std::pair;

class PmergeMe;

typedef void (PmergeMe::*function_p)(void);

class PmergeMe 
{
	private:
		static string _input;
		static string _data;
		static set<int64_t> _set;
		static set<int64_t> _rset;
		static vector<int64_t> _vec;
		static vector<int64_t> _rvec;

		PmergeMe();
		PmergeMe(PmergeMe const &other);
		PmergeMe &operator=(PmergeMe const &other);

	public:
		~PmergeMe();

		static void parse(int ac, char **av);
		template <typename T> static void print_seq(string msg, T &cont);
		template <typename T> static void time(string msg, T (*sort)(void), T &sorted);

		static set<int64_t> sort_set();
		static vector<int64_t> sort_vec();

		static void compare();

		static set<pair<int64_t, int64_t> > make_pairss();
		static vector<pair<int64_t, int64_t> > make_pairsv();
};

template <typename T>
void PmergeMe::print_seq(string msg, T &cont)
{
	cout << msg << "[ ";
	for (typename T::iterator it = cont.begin(); it != cont.end(); it++)
	{
		cout << *it << " ";
	}
	cout << "]" << endl;
}







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