#include "Calc.h"
#include <iostream>

Calc::Calc()
{
	funcs = defaultFuncs;

	// load any saved symbols from a file
	std::ifstream file("saved_symbols.txt");
	if (!file)
	{
		LOG("No file with saved symbols found.");
		vars = defaultVars;
		macros = defaultMacros;
	}
	else
	{
		for (std::string line; std::getline(file, line);)
			calc(line);

		file.close();
		LOG("Loaded saved symbols from a file.");
	}
}

Calc::~Calc()
{
	// save all symbols to a file
	std::ofstream file("saved_symbols.txt", std::ios::trunc);
	precision += 5;
	file << help_varsAndMacros();
	file.close();
}

// for loading only the default symbols
Calc::Calc(int newPrecision)
{
	finalPrecision = newPrecision;
	precision = finalPrecision + 5;

	vars = defaultVars;
	macros = defaultMacros;
	funcs = defaultFuncs;
}

Calc::Calc(Calc* other)
{
	finalPrecision = other->finalPrecision + 5;
	precision = other->precision + 5;
	vars = other->vars;
	macros = other->macros;
	funcs = other->funcs;
}

std::string Calc::operator()(std::string input)
{
	std::string result = calc(input);
	formatOutput(result, finalPrecision);
	return result;
}

std::string Calc::calc(std::string input)
{
	std::string result;
	bool assigning = false;

	while (!nums.empty())
		nums.pop();
	while (!ops.empty())
		ops.pop();

	try
	{
		validateInput(input);
		assignmentFormat(input);
		result = evaluate(input);

		while (!varsBeingDefined.empty())
		{
			assigning = true;
			setSymbol<double>(vars, varsBeingDefined.top(), stold(result));
			varsBeingDefined.pop();
		}

		if (assigning)
			return "";
		setSymbol<double>(vars, "ans", stold(result));
	}
	catch (const char* error)
	{
		result = error;
	}
	catch (std::string error)
	{
		result = error;
	}
	catch (std::bad_alloc)
	{
		result = "Insufficient memory";
	}

	return result;
}

void Calc::resetSymbols()
{
	vars = defaultVars;
	macros = defaultMacros;
	funcs = defaultFuncs;
}

void Calc::setPrecision(int num)
{
	finalPrecision = num;
	precision = finalPrecision + 5;
}

int Calc::getPrecision()
{
	return precision;
}

// search for and handle any assignment operator(s)
void Calc::assignmentFormat(std::string& input)
{
	while (true) // multiple simultaneous variable assignments allowed, e.g. "a=b=c=5"
	{
		bool assigning = false;
		int eqPos = 0;
		for (; eqPos < input.size(); eqPos++)
		{
			if (input[eqPos] == '=')
			{
				// either input[eqPos] is an assignment operator or there isn't a valid one
				if (eqPos == 0)
					return;
				if (eqPos == input.size() - 1 || input[eqPos + 1] == '=')
					return;
				if (eqPos >= 1)
				{
					char ch = input[eqPos - 1];
					if (ch == '>' || ch == '<' || ch == '!')
						return;
				}

				assigning = true;
				break;
			}
		}

		if (!assigning)
			return;

		int macroNameSize = findMacroNameSize(input, eqPos);
		readSymbolDefinition(input, eqPos, macroNameSize);
	}
}

void Calc::readSymbolDefinition(std::string& input, int eqPos, int macroNameSize)
{
	if (!macroNameSize) // then a variable is being defined
	{
		std::string varName = input.substr(0, eqPos);
		input.erase(0, eqPos + 1);
		removeEdgeSpaces(varName);
		varsBeingDefined.push(varName);
	}
	else // then a macro is being defined
	{
		if (varsBeingDefined.size())
			throw LOG("Multiple simultaneous definitions are only possible with variables");

		std::string macroName = input.substr(0, macroNameSize);
		removeEdgeSpaces(macroName);

		std::string paramStr = input.substr(macroNameSize, eqPos - macroNameSize + 1);
		std::vector<std::string> params = readParams(paramStr);
		for (int i = 0; i < params.size(); i++)
			removeEdgeSpaces(params[i]);

		std::string formula = input.substr(eqPos + 1, input.size() - eqPos);
		removeEdgeSpaces(formula);

		setSymbol<Macro>(macros, macroName, { params, formula });
		throw "";
	}
}

// read the input string and determine what to do with each part of it
std::string Calc::evaluate(std::string input)
{
	std::string result,
		temp = "";
	lastTypePushed = NONE;

	for (int i = 0; i < input.size();)
	{
		if (isNum(input[i]))
			readNum(input, i);
		else if (input[i] == ' ')
			i++;
		else if (isAlpha(input[i]))
			readAlpha(input, i);
		else if (isOp(input[i]))
			readOp(input, i);
		else
		{
			std::string message = "Undefined character: ";
			message += input[i];
			throw LOG(message);
		}
	}

	bool emptyString = true;
	for (int i = 0; i < input.size(); i++)
	{
		if (input[i] != ' ')
			emptyString = false;
	}
	if (emptyString)
		throw "";

	while (!ops.empty())
		pop();
	while (nums.size() > 1) // remaining numbers are multiplied together
		pop();

	std::stringstream ss;
	ss.setf(std::ios::fixed);
	ss.precision(precision);
	ss << nums.top();
	result = ss.str();
	return result;
}

void Calc::readNum(std::string& input, int& pos)
{
	if (lastTypePushed == NUM)
		input.insert(pos, "*");
	else
	{
		int numSize = getNumSize(input.substr(pos, input.size() - pos));
		nums.push(stold(input.substr(pos, numSize)));
		pos += numSize;
		lastTypePushed = NUM;
	}
}

void Calc::readAlpha(std::string& input, int& pos)
{
	int alphaSize = getAlphaSize(input.substr(pos, input.size() - pos));
	if (!getSymbolValue(input, pos, alphaSize))
	{
		std::string message = "Undefined character";
		if (alphaSize != 1)
			message += "s";
		message += ": " + input.substr(pos, alphaSize);
		throw LOG(message);
	}
}

void Calc::readOp(std::string& input, int& pos)
{
	int opSize = getOpSize(input.substr(pos, input.size() - pos));
	std::string newOp = input.substr(pos, opSize);

	if (ops.empty() && newOp != ")" && newOp != "(")
		pushFirstOperator(pos, newOp, opSize);
	else
		pushOperator(input, pos, newOp, opSize);
}

void Calc::pushFirstOperator(int& pos, std::string newOp, int opSize)
{
	if (newOp == "-")
	{
		if (lastTypePushed == NONE)
			ops.push("negate");
		else
			ops.push("subtract");
		lastTypePushed = OP;
	}
	else if (nums.empty() && newOp == "!")
		throw LOG("Error: expected an operand before the factorial operator");
	else
	{
		ops.push(newOp);
		lastTypePushed = OP;
	}

	pos += opSize;
}

void Calc::pushOperator(std::string input, int& pos, std::string newOp, int opSize)
{
	if (newOp == "(")
		pushOpenParenthesis(input, pos);
	else if (newOp == ")")
	{
		while (!ops.empty() && ops.top() != "(")
			pop();
		if (ops.empty())
			throw LOG("Error: missing an opening parenthesis");
		pop();
		pos++;
	}
	else if (newOp == "!" || newOp == "*" || newOp == "/" || newOp == "+"
		|| newOp == "%" || newOp == "==" || newOp == ">=" || newOp == "<="
		|| newOp == "!=" || newOp == ">" || newOp == "<")
	{
		if (hasPrecedence(newOp, ops.top()))
		{
			ops.push(newOp);
			pos += opSize;
			lastTypePushed = OP;
		}
		else
			pop();
	}
	else if (newOp == "^")
	{
		if (ops.top() == "^" || hasPrecedence(newOp, ops.top()))
		{
			ops.push(newOp);
			pos += opSize;
			lastTypePushed = OP;
		}
		else
			pop();
	}
	else if (newOp == "-")
		pushMinus(pos);
	else
		throw LOG("Undefined operator: " + newOp);
}

void Calc::pushOpenParenthesis(std::string input, int& pos)
{
	if (pos > 0 && lastTypePushed == NUM)
	{
		if (!ops.empty() && (ops.top() == "^" || ops.top() == "*" || ops.top() == "/"))
			pop();
		else
		{
			ops.push("*");
			ops.push(input.substr(pos, 1));
			pos++;
			lastTypePushed = OP;
		}
	}
	else
	{
		ops.push("(");
		pos++;
		lastTypePushed = OP;
	}
}

void Calc::pushMinus(int& pos)
{
	std::string newOp;

	if (lastTypePushed == NONE || lastTypePushed == OP)
		newOp = "negate";
	else
		newOp = "subtract";

	if (newOp == "negate" || hasPrecedence(newOp, ops.top()))
	{
		ops.push(newOp);
		pos++;
		lastTypePushed = OP;
	}
	else
		pop();
}

// pop and evaluate numbers and operators
void Calc::pop()
{
	if (nums.empty())
		throw LOG("Error: not enough operands for the given operators");

	std::string op;
	if (ops.empty())
		op = "*";
	else
	{
		if (handleUnaryOp())
			return;
		op = ops.top();
		ops.pop();
	}

	handleBinaryOp(op);
}

bool Calc::handleUnaryOp()
{
	if (ops.top() == "(")
	{
		ops.pop();
		return true;
	}
	else if (ops.top() == "negate")
	{
		double temp = nums.top();
		nums.pop();
		temp *= -1;
		nums.push(temp);
		ops.pop();
		return true;
	}
	else if (ops.top() == "!")
	{
		double n = nums.top(),
			total = 1,
			temp = n;
		nums.pop();

		if (n < 0)
			throw "Complex infinity";
		while (temp > 1)
			temp -= 1;
		if (temp < 1 && temp > 0)
			throw "Undefined";
		else if (n == 0)
			total = 1; // 0!=1 by convention
		else
		{
			for (int i = n; i > 1; i--)
				total *= i;
		}

		nums.push(total);
		ops.pop();
		return true;
	}
}

void Calc::handleBinaryOp(std::string op)
{
	if (nums.size() == 1)
		throw LOG("Error: not enough operands for the given operators");

	double num2 = nums.top();
	nums.pop();
	double num1 = nums.top();
	nums.pop();

	if (op == "^")
	{
		if (num1 == 0 && num2 == 0)
			throw "Indeterminate: 0^0";
		else if (num1 < 0 && num2 < 1 && (int)pow(num2, -1) % 2 == 0)
			throw "Imaginary: even root of a negative";
		nums.push(pow(num1, num2));
	}
	else if (op == "*")
		nums.push(num1 * num2);
	else if (op == "/")
	{
		if (num2 == 0)
		{
			if (num1 == 0)
				throw "Indeterminate: 0/0";
			throw "Infinity: n/0";
		}
		nums.push(num1 / num2);
	}
	else if (op == "+")
		nums.push(num1 + num2);
	else if (op == "subtract")
		nums.push(num1 - num2);
	else if (op == "%")
	{
		if (num2 == 0)
			throw "Undefined: n%0";
		nums.push(fmod(num1, num2));
	}
	else if (op == "==")
		nums.push(num1 == num2);
	else if (op == "!=")
		nums.push(num1 != num2);
	else if (op == ">=")
		nums.push(num1 >= num2);
	else if (op == "<=")
		nums.push(num1 <= num2);
	else if (op == ">")
		nums.push(num1 > num2);
	else if (op == "<")
		nums.push(num1 < num2);
	else
		throw LOG("Undefined operator: " + op);
}

template<class T>
void Calc::setSymbol(std::map<std::string, T>& hashTable, std::string newName, T newSymbol)
{
	// erase any existing symbol with the given name
	vars.erase(newName);
	macros.erase(newName);
	funcs.erase(newName);
	
	hashTable.emplace(newName, newSymbol);
}

bool Calc::getSymbolValue(std::string& input, int alphaPos, int alphaSize)
{
	/*
		This function finds the name of one defined symbol within a string of alpha characters
		in the input string, and replaces the name with its value. There may be multiple symbols
		named in the alpha string with no spaces or anything else between them. Precedence is
		given to symbols with longer names, and to symbols further to the left of the string.
		All functions and macros must be immediately followed by an opening parenthesis.
	*/

	// for each substring size of the alpha string
	for (int size = alphaSize; size > 0; size--)
	{
		// for each substring position of the alpha string
		for (int pos = alphaPos; pos + size <= alphaPos + alphaSize; pos++)
		{
			if (findVariable(input, pos, size)
				|| findMacro(input, pos, size)
				|| findFunction(input, pos, size))
				return true;
		}
	}

	// the character(s) are undefined
	return false;
}

bool Calc::findVariable(std::string& input, int pos, int size)
{
	std::string substr = input.substr(pos, size);

	std::map<std::string, double>::iterator it = vars.find(substr);
	if (it != vars.end())
	{
		// replace the variable name with its value
		input.erase(pos, size);
		std::stringstream ss;
		ss.setf(std::ios::fixed);
		ss.precision(precision);
		ss << " " << it->second << " ";
		input.insert(pos, ss.str());
		return true;
	}

	return false;
}

bool Calc::findMacro(std::string& input, int pos, int size)
{
	std::string name = input.substr(pos, size);

	std::map<std::string, Macro>::iterator it = macros.find(name);
	if (it == macros.end())
		return false;
	else
	{
		std::vector<std::string> args = splitArgString(input, pos + size);
		input.erase(pos, size);

		if (it->first == "help")
		{
			if (args.size() && args[0] != "")
				throw help(args[0]);
			throw help_all();
		}
		if (it->first == "setprecision")
		{
			if (args.size() == 1)
			{
				setPrecision(stold(args[0]));
				throw "";
			}
			else
				throw LOG("Function setprecision requires one argument");
		}

		int paramCount = it->second.getParamVect().size();
		if (args.size() != paramCount)
		{
			std::string message = "Error: expected " + std::to_string(paramCount) + " argument";
			if (paramCount != 1)
				message += "s";
			message += " for function " + it->first;
			throw LOG(message);
		}

		evalArgs(args);
		input.insert(pos, callMacro(it, args));
		return true;
	}
}

std::string Calc::callMacro(std::map<std::string, Macro>::iterator it, std::vector<std::string> args)
{
	// get the macro's formula and parameters
	std::string formula = it->second.getFormula();
	std::vector<std::string> params = it->second.getParamVect();

	// create a new calculator that saves the macro's arguments as variables named by the parameters
	Calc c(this, params, args);

	// evaluate the macro
	std::string result = c.calc(formula);
	rethrowAnyErrors(result);

	result.insert(0, " (");
	result.append(") ");
	return result;
}

// only for calling macros
Calc::Calc(Calc* other, std::vector<std::string> params, std::vector<std::string> args)
{
	finalPrecision = other->finalPrecision + 5;
	precision = other->precision + 5;
	vars = other->vars;
	macros = other->macros;
	funcs = other->funcs;

	// create variables for each macro argument
	for (int i = 0; i < args.size(); i++)
		setSymbol<double>(vars, params[i], stold(calc(args[i])));
}

bool Calc::findFunction(std::string& input, int pos, int size)
{
	std::string name = input.substr(pos, size);

	std::map<std::string, std::any>::iterator it = funcs.find(name);
	if (it != funcs.end())
	{
		resolveFunctionType(it->second, input, pos, size);
		return true;
	}

	return false;
}

void Calc::resolveFunctionType(std::any func, std::string& input, int pos, int size)
{
	try
	{
		if (func.type().name() == typeid(long double(*)(long double)).name())
			call(std::any_cast<long double(*)(long double)>(func), input, pos, size);
		else if (func.type().name() == typeid(std::string(*)(void)).name())
			call(std::any_cast<std::string(*)(void)>(func), input, pos, size);
		else if (func.type().name() == typeid(void(*)(int, int, int)).name())
			call(std::any_cast<void(*)(int, int, int)>(func), input, pos, size);
		else
			throw LOG("Code error: The type of function " + input.substr(pos, size) + " is not yet supported.");
	}
	catch (const std::bad_any_cast& error)
	{
		throw LOG(error.what());
	}
}

std::string Calc::help_varsAndMacros()
{
	std::string message = "";

	std::map<std::string, double>::iterator it;
	for (it = vars.begin(); it != vars.end(); it++)
	{
		std::stringstream ss;
		ss.setf(std::ios::fixed);
		ss.precision(finalPrecision);
		ss << it->second;
		std::string num = ss.str();

		formatOutput(num, finalPrecision);
		message += "\n " + it->first + " = " + num;
	}

	std::map<std::string, Macro>::iterator it2;
	for (it2 = macros.begin(); it2 != macros.end(); it2++)
		message += "\n " + it2->first + "(" + it2->second.getParamStr() + ")" + " = " + it2->second.getFormula();

	return message;
}

// throw info about all symbols
std::string Calc::help_all()
{
	std::string message = help_varsAndMacros();
	message += "\n";

	std::map<std::string, std::any>::iterator it;
	int i = 0;
	for (it = funcs.begin(); it != funcs.end(); it++, i++)
	{
		if (i % 10 == 0)
			message += "\n ";
		message += it->first + ", ";
	}

	throw message;
}

// throw info about one symbol
std::string Calc::help(std::string name)
{
	std::string message = "";

	std::map<std::string, double>::iterator it = vars.find(name);
	if (it != vars.end())
	{
		std::stringstream ss;
		ss.setf(std::ios::fixed);
		ss.precision(finalPrecision);
		ss << it->second;
		std::string num = ss.str();

		formatOutput(num, finalPrecision);
		message += "Variable " + it->first + " = " + num;
		throw message;
	}

	std::map<std::string, Macro>::iterator it2 = macros.find(name);
	if (it2 != macros.end())
	{
		message += "Function " + it2->first + "(" + it2->second.getParamStr() + ")" + " = " + it2->second.getFormula();
		throw message;
	}

	std::map<std::string, std::any>::iterator it3 = funcs.find(name);
	if (it3 != funcs.end())
		throw "C++ Function";

	throw LOG(name + " is undefined");
}

void Calc::call(long double(*funcPtr)(long double), std::string& input, int pos, int size)
{
	std::vector<std::string> args = splitArgs<long double, long double>(input, pos, size);
	evalArgs(args);

	std::stringstream ss;
	ss << funcPtr(stold(args[0]));
	ss.setf(std::ios::fixed);
	ss.precision(precision);

	insertFunctionResult(input, pos, size, ss.str());
}

void Calc::call(std::string(*funcPtr)(), std::string& input, int pos, int size)
{
	cleanForNoArgs(input, input.substr(pos, size), pos + size);
	insertFunctionResult(input, pos, size, funcPtr());
}

void Calc::call(void(*funcPtr)(int, int, int), std::string& input, int pos, int size)
{
	std::vector<std::string> args = splitArgs<void, int, int, int>(input, pos, size);
	evalArgs(args);
	funcPtr(stoi(args[0]), stoi(args[1]), stoi(args[2]));
}

// Cleans the input string. This should be called before calculator functions that do not take arguments.
void Calc::cleanForNoArgs(std::string& input, std::string funcName, int argPos)
{
	if (input[argPos] != '(')
		throw LOG("Error: expected '(' after name of function " + funcName);

	bool foundArg = false;
	for (int i = argPos + 1; i < input.size(); i++)
	{
		if (input[i] == ')')
		{
			if (foundArg)
				throw LOG("Error: expected 0 arguments for function " + funcName);

			input.erase(argPos, i - argPos + 1);
			return;
		}
		else if (input[i] != ' ')
			foundArg = true;
	}
}

std::vector<std::string> Calc::splitArgString(std::string& input, int argPos)
{
	int parentheses = 0;

	if (input[argPos] != '(')
		throw LOG("Error: expected '(' after function name");

	// split the arguments
	std::vector<std::string> args;
	for (int j = argPos + 1, k = j, m = j - 1; ; j++)
	{
		if (j > input.size())
			throw LOG("Invalid syntax");
		if (j == input.size())
		{
			args.push_back(input.substr(k, j - k));
			input.erase(argPos, j - m + 1);
			break;
		}
		if (input[j] == '(')
			parentheses++;
		if (input[j] == ')')
		{
			if (parentheses)
				parentheses--;
			else
			{
				args.push_back(input.substr(k, j - k));
				input.erase(argPos, j - m + 1);
				break;
			}
		}
		if (input[j] == ',')
		{
			args.push_back(input.substr(k, j - k));
			j++;
			k = j;
		}
	}

	return args;
}

// splits the args, validates the amount, and deletes them from the input string
template <class T, class ...Ts>
std::vector<std::string> Calc::splitArgs(std::string& input, int pos, int size)
{
	std::vector<std::string> args = splitArgString(input, pos + size);

	int sizeTs = sizeof...(Ts);
	if (args.size() != sizeTs)
	{
		std::string message = "Error: expected " + std::to_string(sizeTs) + " argument";
		if (sizeTs != 1)
			message += "s";
		message += " for function " + input.substr(pos, size);
		throw LOG(message);
	}

	return args;
}

void Calc::evalArgs(std::vector<std::string>& args)
{
	// evaluate each argument
	for (int i = 0; i < args.size(); i++)
	{
		Calc calc(this); // the new calculator MUST have access to any symbols created by the user
		args[i] = calc(args[i]);
		rethrowAnyErrors(args[i]);
	}
}

// This function should be called after the operator() function call of any calculator besides the one in main()
void Calc::rethrowAnyErrors(std::string str)
{
	if (str == "")
		throw LOG("Invalid syntax");
	for (int i = 0; i < str.size(); i++)
	{
		if (isAlpha(str[i]))
			throw LOG(str);
	}
}

void Calc::insertFunctionResult(std::string& input, int pos, int size, std::string result)
{
	// If the result of a sine call is in scientific notation with
	// a negative exponent, set the result to zero
	for (int i = 0; i < result.size(); i++)
	{
		if (result[i] == 'e')
		{
			if (input.substr(pos, size) == "sin" && i < result.size() - 1 && result[i + 1] == '-')
				result = "0";
			else
				throw LOG("Error: program not yet equipped for scientific notation");
		}
	}

	if (result == "-nan(ind)" || result == "nan")
		throw "Imaginary";
	input.erase(pos, size);
	input.insert(pos, "(" + result + ")");
}
