#pragma once

#include "AdapterLibrary.hpp"
#include <string>
#include <sstream>

void call_longDouble_longDouble(long double(*funcPtr)(long double), std::string& input, int pos, int size)
{
	std::vector<std::string> args = splitArgs<long double, long double>(input, pos, size);
	evalArgs(args);

	std::stringstream ss;
	ss << funcPtr(stold(args[0]));
	ss.setf(std::ios::fixed);
	ss.precision(05); // TODO: get the precision from Calc

	insertFunctionResult(input, pos, size, ss.str());
}
