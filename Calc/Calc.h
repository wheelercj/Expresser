#pragma once

#include "DefaultSymbols.h"
#include <stack>

class Calc
{
public:
	Calc();
	~Calc();
	Calc(int newPrecision);
	Calc(Calc*);
	std::string operator()(std::string input);
	std::string calc(std::string input);
	void resetSymbols();
private:
	int finalPrecision = 5;
	int precision = finalPrecision + 5;

	void assignmentFormat(std::string& input);
	void readSymbolDefinition(std::string& input, int eqPos, int nameSize);
	std::string evaluate(std::string str);

	std::stack<double> nums;
	std::stack<std::string> ops;
	void readNum(std::string& input, int& pos);
	void readAlpha(std::string& input, int& pos);
	void readOp(std::string& input, int& pos);
	enum types { NONE, OP, NUM };
	int lastTypePushed = NONE;
	void pushFirstOperator(int& pos, std::string newOp, int opSize);
	void pushOperator(std::string input, int& pos, std::string newOp, int opSize);
	void pushOpenParenthesis(std::string input, int& pos);
	void pushMinus(int& pos);
	void pop();
	bool handleUnaryOp();
	void handleBinaryOp(std::string op);

	std::map<std::string, double> vars = defaultVars;
	std::map<std::string, Macro> macros = defaultMacros;
	std::map<std::string, std::any> funcs = defaultFuncs;

	std::stack<std::string> varsBeingDefined;
	template<class T> void setSymbol(std::map<std::string, T>& hashTable, std::string newName, T newSymbol);
	bool getSymbolValue(std::string& input, int alphaPos, int alphaSize);
	bool getVarValue(std::string& input, int pos, int size);
	bool callMacro(std::string& input, int pos, int size);
	bool callFunction(std::string& input, int pos, int size);
	
	std::string help_varsAndMacros();
	std::string helpAll();
	std::string help(std::string);
	void setprecision(int);

	// function adapters // TODO: move these to a different file after creating a Functions class?
	void call(long double(*funcPtr)(long double), std::string& input, int pos, int size);
	void call(std::string(*funcPtr)(), std::string& input, int pos, int size);
	void call(void(*funcPtr)(int, int, int), std::string& input, int pos, int size);

	// adapter library // TODO: move these to a different file after creating a Functions class?
	void cleanForNoArgs(std::string& input, std::string name, int argPos);
	std::vector<std::string> splitArgString(std::string& input, int argPos);
	template <class T, class ...Ts> std::vector<std::string> splitArgs(std::string& input, int pos, int size);
	void evalArgs(std::vector<std::string>& args);
	void insertFunctionResult(std::string& input, int pos, int size, std::string result);
};
