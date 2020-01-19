#pragma once

#include <string>
#include <vector>

class Macro
{
private:
	std::vector<std::string> params;
	std::string formula;
public:
	Macro(std::vector<std::string> newParams, std::string newFormula);
	std::string operator()(std::vector<std::string> args);
	std::string getFormula();
	std::string getParamStr();
	std::vector<std::string> getParamVect();
};
