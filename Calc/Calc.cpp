#include "Calc.h"

std::string Calc::calc(std::string input)
{
	/*
		Reads the input string and pushes values onto the appropriate stack. Values are popped off the stacks
		and evaluated whenever an operator of lower precedence is found following one of higher precedence.
	 */

	std::string result;

	try
	{
		formatInput(input);

		for (int i = 0; i < input.size();) // the index is incremented when value(s) are pushed onto a stack
		{
			if (isNumber(input[i]))
			{
				int numLength = getNumLength(input.substr(i, input.size() - i));
				nums.push(stod(input.substr(i, numLength)));
				i += numLength;
			}
			else if (isOp(input[i]))
			{
				int opLength = getOpLength(input.substr(i, input.size() - i));
				std::string newOp = input.substr(i, opLength);

				if (ops.empty())
				{
					if (newOp == "-")
					{
						if (i == 0)
							ops.push("negate");
						else
							ops.push("subtract");
					}
					else if (nums.empty() && newOp == "!")
						throw "Invalid syntax";
					else
						ops.push(newOp);
					i += opLength;
				}
				else
				{
					if (newOp == "(")
					{
						if (i > 0 && isNumber(input[i - 1]))
						{
							if (ops.top() == "^" || ops.top() == "*" || ops.top() == "/")
								pop();
							else
							{
								ops.push("*");
								ops.push(input.substr(i, 1));
								i++;
							}
						}
						else
						{
							ops.push(newOp);
							i++;
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
					else if (newOp == "!" || newOp == "^" || newOp == "*" || newOp == "/"
						|| newOp == "+" || newOp == "%" || newOp == "==" || newOp == ">="
						|| newOp == "<=" || newOp == "!=" || newOp == ">" || newOp == "<")
					{
						if (hasPrecedence(newOp))
						{
							ops.push(newOp);
							i += opLength;
						}
						else
							pop();
					}
					else if (newOp == "-")
					{
						if (i == 0 || isOp(input[i - 1]))
							newOp = "negate";
						else
							newOp = "subtract";

						if (newOp == "negate" || hasPrecedence(newOp))
						{
							ops.push(newOp);
							i++;
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

		if (!input.size())
			throw "";
		while (!ops.empty())
			pop();
		while (nums.size() > 1) // remaining numbers will be multiplied together
			pop();

		result = std::to_string(nums.top());
	}
	catch (const char* error)
	{
		result = error;
	}
	catch (std::bad_alloc)
	{
		result = "Insufficient memory";
	}

	while (!nums.empty())
		nums.pop();
	while (!ops.empty())
		ops.pop();
	formatOutput(result);
	return result;
}

void Calc::formatInput(std::string& input)
{
	// remove all spaces from the input string
	for (int i = 0; i < input.size();)
	{
		if (input[i] == ' ')
			input.erase(i, 1);
		else
			i++;
	}

	// check for invalid syntax: multiple operators next to each other
	for (int i = 1; i < input.size(); i++)
	{
		char ch1 = input[i - 1],
			ch2 = input[i];
		if (isOp(ch2) && ch2 != '-' && ch2 != '(' && ch2 != ')' && ch2 != '=')
		{
			if (isOp(ch1) && ch1 != ')' && (ch1 != '!' || ch1 == '!' && ch2 == '!' && i < input.size() - 1 && input[i + 1] != '='))
				throw "Invalid syntax";
		}
	}
}

void Calc::formatOutput(std::string& str)
{
	if (str == "inf")
		str = "Infinity";

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

	if (str == "-0")
		str = "0";

	if (str.size())
		str.insert(0, "\n = ");
}

bool Calc::isNumber(char ch)
{
	if (ch >= '0' && ch <= '9' || ch == '.')
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

int Calc::getNumLength(std::string str)
{
	bool periodFound = false;
	for (int i = 0; i < str.size(); i++)
	{
		if (str[i] == '.')
		{
			if (periodFound || str.size() == 1)
				throw "Invalid syntax";
			periodFound = true;
		}
		else if (!isNumber(str[i]))
		{
			if (i == 1 && str[0] == '.')
				throw "Invalid syntax";
			return i;
		}
	}

	return str.size();
}

int Calc::getOpLength(std::string str)
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