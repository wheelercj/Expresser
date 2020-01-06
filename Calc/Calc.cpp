#include "Calc.h"
#include <vector>

Calc::Calc()
{
}

Calc::Calc(Calc* other)
{
	vars = other->vars;
	macros = other->macros;
	funcs = other->funcs;
	Precision = other->Precision + 5;
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
		formatOutput(result, Precision);
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

void Calc::validateInput(std::string& input)
{
	// check for invalid syntax: multiple operators next to each other
	for (int i = 1, j = 0; i < input.size() && j < input.size(); i++, j++)
	{
		// skip over spaces
		while (j < input.size() && input[j] == ' ')
			j++;
		while (i < input.size() && (input[i] == ' ') || i == j)
			i++;
		if (j >= input.size() || i >= input.size())
			return;

		char ch1 = input[j],
			ch2 = input[i];
		if (isOp(ch2) && ch2 != '-' && ch2 != '(' && ch2 != ')' && ch2 != '=')
		{
			if (isOp(ch1) && ch1 != ')' && (ch1 != '!' || ch1 == '!' && ch2 == '!' && i < input.size() - 1 && input[i + 1] != '='))
				throw "Invalid syntax";
		}
	}
}

void Calc::formatOutput(std::string& str, int precision)
{
	// adjust output precision
	std::stringstream ss;
	ss.setf(std::ios::fixed);
	ss.precision(precision);
	ss << stold(str);
	str = ss.str();

	// remove any trailing zeros
	for (int i = str.size() - 1; i > 0; i--)
	{
		if (str[i] == '0')
			str.erase(i, 1);
		else if (str[i] == '.')
		{
			str.erase(i, 1);
			break;
		}
		else
			break;
	}

	if (str == "inf")
		str = "Infinity";
	else if (str == "-0")
		str = "0";
}

// search for an assignment operator and prepare for assigning if needed
void Calc::assignmentFormat(std::string& input)
{
	bool assigning, alphaFound;

	while (true)
	{
		assigning = false;
		alphaFound = false;

		// search for an assignment operator
		int i = 0;
		for (; i < input.size(); i++)
		{
			if (input[i] == '=')
			{
				// either input[i] is an assignment operator or there isn't a valid one
				if (i == input.size() - 1 || input[i + 1] == '=')
					return;
				assigning = true;
				break;
			}
		}

		if (!assigning)
			return;

		bool spaceAfterAlpha = false;
		for (int j = 0; j < i; j++)
		{
			if (isAlpha(input[j]))
				alphaFound = true;
			else if (alphaFound && input[j] == ' ')
				spaceAfterAlpha = true;
			if (spaceAfterAlpha && isAlpha(input[j]) || !(isAlpha(input[j]) || input[j] == ' '))
				return;
		}

		if (!alphaFound)
			return;

		std::string varName = input.substr(0, i);
		input.erase(0, i + 1);

		// remove all spaces
		for (int j = 0; j < varName.size(); j++)
		{
			if (varName[j] == ' ')
				varName.erase(j--, 1);
		}

		varsBeingDefined.push(varName);
	}
}

std::string Calc::evaluate(std::string input)
{
	/*
		Reads the input string and pushes values onto the appropriate stack. Values are popped off the stacks
		and evaluated whenever an operator of lower precedence is found following one of higher precedence.
	 */

	std::string result;
	lastTypePushed = NONE;

	for (int i = 0; i < input.size();) // the index is incremented when value(s) are pushed onto a stack
	{
		if (isNum(input[i]))
		{
			if (lastTypePushed == NUM)
				input.insert(i, "*");
			else
			{
				int numSize = getNumSize(input.substr(i, input.size() - i));
				nums.push(stold(input.substr(i, numSize)));
				i += numSize;
				lastTypePushed = NUM;
			}
		}
		else if (input[i] == ' ')
			i++;
		else if (isAlpha(input[i]))
		{
			int alphaSize = getAlphaSize(input.substr(i, input.size() - i));
			if (!getSymbolValue(input, i, alphaSize))
				throw "Undefined character";
		}
		else if (isOp(input[i]))
			readOp(input, i);
		else
			throw "Undefined character";
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
	while (nums.size() > 1) // remaining numbers will be multiplied together
		pop();

	std::stringstream ss;
	ss.setf(std::ios::fixed);
	int p = Precision + 5;
	ss.precision(p);
	ss << nums.top();
	result = ss.str();
	setSymbol<double>(vars, "ans", stold(result));
	return result;
}

// pop and evaluate number(s) and/or operator(s)
void Calc::pop()
{
	if (nums.empty())
		throw "Invalid syntax";

	std::string op;
	if (ops.empty())
		op = "*";
	else
	{
		if (ops.top() == "(")
		{
			ops.pop();
			return;
		}
		else if (ops.top() == "negate")
		{
			double temp = nums.top();
			nums.pop();
			temp *= -1;
			nums.push(temp);
			ops.pop();
			return;
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
			return;
		}
		else
		{
			op = ops.top();
			ops.pop();
		}
	}

	if (nums.size() == 1)
		throw "Invalid syntax";

	double num2 = nums.top();
	nums.pop();
	double num1 = nums.top();
	nums.pop();

	if (op == "^")
	{
		if (num1 == 0 && num2 == 0)
			throw "Indeterminate";
		else if (num1 < 0 && num2 < 1 && (int)pow(num2, -1) % 2 == 0)
			throw "Imaginary";
		nums.push(pow(num1, num2));
	}
	else if (op == "*")
		nums.push(num1 * num2);
	else if (op == "/")
	{
		if (num2 == 0)
		{
			if (num1 == 0)
				throw "Indeterminate";
			throw "Infinity";
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
			throw "Undefined";
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
		throw "Invalid syntax";
}

bool Calc::isNum(char ch)
{
	if (ch >= '0' && ch <= '9' || ch == '.')
		return true;
	return false;
}

bool Calc::isAlpha(char ch)
{
	ch = tolower(ch);
	if (ch >= 'a' && ch <= 'z' || ch == '_')
		return true;
	return false;
}

bool Calc::isOp(char ch)
{
	std::string validOps = "()^*/+-!%<>=";
	if (validOps.find(ch) != std::string::npos)
		return true;
	return false;
}

int Calc::getNumSize(std::string str)
{
	bool periodFound = false;
	for (int i = 0; i < str.size(); i++)
	{
		if (str[i] == '.')
		{
			if (periodFound || str.size() == 1)
				throw "Invalid syntax"; // TODO: make all error messages more specific
			periodFound = true;
		}
		else if (!isNum(str[i]))
		{
			if (i == 1 && str[0] == '.')
				throw "Invalid syntax";
			return i;
		}
	}

	return str.size();
}

int Calc::getAlphaSize(std::string substr)
{
	int i = 1;
	for (; i < substr.size(); i++)
	{
		char ch = tolower(substr[i]);
		if ((ch < 'a' || ch > 'z') && ch != '_')
			break;
	}

	return i;
}

int Calc::getOpSize(std::string str)
{
	if (str.size() > 1)
	{
		if (str[0] == '!' || str[0] == '=' || str[0] == '>' || str[0] == '<')
		{
			if (str[1] == '=' && !(str.size() > 2 && str[2] == '='))
				return 2;
		}
	}

	return 1;
}

void Calc::readOp(std::string input, int& pos)
{
	int opSize = getOpSize(input.substr(pos, input.size() - pos));
	std::string newOp = input.substr(pos, opSize);

	if (ops.empty())
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
			throw "Invalid syntax";
		else
		{
			ops.push(newOp);
			lastTypePushed = OP;
		}

		pos += opSize;
	}
	else
	{
		if (newOp == "(")
		{
			if (pos > 0 && lastTypePushed == NUM)
			{
				if (ops.top() == "^" || ops.top() == "*" || ops.top() == "/")
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
				ops.push(newOp);
				pos++;
				lastTypePushed = OP;
			}
		}
		else if (newOp == ")")
		{
			while (!ops.empty() && ops.top() != "(")
				pop();
			if (ops.empty())
				throw "Invalid syntax";
			pop();
			pos++;
		}
		else if (newOp == "!" || newOp == "*" || newOp == "/" || newOp == "+"
			|| newOp == "%" || newOp == "==" || newOp == ">=" || newOp == "<="
			|| newOp == "!=" || newOp == ">" || newOp == "<")
		{
			if (hasPrecedence(newOp))
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
			if (ops.top() == "^" || hasPrecedence(newOp))
			{
				ops.push(newOp);
				pos += opSize;
				lastTypePushed = OP;
			}
			else
				pop();
		}
		else if (newOp == "-")
		{
			if (lastTypePushed == NONE || lastTypePushed == OP)
				newOp = "negate";
			else
				newOp = "subtract";

			if (newOp == "negate" || hasPrecedence(newOp))
			{
				ops.push(newOp);
				pos++;
				lastTypePushed = OP;
			}
			else
				pop();
		}
		else
			throw "Invalid syntax";
	}
}

bool Calc::hasPrecedence(std::string op1)
{
	std::string op2 = ops.top();
	std::vector<std::string> order = { "!", "^", "negate", "*", "+", "%", "==", "(" };

	// Replace some ops with others locally so that the order vector does not imply
	// that some ops with the same precedence have different precedences.
	if (op1 == "/")
		op1 = "*";
	else if (op1 == "subtract")
		op1 = "+";
	else if (op1 == ">=" || op1 == "<=" || op1 == "!=" || op1 == ">" || op1 == "<")
		op1 = "==";
	if (op2 == "/")
		op2 = "*";
	else if (op2 == "subtract")
		op2 = "+";
	else if (op2 == ">=" || op2 == "<=" || op2 == "!=" || op2 == ">" || op2 == "<")
		op2 = "==";

	for (int i = 0; i < order.size(); i++)
	{
		if (order[i] == op2)
			return false;
		if (order[i] == op1)
			return true;
	}
}

template<class T>
void Calc::setSymbol(std::unordered_map<std::string, T>& hashTable, std::string newName, T newSymbol)
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
			std::string substr = input.substr(pos, size);

			// Variables
			std::unordered_map<std::string, double>::iterator it = vars.find(substr);
			if (it != vars.end())
			{
				// replace the variable name with its value
				input.erase(pos, size);
				std::stringstream ss;
				ss.setf(std::ios::fixed);
				int p = Precision + 5;
				ss.precision(p);
				ss << " " << it->second << " ";
				input.insert(pos, ss.str());
				return true;
			}
			
			// Macros
			std::unordered_map<std::string, Macro>::iterator it2 = macros.find(substr);
			if (it2 != macros.end())
			{
				std::vector<std::string> args = readArgs(input, pos, size);

				if (it2->first == "help")
				{
					// call a help function that throws a message
					if (args.size() && args[0] != "")
						help(args[0]);
					help();
				}
				if (it2->first == "setprecision")
				{
					// adjust output precision and throw an empty string
					if (args.size())
						setprecision(stold(args[0]));
					else
						throw "Invalid syntax";
				}
				if (it2->first == "rand")
					throw random();

				if (args.size() != it2->second.getParamVect().size())
					throw "Invalid syntax";

				// evaluate each argument
				Calc c2(this);
				for (int i = 0; i < args.size(); i++)
				{
					args[i] = c2.calc(args[i]);

					// rethrow messages
					if (args[i] == "")
						throw "Invalid syntax";
					for (int j = 0; j < args[i].size(); j++)
					{
						if (isAlpha(args[i][j]))
							throw args[i];
					}
				}

				// expand the macro and insert its return value
				input.insert(pos, " " + it2->second(args) + " ");
				return true;
			}

			// Functions
			std::unordered_map<std::string, Function>::iterator it3 = funcs.find(substr);
			if (it3 != funcs.end())
			{
				std::vector<std::string> args = readArgs(input, pos, size);
				if (args.size() != 1)
					throw "Invalid syntax";

				// evaluate each argument
				Calc c2(this);
				for (int i = 0; i < args.size(); i++)
				{
					args[i] = c2.calc(args[i]);
					
					// rethrow messages
					if (args[i] == "")
						throw "Invalid syntax";
					for (int j = 0; j < args[i].size(); j++)
					{
						if (isAlpha(args[i][j]))
							throw args[i];
					}
				}

				// call the function and insert its return value
				std::string result = it3->second(args);
				if (result == "-nan(ind)")
					throw "Imaginary";
				input.insert(pos, " " + result + " ");
				return true;
			}
		}
	}

	// the character(s) are undefined
	return false;
}

std::vector<std::string> Calc::readArgs(std::string& input, int pos, int size)
{
	int parentheses = 0;

	if (input[pos + size] != '(')
		throw "Invalid syntax";

	// get the arguments
	std::vector<std::string> args;
	for (int j = pos + size + 1, k = j, m = j; ; j++)
	{
		if (j > input.size())
			throw "Invalid syntax";
		if (j == input.size())
		{
			if (j == pos + size + 1)
				throw "Invalid syntax";
			args.push_back(input.substr(k, j - k));
			input.erase(pos, size + j - m + 1);
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
				input.erase(j, 1);
				args.push_back(input.substr(k, j - k));
				input.erase(pos, size + j);
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

// throw info about all symbols
void Calc::help()
{
	std::string message = "";

	message += "\n Variables:";
	std::unordered_map<std::string, double>::iterator it;
	for (it = vars.begin(); it != vars.end(); it++)
	{
		std::stringstream ss;
		ss.setf(std::ios::fixed);
		int p = Precision + 5;
		ss.precision(p);
		ss << it->second;
		std::string num = ss.str();
		formatOutput(num, Precision + 5);
		message += "\n\t " + it->first + " = " + num;
	}

	message += "\n Functions:\t";
	std::unordered_map<std::string, Function>::iterator it3;
	int i = 0;
	for (it3 = funcs.begin(); it3 != funcs.end(); it3++, i++)
	{
		if (i % 10 == 0)
			message += "\n\t";
		message += it3->first + ", ";
	}

	message += "\n Macros:";
	std::unordered_map<std::string, Macro>::iterator it2;
	for (it2 = macros.begin(); it2 != macros.end(); it2++)
		message += "\n\t " + it2->first + "(" + it2->second.getParamStr() + ")" + " = " + it2->second.getFunc();

	throw message;
}

// throw info about one symbol
void Calc::help(std::string name)
{
	std::string message = "";

	std::unordered_map<std::string, double>::iterator it = vars.find(name);
	if (it != vars.end())
	{
		std::stringstream ss;
		ss.setf(std::ios::fixed);
		int p = Precision + 5;
		ss.precision(p);
		ss << it->second;
		std::string num = ss.str();
		formatOutput(num, Precision + 5);
		message += "Variable " + it->first + " = " + num;
		throw message;
	}

	std::unordered_map<std::string, Macro>::iterator it2 = macros.find(name);
	if (it2 != macros.end())
	{
		message += "Macro " + it2->first + "(" + it2->second.getParamStr() + ")" + " = " + it2->second.getFunc();
		throw message;
	}

	std::unordered_map<std::string, Function>::iterator it3 = funcs.find(name);
	if (it3 != funcs.end())
		throw "C++ Function";

	throw "Undefined character(s)";
}

void Calc::setprecision(int num)
{
	Precision = num;
	throw "";
}

std::string Calc::random()
{
	srand((unsigned)time(0));
	double r = (rand() % 101) / 100.0;
	std::stringstream ss;
	ss.setf(std::ios::fixed);
	int p = Precision + 5;
	ss.precision(p);
	ss << r;
	return ss.str();
}
