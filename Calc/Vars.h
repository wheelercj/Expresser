#ifndef VARS_H
#define VARS_H
#include <string>
#include <list>

struct Var
{
	std::string name,
		value;
};

class Vars
{
protected:
	bool getVar(std::string&, int);
	bool isNumber(char);
	bool isOp(char);
private:
	int getAlphaSize(std::string);
public:
	void setVar(std::string, std::string);
	std::list<Var> vars = { // variables must be ordered by names longest to shortest
		{ "ans", "" },
		{ "phi", "1.618033989" },
		{ "pi", "3.14159265" },
		{ "e", "2.718281828" },
		{ "g", "9.80665000"}
	};
};

#endif // !VARS_H
