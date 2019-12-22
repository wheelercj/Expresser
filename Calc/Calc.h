#ifndef CALC_H
#define CALC_H
#include <string>
#include <stack>
#include <vector>

class Calc
{
public:
	std::string calc(std::string);
private:
	std::stack<double> nums;
	std::stack<std::string> ops;
	void formatInput(std::string&);
	void formatOutput(std::string&);
	bool isNumber(char);
	bool isOp(char);
	int getNumLength(std::string);
	bool hasPrecedence(std::string, std::string);
	void pop();
};

#endif // !CALC_H