#ifndef CALC_H
#define CALC_H
#include "Symbols.h"

class Calc : public Symbols
{
public:
	std::string calc(std::string);
private:
	int Precision = 9;
	std::stack<double> nums;
	std::stack<std::string> ops;
	std::string lastTypePushed = ""; // can be "", "op", or "num"
	void validateInput(std::string&);
	void assignmentFormat(std::string&);
	std::string evaluate(std::string);
	void formatOutput(std::string&);
	int getNumSize(std::string);
	int getOpSize(std::string);
	bool hasPrecedence(std::string);
	void pop();
};

#endif // !CALC_H
