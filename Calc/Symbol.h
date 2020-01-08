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

class Function
{
public:
	virtual std::string operator()(std::vector<std::string> args) = 0;
};

template <class T, class ...Ts>
class Func : public Function
{
private:
	T(*funcPtr)(Ts...);
public:
	Func(T(*newFuncPtr)(Ts...));
	std::string operator()(std::vector<std::string> args);
};

template<class T, class ...Ts>
inline Func<T, Ts...>::Func(T(*newFuncPtr)(Ts...))
{
	funcPtr = newFuncPtr;
}

template<class T, class ...Ts>
inline std::string Func<T, Ts...>::operator()(std::vector<std::string> strArgs)
{
	// convert the arguments from strings if needed
	for (int i = 0; i < strArgs.size(); i++)
	{
		if (strArgs[i].empty())
		{

		}
		else if (isNum(strArgs[i][0]))
		{

		}
		else if (isAlpha(strArgs[i][0]))
			continue;
	}
}
