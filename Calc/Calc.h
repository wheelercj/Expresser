#pragma once

#include "Symbols.h"
#include <string>
#include <stack>

class Calc
{
public:
	std::string calc(std::string input);
private:
	std::stack<double> nums;
	std::stack<std::string> ops;
	enum types { NONE, OP, NUM };
	int lastTypePushed = NONE;
	std::stack<std::string> varsBeingDefined;
	int Precision = 9;

	void validateInput(std::string& input);
	void assignmentFormat(std::string&  input);
	std::string evaluate(std::string str);
	bool isNum(char ch);
	bool isAlpha(char ch);
	bool isOp(char ch);
	void insertVarValue(std::string& input, std::string value, int start);
	void formatOutput(std::string& str);
	int getNumSize(std::string str);
	int getOpSize(std::string str);
	int getAlphaSize(std::string str);
	bool getSymbolValue(std::string& input, int i, int alphaSize);
	bool hasPrecedence(std::string op1);
	void pop();
};
