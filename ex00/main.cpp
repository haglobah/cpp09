#include "BitcoinExchange.hpp"

using std::string;
using std::cout;
using std::endl;

int main(int ac, char **av)
{
	if (ac != 2)
	{
		cout << "btc: Invalid number of args. Call it like that:" << endl;
		cout << "    ./btc <input_path>" << endl;
		return (1);
	}
	string input = av[1];
	if (input.empty())
	{
		cout << "btc: input_path is empty. Call it like that:" << endl;
		cout << "    ./btc <input_path>" << endl;
		return (1);
	}
	try 
	{
		BitcoinExchange::print_values(input);
	}
	catch (const std::exception& e) 
	{
		std::cerr << e.what() << endl;
	}
	return (0);
}