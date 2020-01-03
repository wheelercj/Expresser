#pragma once

#include "DefaultSymbols.hpp"
#include <string>
#include <stack>
#include <unordered_map>

class Calc
{
public:
	Calc();
	Calc(Calc*);
	std::string calc(std::string input);
private:
	int Precision = 9;

	void validateInput(std::string& input);
	void formatOutput(std::string& str);
	void assignmentFormat(std::string&  input);
	std::string evaluate(std::string str);
	bool hasPrecedence(std::string op1);
	void pop();

	std::stack<double> nums;
	std::stack<std::string> ops;
	enum types { NONE, OP, NUM };
	int lastTypePushed = NONE;
	bool isNum(char ch);
	bool isAlpha(char ch);
	bool isOp(char ch);
	int getNumSize(std::string str);
	int getAlphaSize(std::string str);
	int getOpSize(std::string str);

	std::unordered_map<std::string, Variable>* vars;
	std::unordered_map<std::string, StrFunction>* strFuncs;
	std::unordered_map<std::string, CppFunction>* cppFuncs;
	std::stack<std::string> varsBeingDefined;
	void setVar(std::string newName, std::string newValue);
	// TODO: create a setStrFunc function
	bool getSymbolValue(std::string& input, int i, int alphaSize);
	std::vector<std::string> readArgs(std::string& input, int pos, int size);

	void help();
	void help(std::string);
	void setprecision(int);
};
