#pragma once

#include <string>
#include <vector>

class Variable
{
private:
	std::string name;
	double value;
public:
	Variable(std::string newName, double newValue);
	std::string getName() const;
	std::string getValue();
	void setName(std::string newName);
	void setValue(std::string newValue);
};

class StrFunction
{
private:
	std::string name;
	std::string function;
	std::vector<std::string> params;
public:
	StrFunction(std::string newName, std::vector<std::string> newParams, std::string newFunction);
	std::string operator()(std::vector<std::string> args);
	std::string getName() const;
	std::string getFunc();
	std::string getParams();
	void setName(std::string newName);
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
	std::string name;
	double(*funcPtr)(double); // TODO: get this to work with all functions. Maybe use a variadic template class
public:
	CppFunction(std::string newName, double(*newFuncPtr)(double));
	std::string operator()(std::vector<std::string> args);
	std::string getName() const;
	void setName(std::string newName);
	void setFunc(double(*newFuncPtr)(double));
};
