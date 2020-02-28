#pragma once

#include "Common.h"
#include <vector>

/*
	A Macro object is not an entire macro. The macro's name is stored
	as the key in a	hash table, so the function that calls macros
	must also not be part of the Macro class.
*/

class Macro
{
private:
	std::vector<std::string> params;
	std::string formula;
public:
	Macro(std::vector<std::string> newParams, std::string newFormula);
	std::string getFormula();
	std::string getParamStr();
	std::vector<std::string> getParamVect();
};

int findMacroNameSize(std::string& input, int eqPos);
