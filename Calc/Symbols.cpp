#include "Symbols.h"

bool Symbols::getVarValue(std::string& str, int i, int alphaSize)
{
	/*
		This function finds the name of one defined symbol within a string of alpha characters,
		and replaces the name with its value. There may be multiple symbols named in the alpha
		string with no spaces or anything else between them. Precedence is given to symbols
		with longer names, and to symbols further to the right of the string.
	*/

	std::list<Symbol>::iterator it;
	int varSize;

	// for each defined symbol
	for (it = symbols.begin(); it != symbols.end(); it++)
	{
		varSize = it->name.size();
		
		// for each position the symbol can fit into the alpha string, from right to left
		for (int k = alphaSize - varSize; k >= 0; k--)
		{
			// if the substring matches the name of a defined symbol
			if (str.substr(i + k, varSize) == it->name)
			{
				// replace the symbol name with its value
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

int Symbols::getAlphaSize(std::string str)
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

void Symbols::setVar(std::string name, std::string value)
{
	// search for an existing var with the given name
	std::list<Symbol>::iterator it;
	for (it = symbols.begin(); it != symbols.end(); it++)
	{
		if (name == it->name)
		{
			it->value = value;
			return;
		}
	}

	// else, create a new var and insert it into the correct part of the list
	for (it = symbols.begin(); it != symbols.end(); it++)
	{
		if (name.size() > it->name.size())
		{
			symbols.insert(it, { name, value });
			return;
		}
	}
}