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
public:
	std::list<Var> vars = { // variables must be ordered by names longest to shortest
		{ "ans", "" },
		{ "phi", "1.618033989" },
		{ "pi", "3.14159265" },
		{ "e", "2.718281828" },
		{ "g", "9.80665000"}
	};
	void setVar(std::string, std::string);
protected:
	bool getVar(std::string&, int);
	bool isNumber(char);
	bool isOp(char);
	std::string lastType = "";
private:
	int getAlphaSize(std::string);
};

#endif // !VARS_H
