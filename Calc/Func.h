#pragma once

#include <string>

template <class T, class ...Ts>
class Func
{
private:
	std::string params;
	T(*funcPtr)(Ts...);
public:
	Func(std::string newParams, T(*newFuncPtr)(Ts...));
	std::string getParams();
	void operator()(std::string& input, int namePos, int nameSize);
};
