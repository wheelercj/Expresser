#ifndef VARS_H
#define VARS_H
#include <string>
#include <list>
#include <stack>

struct Var
{
	std::string name,
		value;
};

class Vars
{
protected:
	int getAlphaSize(std::string);
	bool getVarValue(std::string&, int, int);
	bool isNum(char);
	bool isAlpha(char);
	bool isOp(char);
private:
public:
	std::stack<std::string> varsBeingDefined;
	void setVar(std::string, std::string);
	std::list<Var> vars = { // variables must be ordered by names longest to shortest
		{ "ans", "" },		// TODO: create a function that sorts the variables by name length
		{ "phi", "1.618033988749894848204586834365638117720309179805762862135" },
		{ "pi", "3.141592653589793238462643383279502884197169399375105820974" },
		{ "e", "2.718281828459045235360287471352662497757247093699959574966" },
		{ "g", "9.80665"}
	};
};

#endif // !VARS_H
