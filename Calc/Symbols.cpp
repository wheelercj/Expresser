#include "Symbols.h"
#include "Calc.h"

// replace a symbol name with its value
void Symbols::insertValue(std::string& input, std::string value, int start)
{
	input.erase(start, value.size());
	value.insert(0, " ");
	value.append(" ");
	input.insert(start, value);
}

int Symbols::getAlphaSize(std::string substr)
{
	int i = 1;
	for (; i < substr.size(); i++)
	{
		char ch = tolower(substr[i]);
		if ((ch < 'a' || ch > 'z') && ch != '_')
			break;
	}

	return i;
}

bool Symbols::getSymbolValue(std::string& input, int i, int alphaSize)
{
	/*
		This function finds the name of one defined symbol within a string of alpha characters,
		and replaces the name with its value. There may be multiple symbols named in the alpha
		string with no spaces or anything else between them. Precedence is given to symbols
		with longer names, and to symbols further to the right of the string.
	*/

	std::list<Symbol>::iterator it;

	// for each defined symbol
	for (it = symbols.begin(); it != symbols.end(); it++)
	{
		int nameSize = it->name.size();
		
		// for each position the symbol's name can fit into the alpha string, from right to left
		for (int j = alphaSize - nameSize; j >= 0; j--)
		{
			// if the substring matches the symbol's name
			if (input.substr(i + j, nameSize) == it->name)
			{
				int nameLoc = i + j;

				if (it->params.empty()) // the symbol is a variable
				{
					insertValue(input, it->value, nameLoc);
					return true;
				}
				else // the symbol is a function
				{
					// find the function's arguments
					int start = i + alphaSize;
					if (input[start] != '(')
						throw "Invalid syntax";
					start++;
					int count = 0;
					while (start + count < input.size() - 1 && input[start + count] != ')')
						count++;
					std::string argStr = input.substr(start, count);
					input.erase(start - 1, count + 2);

					/*
					// TODO: To allow arguments to be expressions containing operators, variables, etc.,
						create a new calculator object to evaluate each argument. The new calculator
						should be created in a way that does not make a copy of any symbols or 
						settings from the original calculator, but instead has read-only access to
						those of the original.

						If I create the new calculator without dynamically allocating it, what will
						happen if the new calculator also creates a new calculator?
					*/

					// separate the arguments
					std::vector<std::string> args;
					Calc c2;
					for (int i = 0; i < argStr.size(); i++)
					{
						if (argStr[i] == ',')
						{
							std::string arg = c2.calc(argStr.substr(0, i));
							args.push_back(arg);
							argStr.erase(0, i + 1);
							i = 0;
						}
					}

					// call the function
					if (it->value == "\\") // then the function is expressed in C++
					{
						std::string value = callFunction(it->name, args);
						insertValue(input, value, nameLoc);
						return true;
					}
					else // the function is expressed as a string stored in value
					{
						// TODO: plug in the found args
						return true;
					}
				}
			}
		}
	}

	// the symbol is undefined
	return false;
}

bool Symbols::isNum(char ch)
{
	if (ch >= '0' && ch <= '9' || ch == '.')
		return true;
	return false;
}

bool Symbols::isAlpha(char ch)
{
	ch = tolower(ch);
	if (ch >= 'a' && ch <= 'z' || ch == '_')
		return true;
	return false;
}

bool Symbols::isOp(char ch)
{
	std::string validOps = "()^*/+-!%<>=";
	if (validOps.find(ch) != std::string::npos)
		return true;
	return false;
}

void Symbols::setSymbol(std::string name, std::string value)
{
	// search for an existing symbol with the given name
	std::list<Symbol>::iterator it;
	for (it = symbols.begin(); it != symbols.end(); it++)
	{
		if (name == it->name)
		{
			it->value = value;
			return;
		}
	}

	// else, create a new symbol and insert it into the correct part of the list
	for (it = symbols.begin(); it != symbols.end(); it++)
	{
		if (name.size() > it->name.size())
		{
			symbols.insert(it, { name, value });
			return;
		}
	}
}

std::string Symbols::callFunction(std::string name, std::vector<std::string> args)
{
	std::stringstream ss;

	switch (args.size())
	{
	case 0:
		if (name == "help")
			ss << help();

		else
			throw "Invalid syntax";

	case 1:
		if (name == "help")
			ss << help(args[0]); // TODO: learn how to create and use function pointers?

		else if (name == "sqrt")
			ss << sqrt(stold(args[0]));

		else if (name == "ceil")
			ss << ceil(stold(args[0]));
		else if (name == "floor")
			ss << floor(stold(args[0]));

		// trigonometric functions
		else if (name == "sin")
			ss << sin(stold(args[0]));
		else if (name == "cos")
			ss << cos(stold(args[0]));
		else if (name == "tan")
			ss << tan(stold(args[0]));
		else if (name == "csc")
			ss << "1/sin(" << args[0] << ")";
		else if (name == "sec")
			ss << "1/cos(" << args[0] << ")";
		else if (name == "cot")
			ss << "1/tan(" << args[0] << ")";

		// inverse trigonometric functions
		else if (name == "asin")
			ss << asin(stold(args[0]));
		else if (name == "acos")
			ss << acos(stold(args[0]));
		else if (name == "atan")
			ss << atan(stold(args[0]));
		else if (name == "acsc")
			ss << "1/asin(" << args[0] << ")";
		else if (name == "asec")
			ss << "1/asec(" << args[0] << ")";
		else if (name == "acot")
			ss << "1/acot(" << args[0] << ")";

		// hyperbolic functions
		else if (name == "sinh")
			ss << sinh(stold(args[0]));
		else if (name == "cosh")
			ss << cosh(stold(args[0]));

		// inverse hyperbolic functions
		else if (name == "asinh")
			ss << asinh(stold(args[0]));
		else if (name == "acosh")
			ss << acosh(stold(args[0]));

		else
			throw "Invalid syntax";

	case 2:
		if (name == "pow")
			ss << pow(stold(args[0]), stold(args[1]));

		else if (name == "sin^")
			ss << pow(sin(stold(args[1])), stold(args[0]));

		else if (name == "sinh^")
			ss << pow(sinh(stold(args[1])), stold(args[0]));

		else
			throw "Invalid syntax";
	}

	return ss.str();
}

// return the name, parameters, and value of one symbol
std::string Symbols::help(std::string name)
{
	std::list<Symbol>::iterator it;
	std::string output = "";

	for (it = symbols.begin(); it != symbols.end(); it++)
	{
		if (name == "" || it->name == name)
		{
			output.append(it->name);
			if (!it->params.empty())
			{
				output.append("(");
				output.append(it->params);
				output.append(")");
			}
			if (it->value != "\\")
			{
				output.append(" = ");
				output.append(it->value);
			}

			if (name != "")
				return output;
			else
				output.append("\n ");
		}
	}

	return output;
}

// return the names, parameters, and values of all symbols
std::string Symbols::help()
{
	return help("");
}
