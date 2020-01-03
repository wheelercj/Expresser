#include "Symbol.h"
#include <sstream>

Variable::Variable(std::string newName, double newValue)
{
	name = newName;
	value = newValue;
}

std::string Variable::getName() const
{
	return name;
}

std::string Variable::getValue()
{
	std::stringstream ss;
	ss << value;
	std::string val = ss.str();
	val.insert(0, " ");
	val.append(" ");
	return val;
}

void Variable::setName(std::string newName)
{
	name = newName;
}

void Variable::setValue(std::string newValue)
{
	value = stod(newValue);
}

StrFunction::StrFunction(std::string newName, std::vector<std::string> newParams, std::string newFunction)
{
	name = newName;
	params = newParams;
	function = newFunction;
}

std::string StrFunction::operator()(std::vector<std::string> args)
{
	std::string tempFunc = function;

	// for each parameter
	for (int i = 0; i < params.size(); i++)
	{
		// for each substring of the function with the same size as params[i]
		for (int j = 0; j < tempFunc.size(); j++)
		{
			std::string substr = tempFunc.substr(j, params[i].size());

			// if the substring is the parameter
			if (params[i] == substr)
			{
				// replace the parameter with the corresponding argument
				tempFunc.erase(j, params[i].size());
				tempFunc.insert(j, args[i]);
			}
		}
	}

	return tempFunc;
}

std::string StrFunction::getName() const
{
	return name;
}

std::string StrFunction::getFunc()
{
	return function;
}

std::string StrFunction::getParams()
{
	std::string paramStr = "";
	for (int i = 0; i < params.size(); i++)
		paramStr += params[i] + ",";
	return paramStr;
}

void StrFunction::setName(std::string newName)
{
	name = newName;
}

void StrFunction::setFunc(std::string newFunction)
{
	function = newFunction;
}

void StrFunction::setParams(std::string newParams)
{
	for (int i = 0, j = 0; i < newParams.size(); i++)
	{
		if (newParams[i] == ',')
		{
			params.push_back(newParams.substr(j, i - j));
			j = i + 1;
		}
	}
}

CppFunction::CppFunction(std::string newName, double(*newFuncPtr)(double))
{
	name = newName;
	funcPtr = newFuncPtr;
}

std::string CppFunction::operator()(std::vector<std::string> args)
{
	double result = funcPtr(stod(args[0]));
	std::stringstream ss;
	ss << result;
	return ss.str();
}

std::string CppFunction::getName() const
{
	return name;
}

void CppFunction::setName(std::string newName)
{
	name = newName;
}

void CppFunction::setFunc(double(*newFuncPtr)(double))
{
	funcPtr = newFuncPtr;
}
