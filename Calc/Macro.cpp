#include "Macro.h"

Macro::Macro(std::vector<std::string> newParams, std::string newFormula)
{
	params = newParams;
	formula = newFormula;
}

std::string Macro::getFormula()
{
	return formula;
}

std::string Macro::getParamStr()
{
	std::string paramStr = "";
	for (int i = 0; i < params.size(); i++)
	{
		paramStr += params[i];
		if (i < params.size() - 1)
			paramStr += ",";
	}
	return paramStr;
}

std::vector<std::string> Macro::getParamVect()
{
	return params;
}

// returns zero if the symbol is a variable
int findMacroNameSize(std::string& input, int eqPos)
{
	bool alphaFound = false;
	bool spaceAfterAlpha = false;

	for (int i = 0; i < eqPos; i++)
	{
		if (isAlpha(input[i]))
		{
			alphaFound = true;
			if (spaceAfterAlpha)
				throw LOG("Invalid space before assignment operator");
		}
		else if (input[i] == ' ')
		{
			if (alphaFound)
				spaceAfterAlpha = true;
		}
		else if (input[i] == '(')
		{
			if (spaceAfterAlpha)
				throw LOG("Invalid space before parameter(s)");
			if (!alphaFound)
				throw LOG("Missing symbol name before assignment operator");

			return i;
			break;
		}
		else
		{
			std::string message = "Invalid character before assignment operator: ";
			message += input[i];
			throw LOG(message);
		}
	}

	if (!alphaFound)
		throw LOG("Missing symbol name before assignment operator");

	return 0;
}
