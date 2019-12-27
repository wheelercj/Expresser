#include "Vars.h"

bool Vars::getVarValue(std::string& str, int i, int alphaSize)
{
	/*
		This function finds the name of one defined variable within a string of alpha characters,
		and replaces the name with its value. There may be multiple variables named in the alpha
		string with no spaces or anything else between them. Precedence is given to variables
		with longer names, and to variables further to the right of the string.
	*/

	std::list<Var>::iterator it;
	int varSize;

	// for each defined variable
	for (it = vars.begin(); it != vars.end(); it++)
	{
		varSize = it->name.size();
		
		// for each position the variable can fit into the alpha string, from right to left
		for (int k = alphaSize - varSize; k >= 0; k--)
		{
			// if the substring matches the name of a defined variable
			if (str.substr(i + k, varSize) == it->name)
			{
				// replace the variable name with its value
				str.erase(i + k, varSize);
				std::string value = it->value;
				value.insert(0, " ");
				value.append(" ");
				str.insert(i + k, value);
				return true;
			}
		}
	}

	return false;
}

bool Vars::isNum(char ch)
{
	if (ch >= '0' && ch <= '9' || ch == '.')
		return true;
	return false;
}

bool Vars::isAlpha(char ch)
{
	ch = tolower(ch);
	if (ch >= 'a' && ch <= 'z' || ch == '_')
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
	int i = 0;
	for (; i < str.size(); i++)
	{
		char ch = tolower(str[i]);
		if ((ch < 'a' || ch > 'z') && ch != '_')
			break;
	}

	return i;
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

	// else, create a new var and insert it into the correct part of the list
	for (it = vars.begin(); it != vars.end(); it++)
	{
		if (name.size() > it->name.size())
		{
			vars.insert(it, { name, value });
			return;
		}
	}
}