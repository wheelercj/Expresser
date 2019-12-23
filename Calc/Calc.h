#ifndef CALC_H
#define CALC_H
#include <string>
#include <stack>
#include <list>

struct Var
{
	std::string name,
		value;
};

class Calc
{
public:
	std::string calc(std::string);
private:
	std::stack<double> nums;
	std::stack<std::string> ops;
	std::string ans = "";
	std::list<Var> constants = { // constants and variables in lists must be ordered by names longest to shortest
		{ "phi", "1.618033989" },
		{ "pi", "3.14159265" },
		{ "e", "2.718281828" },
		{ "g", "9.80665000"} };
	void formatInput(std::string&);
	void formatOutput(std::string&);
	bool isNumber(char);
	bool isVar(std::string&, int);
	bool isOp(char);
	int getNumLength(std::string);
	int getOpLength(std::string);
	bool hasPrecedence(std::string);
	void pop();
};

#endif // !CALC_H