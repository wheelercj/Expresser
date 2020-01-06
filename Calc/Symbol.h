#pragma once

#include <string>
#include <vector>
#include <sstream>

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

//	template<class ...T>
//	struct Func
//	{
//		T(*ptr)(...);
//	};

class Function
{
private:
	double(*funcPtr)(double); // TODO: get this to work with all functions. Maybe use a variadic template class
public:
	Function(double(*newFuncPtr)(double));
	std::string operator()(std::vector<std::string> args);
};
