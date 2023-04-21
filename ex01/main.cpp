#include "RPN.hpp"

using std::string;
using std::cout;
using std::endl;

int main(int ac, char **av)
{
	if (ac != 2)
	{
		cout << "RPN: Invalid number of args. Call it like that:" << endl;
		cout << "    ./RPN \"<input>\"" << endl;
		return (1);
	}
	string input = av[1];
	if (input.empty())
	{
		cout << "RPN: input_path is empty. Call it like that:" << endl;
		cout << "    ./RPN \"<input>\"" << endl;
		return (1);
	}
	try 
	{
		RPN::calculate(input);
	}
	catch (const std::exception& e) 
	{
		std::cerr << e.what() << endl;
	}
	return (0);
}