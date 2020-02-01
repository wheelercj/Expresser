#pragma once

#include "Common.h"
#include <vector>

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
