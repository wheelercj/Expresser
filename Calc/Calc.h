#pragma once

#include "DefaultSymbols.hpp"
#include <stack>

class Calc
{
public:
	Calc();
	Calc(Calc*);
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

	std::unordered_map<std::string, double> vars = Symbols::defaultVars;
	std::unordered_map<std::string, Macro> macros = Symbols::defaultMacros;
	std::unordered_map<std::string, long double(*)(long double)> funcs = Symbols::defaultFuncs;
	std::stack<std::string> varsBeingDefined;
	template<class T> void setSymbol(std::unordered_map<std::string, T>& hashTable, std::string newName, T newSymbol);
	bool getSymbolValue(std::string& input, int alphaPos, int alphaSize);
	bool getVarValue(std::string& input, int pos, int size);
	bool callMacro(std::string& input, int pos, int size);
	bool findFunction(std::string& input, int pos, int size);
	std::vector<std::string> readArgs(std::string& input, int pos);
	void evalArgs(std::vector<std::string>& args);
	void insertFunctionResult(std::string& input, int pos, std::string result);
	template <class T, class ...Ts> void handleFunction(std::string& input, int pos, int size, std::string name, T(*funcPtr)(Ts...), std::string(*funcCaller)(T(*)(Ts...), std::string...));
	std::string callLongDoubleFunction(long double(*funcPtr)(long double), std::string num);

	// functions for the user to call
	std::string help();
	std::string help(std::string);
	void setprecision(int);
	std::string random();
};
