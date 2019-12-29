#ifndef CALC_H
#define CALC_H
#include "Symbols.h"

class Calc : public Symbols
{
public:
	std::string calc(std::string input);
private:
	std::stack<double> nums;
	std::stack<std::string> ops;
	std::string lastTypePushed = ""; // can be "", "op", or "num"
	void validateInput(std::string& input);
	void assignmentFormat(std::string&  input);
	std::string evaluate(std::string str);
	void formatOutput(std::string& str);
	int getNumSize(std::string str);
	int getOpSize(std::string str);
	bool hasPrecedence(std::string op1);
	void pop();
};

#endif // !CALC_H
