#include "Symbols.h"

std::string Symbols::help() // return info about all symbols
{
	std::string info = "\\"; // TODO: make all strFuncs that start with \\ throw the rest of their message

	std::list<Variable>::iterator it; // TODO: iterate through the hash tables that include user-defined symbols, not the lists here
	for (it = vars.begin(); it != vars.end(); it++)
	{

	}
}

std::string Symbols::random()
{
	srand((unsigned)time(0));
	double x = (rand() % 101) / 100.0;
	std::stringstream ss;
	ss << x;
	return ss.str();
}
