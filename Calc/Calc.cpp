#include "Calc.h"

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
			setSymbol(varsBeingDefined.top(), result);
			varsBeingDefined.pop();
		}

		if (assigning)
			return "";
		formatOutput(result);
	}
	catch (const char* error)
	{
		result = error;
	}
	catch (std::bad_alloc)
	{
		result = "Insufficient memory";
	}

	if (result.size())
		result.insert(0, " = ");
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
			if (input[i] == '=') // either this is an assignment operator or there isn't a valid one
			{
				assigning = true;
				break;
			}
		}

		if (!assigning)
			return;

		// verify whether input[i] is an assignment operator
		if (i < input.size() - 1 && input[i + 1] != '=')
		{
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

			// remove all preceding and succeeding spaces
			for (int j = 0; j < varName.size(); j++)
			{
				if (varName[j] == ' ')
					varName.erase(j--, 1);
			}

			varsBeingDefined.push(varName);
		}
		else
			return;
	}
}

std::string Calc::evaluate(std::string input)
{
	/*
		Reads the input string and pushes values onto the appropriate stack. Values are popped off the stacks
		and evaluated whenever an operator of lower precedence is found following one of higher precedence.
	 */

	std::string result;
	lastTypePushed = "";

	for (int i = 0; i < input.size();) // the index is incremented when value(s) are pushed onto a stack
	{
		if (isNum(input[i]))
		{
			if (lastTypePushed == "num")
				input.insert(i, "*");
			else
			{
				int numSize = getNumSize(input.substr(i, input.size() - i));
				nums.push(stold(input.substr(i, numSize)));
				i += numSize;
				lastTypePushed = "num";
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
		{
			int opSize = getOpSize(input.substr(i, input.size() - i));
			std::string newOp = input.substr(i, opSize);

			if (ops.empty())
			{
				if (newOp == "-")
				{
					if (lastTypePushed == "")
						ops.push("negate");
					else
						ops.push("subtract");
					lastTypePushed = "op";
				}
				else if (nums.empty() && newOp == "!")
					throw "Invalid syntax";
				else
				{
					ops.push(newOp);
					lastTypePushed = "op";
				}

				i += opSize;
			}
			else
			{
				if (newOp == "(")
				{
					if (i > 0 && lastTypePushed == "num")
					{
						if (ops.top() == "^" || ops.top() == "*" || ops.top() == "/")
							pop();
						else
						{
							ops.push("*");
							ops.push(input.substr(i, 1));
							i++;
							lastTypePushed = "op";
						}
					}
					else
					{
						ops.push(newOp);
						i++;
						lastTypePushed = "op";
					}
				}
				else if (newOp == ")")
				{
					while (!ops.empty() && ops.top() != "(")
						pop();
					if (ops.empty())
						throw "Invalid syntax";
					pop();
					i++;
				}
				else if (newOp == "!" || newOp == "*" || newOp == "/" || newOp == "+"
					|| newOp == "%" || newOp == "==" || newOp == ">=" || newOp == "<="
					|| newOp == "!=" || newOp == ">" || newOp == "<")
				{
					if (hasPrecedence(newOp))
					{
						ops.push(newOp);
						i += opSize;
						lastTypePushed = "op";
					}
					else
						pop();
				}
				else if (newOp == "^")
				{
					if (ops.top() == "^" || hasPrecedence(newOp))
					{
						ops.push(newOp);
						i += opSize;
						lastTypePushed = "op";
					}
					else
						pop();
				}
				else if (newOp == "-")
				{
					if (lastTypePushed == "" || lastTypePushed == "op")
						newOp = "negate";
					else
						newOp = "subtract";

					if (newOp == "negate" || hasPrecedence(newOp))
					{
						ops.push(newOp);
						i++;
						lastTypePushed = "op";
					}
					else
						pop();
				}
				else
					throw "Invalid syntax";
			}
		}
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
	ss.precision(p); // precision will be reduced by five after this, before printing
	ss << nums.top();
	result = ss.str();
	setSymbol("ans", result);
	return result;
}

void Calc::formatOutput(std::string& str)
{
	// adjust output precision // TODO: allow the user to adjust precision
	std::stringstream ss;
	ss.setf(std::ios::fixed);
	ss.precision(Precision);
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
