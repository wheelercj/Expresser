#pragma once

#include <string>
#include <vector>
#include <sstream>

class StrFunction
{
private:
	std::string function;
	std::vector<std::string> params;
public:
	StrFunction(std::vector<std::string> newParams, std::string newFunction);
	std::string operator()(std::vector<std::string> args);
	std::string getFunc();
	std::string getParams();
	void setFunc(std::string newFunction);
	void setParams(std::string newParams);
};

//	template<class ...T>
//	struct Func
//	{
//		T(*ptr)(...);
//	};

class CppFunction
{
private:
	double(*funcPtr)(double); // TODO: get this to work with all functions. Maybe use a variadic template class
public:
	CppFunction(double(*newFuncPtr)(double));
	std::string operator()(std::vector<std::string> args);
	void setFunc(double(*newFuncPtr)(double));
};
