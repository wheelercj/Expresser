#include "Common.h"

bool is_num(char ch)
{
	if (ch >= '0' && ch <= '9' || ch == '.')
		return true;
	return false;
}

bool is_alpha(char ch)
{
	ch = tolower(ch);
	if (ch >= 'a' && ch <= 'z' || ch == '_')
		return true;
	return false;
}

bool is_op(char ch)
{
	std::string valid_ops = "()^*/+-!%<>=";
	if (valid_ops.find(ch) != std::string::npos)
		return true;
	return false;
}

int get_num_size(std::string str)
{
	bool period_found = false;
	for (int i = 0; i < str.size(); i++)
	{
		if (str[i] == '.')
		{
			if (period_found)
				throw LOG("Error: multiple periods in one number");
			if (str.size() == 1)
				throw LOG("Invalid use of a period");

			period_found = true;
		}
		else if (!is_num(str[i]))
		{
			if (i == 1 && str[0] == '.')
				throw LOG("Invalid use of a period");

			return i;
		}
	}

	return str.size();
}

int get_alpha_size(std::string str)
{
	int i = 1;
	for (; i < str.size(); i++)
	{
		if (!is_alpha(str[i]))
			break;
	}

	return i;
}

int get_op_size(std::string str)
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

bool has_precedence(std::string op1, std::string op2)
{
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

void remove_edge_spaces(std::string& str)
{
	while (str[0] == ' ')
		str.erase(0, 1);
	while (str[str.size() - 1] == ' ')
		str.erase(str.size() - 1, 1);
}

// check for multiple operators or periods next to each other
void validate_input(std::string& input)
{
	for (int i = 1; i < input.size(); i++)
	{
		char ch1 = input[i - 1],
			ch2 = input[i];

		if (ch1 == '.' && ch2 == '.')
			throw LOG("Invalid syntax: periods next to each other");
		else if (is_op(ch2) && ch2 != '-' && ch2 != '(' && ch2 != ')' && ch2 != '=')
		{
			if (is_op(ch1) && ch1 != ')' && (ch1 != '!' || ch1 == '!'
				&& ch2 == '!' && i < input.size() - 1 && input[i + 1] != '='))
			{
				std::string message = "Invalid syntax: ";
				message += ch1;
				message += ch2;
				throw LOG(message);
			}
		}
	}
}

void format_output(std::string& str, int precision)
{
	// adjust output precision
	std::stringstream ss;
	ss.setf(std::ios::fixed);
	ss.precision(precision);

	try
	{
		for (int i = 0; i < str.size(); i++)
		{
			if (is_alpha(str[i]))
			{
				if (str == "inf")
					str = LOG("Infinity");
				return;
			}
		}

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
	}
	catch (std::invalid_argument)
	{
		LOG("Caught an invalid argument error");
	}


	if (str == "-0")
		str = "0";
}

std::vector<std::string> read_params(std::string str)
{
	std::vector<std::string> params;
	bool alpha_found = false;
	bool space_after_alpha = false;
	for (int i = 0, j = 1; i < str.size(); i++)
	{
		if (is_alpha(str[i]))
		{
			alpha_found = true;
			if (space_after_alpha)
				throw LOG("Invalid space in parameter name");
		}
		else if (str[i] == ' ')
		{
			if (alpha_found)
				space_after_alpha = true;
		}
		else if (str[i] == ',' || str[i] == ')')
		{
			std::string param = str.substr(j, i - j);
			if (param == "")
				throw LOG("Invalid syntax: unnamed parameter");
			params.push_back(param);
			j = i + 1;
			alpha_found = false;
			space_after_alpha = false;

			if (str[i] == ')')
				break;
		}
		else if (is_op(str[i]))
		{
			if (str[i] != '(' || i > 0)
			{
				std::string message = "Invalid character in parameter list: ";
				message += str[i];
				throw LOG(message);
			}
		}
		else
		{
			std::string message = "Invalid character in parameter list: ";
			message += str[i];
			throw LOG(message);
		}
	}

	return params;
}
