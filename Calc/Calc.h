#pragma once

#include "DefaultSymbols.hpp"
#include <stack>

class Calc
{
public:
	Calc();
	Calc(int);
	Calc(Calc*);
	~Calc();
	std::string calc(std::string input);
	void resetSymbols();
private:
	int Precision = 5;

	void validateInput(std::string& input);
	void formatOutput(std::string& str, int precision);
	void assignmentFormat(std::string& input);
	int findMacroNameSize(std::string& input, int eqPos);
	void readSymbolDefinition(std::string& input, int eqPos, int nameSize);
	std::vector<std::string> readParams(std::string str);
	void removeEdgeSpaces(std::string& str);
	std::string evaluate(std::string str);

	std::stack<double> nums;
	std::stack<std::string> ops;
	void pop();
	enum types { NONE, OP, NUM };
	int lastTypePushed = NONE;
	bool isNum(char ch);
	bool isAlpha(char ch);
	bool isOp(char ch);
	int getNumSize(std::string str);
	int getAlphaSize(std::string str);
	int getOpSize(std::string str);
	void readOp(std::string input, int& pos);
	bool hasPrecedence(std::string op1);

	std::unordered_map<std::string, double> vars;
	std::unordered_map<std::string, Macro> macros;
	std::unordered_map<std::string, Function> funcs;
	std::stack<std::string> varsBeingDefined;
	template<class T> void setSymbol(std::unordered_map<std::string, T>& hashTable, std::string newName, T newSymbol);
	bool getSymbolValue(std::string& input, int alphaPos, int alphaSize);
	std::vector<std::string> readArgs(std::string& input, int pos);
	std::string get_Vars_and_Macros();

	// functions for the user to call
	std::string help();
	std::string help(std::string);
	void setprecision(int);
	std::string random();
};
