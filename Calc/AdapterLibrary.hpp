#pragma once

#include "Calc.h"
#include "Debug.hpp"

/*
	template <class T, class ...Ts> std::vector<std::string> splitArgs(std::string& input, int pos, int size);
	void evalArgs(std::vector<std::string>& args);
	void insertFunctionResult(std::string& input, int pos, int size, std::string result);
	//int getPrecision();
*/

std::vector<std::string> splitStrArgs(std::string& input, int argPos)
{
	int parentheses = 0;

	if (input[argPos] != '(')
		throw LOG("Error: expected '(' after function name");

	// split the arguments
	std::vector<std::string> args;
	for (int j = argPos + 1, k = j, m = j - 1; ; j++)
	{
		if (j > input.size())
			throw LOG("Invalid syntax");
		if (j == input.size())
		{
			args.push_back(input.substr(k, j - k));
			input.erase(argPos, j - m + 1);
			break;
		}
		if (input[j] == '(')
			parentheses++;
		if (input[j] == ')')
		{
			if (parentheses)
				parentheses--;
			else
			{
				args.push_back(input.substr(k, j - k));
				input.erase(argPos, j - m + 1);
				break;
			}
		}
		if (input[j] == ',')
		{
			args.push_back(input.substr(k, j - k));
			j++;
			k = j;
		}
	}

	return args;
}

template <class T, class ...Ts>
std::vector<std::string> splitArgs(std::string& input, int pos, int size)
{
	std::vector<std::string> args = splitStrArgs(input, pos + size);

	int sizeTs = sizeof...(Ts);
	if (args.size() != sizeTs)
	{
		std::string message = "Error: expected ";
		message += std::to_string(sizeTs);
		message += " argument";
		if (sizeTs != 1)
			message += "s";
		message += " for function ";
		message += input.substr(pos, size);
		throw LOG(message);
	}

	return args;
}

void evalArgs(std::vector<std::string>& args)
{
	// evaluate each argument
	Calc c2(10); // TODO: get access to the original calc's user symbols somehow. Make this a friend function?
	for (int i = 0; i < args.size(); i++)
	{
		args[i] = c2._calc(args[i]);

		// rethrow messages
		if (args[i] == "")
			throw LOG("Invalid syntax");
		for (int j = 0; j < args[i].size(); j++)
		{
			if (c2.isAlpha(args[i][j]))
				throw LOG(args[i]);
		}
	}
}

void insertFunctionResult(std::string& input, int pos, int size, std::string result)
{
	// If the result of a sin call is in scientific notation with
	// a negative exponent, it's probably supposed to equal zero
	for (int i = 0; i < result.size(); i++)
	{
		if (result[i] == 'e' && input.substr(pos, size) == "sin")
		{
			if (i < result.size() - 1 && result[i + 1] == '-')
				result = "0";
			else
				throw LOG("Not equipped for scientific notation");
		}
	}

	if (result == "-nan(ind)")
		throw "Imaginary";
	input.erase(pos, size);
	input.insert(pos, "(" + result + ")");
}

//class Calc;
//int getPrecision()
//{
//	return Calc::Precision; // error: must be relative to a specific object
//}
