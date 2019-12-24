#include "Vars.h"

// find a variable in the input string, and replace it with its value
bool Vars::getVar(std::string& str, int i)
{
	int size = getAlphaSize(str.substr(i, str.size() - i));

	std::list<Var>::iterator it;
	// for each variable
	for (it = vars.begin(); it != vars.end(); it++)
	{
		// for each substring of the alpha string
		for (int j = str.size() - i; j > 0; j--)
		{
			// for each position the substring can fit into the alpha string, from right to left
			for (int k = j - it->name.size(); k >= 0; k--)
			{
				// if the substring matches a variable name
				if (str.substr(i + k, j) == it->name)
				{
					// replace the variable name with its value
					str.erase(i + k, j);
					std::string value = it->value;

					// determine the datatype at the end of the string
					for (int m = value.size() - 1; m >= 0; m--)
					{
						if (isNumber(value[m]))
						{
							lastType = "num";
							break;
						}
						if (isOp(value[m]))
						{
							lastType = "op";
							break;
						}
					}

					value.insert(0, " ");
					value.append(" ");
					str.insert(i + k, value);
					return true;
				}
			}
		}
	}

	return false;
}

bool Vars::isNumber(char ch)
{
	if (ch >= '0' && ch <= '9' || ch == '.')
		return true;
	return false;
}

bool Vars::isOp(char ch)
{
	std::string validOps = "()^*/+-!%<>=";
	if (validOps.find(ch) != std::string::npos)
		return true;
	return false;
}

int Vars::getAlphaSize(std::string str)
{
	for (int i = 0; i < str.size(); i++)
	{
		char ch = tolower(str[i]);
		if (!(ch >= 'a' && ch <= 'z') && ch != '_' && ch != '(')
			return i;
	}
}

void Vars::setVar(std::string name, std::string value)
{
	// search for an existing var with the given name
	std::list<Var>::iterator it;
	for (it = vars.begin(); it != vars.end(); it++)
	{
		if (name == it->name)
		{
			it->value = value;
			return;
		}
	}

	//TODO: create a new var, and insert it into the correct part of the list
	// prevent any variable from having the same name as a function and vice-versa
}