#ifndef SYMBOLS_H
#define SYMBOLS_H
#include <stack>
#include <string>
#include <sstream>
#include <vector>
#include <list>

struct Symbol // a variable or a function
{
	std::string name,
		value,
		params;
	/*
		if params.empty()
			the symbol is a variable and value should be a number
		else
			the symbol is a function
			the function's parameters are listed in params, separated by commas
			if value == "\\"
				the function is expressed in C++
			else
				the function is expressed as a string stored in value
	*/
};

class Symbols
{
private:
	void insertValue(std::string& input, std::string value, int start);
protected:
	int getAlphaSize(std::string str);
	bool getSymbolValue(std::string& input, int i, int alphaSize);
	bool isNum(char ch);
	bool isAlpha(char ch);
	bool isOp(char ch);
	std::stack<std::string> varsBeingDefined;
	void setSymbol(std::string name, std::string value);
	std::string callFunction(std::string name, std::vector<std::string> args);
	int Precision = 9;
	std::string help(std::string name);
	std::string help();
	std::list<Symbol> symbols = { // variables and functions
		{ "ans", "" },			// TODO: create a function that sorts the symbols by name length
		{ "phi", "1.618033988749894848204586834365638117720309179805762862135" },
		{ "pi", "3.141592653589793238462643383279502884197169399375105820974" },
		{ "e", "2.718281828459045235360287471352662497757247093699959574966" },
		{ "g", "9.80665" }
	}; // TODO: convert this list to a hash table?
};

#endif // !SYMBOLS_H
