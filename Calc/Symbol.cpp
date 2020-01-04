#include "Symbol.h"

StrFunction::StrFunction(std::vector<std::string> newParams, std::string newFunction)
{
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

std::string StrFunction::getFunc()
{
	return function;
}

std::string StrFunction::getParamStr()
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

std::vector<std::string> StrFunction::getParamVect()
{
	return params;
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

CppFunction::CppFunction(double(*newFuncPtr)(double))
{
	funcPtr = newFuncPtr;
}

std::string CppFunction::operator()(std::vector<std::string> args)
{
	double result = funcPtr(stod(args[0]));
	std::stringstream ss;
	ss << result;
	return ss.str();
}

void CppFunction::setFunc(double(*newFuncPtr)(double))
{
	funcPtr = newFuncPtr;
}
