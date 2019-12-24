#ifndef CALC_H
#define CALC_H
#include "Vars.h"
#include <stack>

class Calc : public Vars
{
public:
	std::string calc(std::string);
private:
	std::stack<double> nums;
	std::stack<std::string> ops;
	std::string lastType = "";
	void validateInput(std::string&);
	void formatOutput(std::string&);
	int getNumSize(std::string);
	int getOpSize(std::string);
	bool hasPrecedence(std::string);
	void pop();
};

#endif // !CALC_H
