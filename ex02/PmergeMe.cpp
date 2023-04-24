#include "PmergeMe.hpp"

using std::istringstream;
using std::string;
using std::cout;
using std::endl;
using std::vector;
using std::set;

set<int64_t> PmergeMe::_set;
set<int64_t> PmergeMe::_rset;
vector<int64_t> PmergeMe::_vec;
vector<int64_t> PmergeMe::_rvec;

PmergeMe::~PmergeMe()
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

bool find(vector<int64_t> v, int64_t num)
{
	for (vector<int64_t>::iterator it = v.begin(); it != v.end(); ++it)
	{
		if (*it == num)
			return (true);
	}
	return (false);
}

void PmergeMe::parse(int ac, char **av)
{
	for (int i = 1; i < ac; i++)
	{
		string s_num = av[i];
		if (!is_only(s_num, "0123456789")) throw invalidChars();
		
		int64_t num;
		std::istringstream ss(s_num);
		ss >> num;

		if (num > INT_MAX) throw invalidNumber();
		if (!find(_vec, num))
			_vec.push_back(num);
		_set.insert(num);
	}
}

void print_time(uint64_t start, uint64_t end, string msg = "")
{
	double duration = double(end - start) / CLOCKS_PER_SEC;

	cout << msg <<
		((duration > 10000) ? duration / 1000 : duration) <<
		((duration > 10000) ? "ms" : "µs") << endl;
}

template <typename T>
void PmergeMe::time(string msg, T (*sort)(void), T &sorted)
{
	clock_t start = clock();
	sorted = sort();
	clock_t end = clock();

	print_seq(msg, sorted);
	print_time(start, end);
}

void PmergeMe::compare()
{
	print_seq("Before: ", _vec);

	time("Sorting std::set: ", &sort_set, _rset);
	time("Sorting std::vec: ", &sort_vec, _rvec);
}

void pair_insert(vector<pair<int64_t, int64_t> > &pairs, pair<int64_t, int64_t> &p)
{
	for (vector<pair<int64_t, int64_t> >::iterator it = pairs.begin(); it != pairs.end(); ++it)
	{
		if (it->first > p.first)
		{
			pairs.insert(it, p);
			return ;
		}
	}
	pairs.push_back(p);
}

vector<pair<int64_t, int64_t> > &PmergeMe::make_pairsv(vector<pair<int64_t, int64_t> > &pairs)
{
	int64_t a;
	pair<int64_t, int64_t> p;

	for (vector<int64_t>::iterator it = _vec.begin(); it != _vec.end(); ++it)
	{
		a = *it++;
		if (it == _vec.end())
		{
			_rvec.push_back(a);
			break;
		}
		int64_t b = *it;
		p = (a < b) ? pair<int64_t, int64_t>(a, b) : pair<int64_t, int64_t>(b, a);
		pair_insert(pairs, p);
	}
	return (pairs);
}

void PmergeMe::binary_insert(int64_t num)
{
	for (vector<int64_t>::iterator it = _rvec.begin(); it != _rvec.end(); ++it)
	{
		if (*it > num)
		{
			_rvec.insert(it, num);
			return ;
		}
	}
	_rvec.push_back(num);
}

void PmergeMe::binary_insertion(vector<pair<int64_t, int64_t> > pairs)
{
	int64_t last = _rvec.back();
	_rvec.pop_back();
	for (vector<pair<int64_t, int64_t> >::iterator it = pairs.begin(); it != pairs.end(); ++it)
	{
		_rvec.push_back(it->first);
	}
	for (vector<pair<int64_t, int64_t> >::iterator it = pairs.begin(); it != pairs.end(); ++it)
	{
		// print_pair(*it);
		binary_insert(it->second);
		// print_seq("_rvec: ", _rvec);
	}
	binary_insert(last);
}

vector<int64_t> PmergeMe::sort_vec()
{
	vector<std::pair<int64_t, int64_t> > pairs;
	pairs = make_pairsv(pairs);
	// print_pairs("Pairs: ", pairs);
	// cout << endl;
	binary_insertion(pairs);
	return (_rvec);
}







set<pair<int64_t, int64_t> > PmergeMe::make_pairss()
{
	set<pair<int64_t, int64_t> > pairs;
	int64_t a;

	for (set<int64_t>::iterator it = _set.begin(); it != _set.end(); ++it)
	{
		a = *it++;
		if (it == _set.end())
		{
			_rset.insert(a);
			break;
		}
		int64_t b = *it;
		pairs.insert((a < b) ? pair<int64_t, int64_t>(a, b) : pair<int64_t, int64_t>(b, a));
	}
	return (pairs);
}


set<int64_t> PmergeMe::sort_set()
{
	set<std::pair<int64_t, int64_t> > pairs = make_pairss();
	for (set<pair<int64_t, int64_t> >::iterator it = pairs.begin(); it != pairs.end(); ++it)
	{
		_rset.insert(it->first);
	}
	for (set<pair<int64_t, int64_t> >::iterator it = pairs.begin(); it != pairs.end(); ++it)
	{
		_rset.insert(it->second);
	}
	return (_rset);
}
