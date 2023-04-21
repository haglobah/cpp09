#include "PmergeMe.hpp"

using std::string;
using std::cout;
using std::endl;

int main(int ac, char **av)
{
	try 
	{
		PmergeMe::parse(ac, av);
	}
	catch (const std::exception& e) 
	{
		std::cerr << e.what() << endl;
	}
	PmergeMe::compare();
	return (0);
}