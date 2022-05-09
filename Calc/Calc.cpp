#include "Calc.h"
#include <iostream>

Calc::Calc()
{
	_funcs = default_funcs;

	// load any saved symbols from a file
	std::ifstream file("saved_symbols.txt");
	if (!file)
	{
		LOG("No file with saved symbols found.");
		_vars = default_vars;
		_macros = default_macros;
	}
	else
	{
		for (std::string line; std::getline(file, line);)
			_evaluate(line);

		file.close();
		LOG("Loaded saved symbols from a file.");
	}
}

Calc::~Calc()
{
	// save all symbols to a file
	std::ofstream file("saved_symbols.txt", std::ios::trunc);
	_precision += 5;
	file << _help_with_vars_and_macros();
	file.close();
}

// for loading only the default symbols
Calc::Calc(int new_precision)
{
	_final_precision = new_precision;
	_precision = _final_precision + 5;

	_vars = default_vars;
	_macros = default_macros;
	_funcs = default_funcs;
}

Calc::Calc(Calc* other)
{
	_final_precision = other->_final_precision + 5;
	_precision = other->_precision + 5;
	_vars = other->_vars;
	_macros = other->_macros;
	_funcs = other->_funcs;
}

std::string Calc::operator()(std::string input)
{
	std::string result = _evaluate(input);
	format_global_output(result, _final_precision);
	return result;
}

std::string Calc::_evaluate(std::string input)
{
	// make sure the numbers and operators stacks are clear 
	while (!_nums.empty())
		_nums.pop();
	while (!_ops.empty())
		_ops.pop();

	std::string result;
	try
	{
		validate_input(input);
		_detect_assignment(input);
		result = _parse_input(input);

		bool assigning = false;
		while (!_vars_being_defined.empty())
		{
			assigning = true;
			_set_symbol<double>(_vars, _vars_being_defined.top(), stold(result));
			_vars_being_defined.pop();
		}

		if (assigning)
			return "";
		_set_symbol<double>(_vars, "ans", stold(result));
	}
	catch (const char* message)
	{
		result = message;
	}
	catch (std::string message)
	{
		result = message;
	}
	catch (std::bad_alloc)
	{
		result = "Insufficient memory";
	}

	return result;
}

void Calc::_reset_symbols()
{
	_vars = default_vars;
	_macros = default_macros;
	_funcs = default_funcs;
}

void Calc::_set_precision(int num)
{
	_final_precision = num;
	_precision = _final_precision + 5;
}

int Calc::_get_precision()
{
	return _precision;
}

// search for and handle any assignment operator(s)
void Calc::_detect_assignment(std::string& input)
{
	bool assigning = true;

	// The user can assign a value to multiple variables in a single input, e.g. `a=b=c=5`.
	while (assigning) // One assignment operation per loop iteration.
	{
		assigning = false;
		int eq_pos = 0;
		for (; eq_pos < input.size() && !assigning; eq_pos++)
		{
			if (input[eq_pos] == '=')
			{
				// either input[eqPos] is an assignment operator or there isn't a valid one
				if (eq_pos == 0)
					return; // an assignment op must not be at the beginning of the input...
				if (eq_pos == input.size() - 1 || input[eq_pos + 1] == '=')
					return; // ...nor at the end
				if (eq_pos >= 1)
				{
					char ch = input[eq_pos - 1];
					if (ch == '>' || ch == '<' || ch == '!')
						return; // an assignment op must not be preceded by one of these operators
				}

				assigning = true;
				eq_pos--;
			}
		}

		if (assigning)
		{
			int macro_name_size = find_macro_name_size(input, eq_pos);
			_parse_symbol_definition(input, eq_pos, macro_name_size);
		}
	}
}

void Calc::_parse_symbol_definition(std::string& input, int eq_pos, int macro_name_size)
{
	if (!macro_name_size) // then a variable is being defined
	{
		std::string var_name = input.substr(0, eq_pos);
		input.erase(0, eq_pos + 1);
		remove_edge_spaces(var_name);
		_vars_being_defined.push(var_name);
	}
	else // then a macro is being defined
	{
		if (_vars_being_defined.size())
			throw LOG("Multiple simultaneous definitions are only possible with variables");

		std::string macro_name = input.substr(0, macro_name_size);
		remove_edge_spaces(macro_name);

		std::string param_str = input.substr(macro_name_size, eq_pos - macro_name_size + 1);
		std::vector<std::string> params = read_params(param_str);
		for (int i = 0; i < params.size(); i++)
			remove_edge_spaces(params[i]);

		std::string formula = input.substr(eq_pos + 1, input.size() - eq_pos);
		remove_edge_spaces(formula);

		_set_symbol<Macro>(_macros, macro_name, { params, formula });
		throw "";
	}
}

// read the input string and determine what to do with each part of it
std::string Calc::_parse_input(std::string input)
{
	std::string result,
		temp = "";
	_last_type_pushed = NONE;

	for (int i = 0; i < input.size();)
	{
		if (is_num(input[i]))
			_parse_num(input, i);
		else if (input[i] == ' ')
			i++;
		else if (is_alpha(input[i]))
			_parse_alpha(input, i);
		else if (is_op(input[i]))
			_parse_op(input, i);
		else
		{
			std::string message = "Undefined character: ";
			message += input[i];
			throw LOG(message);
		}
	}

	bool empty_string = true;
	for (int i = 0; i < input.size(); i++)
	{
		if (input[i] != ' ')
			empty_string = false;
	}
	if (empty_string)
		throw "";

	while (!_ops.empty())
		_pop_and_evaluate_ops_and_nums();
	while (_nums.size() > 1) // remaining numbers are multiplied together
		_pop_and_evaluate_ops_and_nums();

	std::stringstream ss;
	ss.setf(std::ios::fixed);
	ss.precision(_precision);
	ss << _nums.top();
	result = ss.str();
	return result;
}

void Calc::_parse_num(std::string& input, int& pos)
{
	if (_last_type_pushed == NUM)
		input.insert(pos, "*");
	else
	{
		int num_size = get_num_size(input.substr(pos, input.size() - pos));
		_nums.push(stold(input.substr(pos, num_size)));
		pos += num_size;
		_last_type_pushed = NUM;
	}
}

void Calc::_parse_alpha(std::string& input, int& pos)
{
	int alpha_size = get_alpha_size(input.substr(pos, input.size() - pos));
	if (!_get_symbol_value(input, pos, alpha_size))
	{
		std::string message = "Undefined character";
		if (alpha_size != 1)
			message += "s";
		message += ": " + input.substr(pos, alpha_size);
		throw LOG(message);
	}
}

void Calc::_parse_op(std::string& input, int& pos)
{
	int op_size = get_op_size(input.substr(pos, input.size() - pos));
	std::string new_op = input.substr(pos, op_size);

	if (_ops.empty() && new_op != ")" && new_op != "(")
		_push_op_onto_empty_stack(pos, new_op, op_size);
	else
		_push_op_onto_nonempty_stack(input, pos, new_op, op_size);
}

void Calc::_push_op_onto_empty_stack(int& pos, std::string new_op, int op_size)
{
	if (new_op == "-")
	{
		if (_last_type_pushed == NONE)
			_ops.push("negate");
		else
			_ops.push("subtract");
		_last_type_pushed = OP;
	}
	else if (_nums.empty() && new_op == "!")
		throw LOG("Error: expected an operand before the factorial operator");
	else
	{
		_ops.push(new_op);
		_last_type_pushed = OP;
	}

	pos += op_size;
}

void Calc::_push_op_onto_nonempty_stack(std::string input, int& pos, std::string new_op, int op_size)
{
	if (new_op == "(")
		_push_open_parenthesis(input, pos);
	else if (new_op == ")")
	{
		while (!_ops.empty() && _ops.top() != "(")
			_pop_and_evaluate_ops_and_nums();
		if (_ops.empty())
			throw LOG("Error: missing an opening parenthesis");
		_pop_and_evaluate_ops_and_nums();
		pos++;
	}
	else if (new_op == "!" || new_op == "*" || new_op == "/" || new_op == "+"
		|| new_op == "%" || new_op == "==" || new_op == ">=" || new_op == "<="
		|| new_op == "!=" || new_op == ">" || new_op == "<")
	{
		if (has_precedence(new_op, _ops.top()))
		{
			_ops.push(new_op);
			pos += op_size;
			_last_type_pushed = OP;
		}
		else
			_pop_and_evaluate_ops_and_nums();
	}
	else if (new_op == "^")
	{
		if (_ops.top() == "^" || has_precedence(new_op, _ops.top()))
		{
			_ops.push(new_op);
			pos += op_size;
			_last_type_pushed = OP;
		}
		else
			_pop_and_evaluate_ops_and_nums();
	}
	else if (new_op == "-")
		_push_minus(pos);
	else
		throw LOG("Undefined operator: " + new_op);
}

void Calc::_push_open_parenthesis(std::string input, int& pos)
{
	if (pos > 0 && _last_type_pushed == NUM)
	{
		if (!_ops.empty() && (_ops.top() == "^" || _ops.top() == "*" || _ops.top() == "/"))
			_pop_and_evaluate_ops_and_nums();
		else
		{
			_ops.push("*");
			_ops.push(input.substr(pos, 1));
			pos++;
			_last_type_pushed = OP;
		}
	}
	else
	{
		_ops.push("(");
		pos++;
		_last_type_pushed = OP;
	}
}

void Calc::_push_minus(int& pos)
{
	std::string new_op;

	if (_last_type_pushed == NONE || _last_type_pushed == OP)
		new_op = "negate";
	else
		new_op = "subtract";

	if (new_op == "negate" || has_precedence(new_op, _ops.top()))
	{
		_ops.push(new_op);
		pos++;
		_last_type_pushed = OP;
	}
	else
		_pop_and_evaluate_ops_and_nums();
}

// pop and evaluate numbers and operators
void Calc::_pop_and_evaluate_ops_and_nums()
{
	if (_nums.empty())
		throw LOG("Error: not enough operands for the given operators");

	std::string op;
	if (_ops.empty())
		op = "*";
	else
	{
		if (_parse_unary_op())
			return;
		op = _ops.top();
		_ops.pop();
	}

	_parse_binary_op(op);
}

bool Calc::_parse_unary_op()
{
	if (_ops.top() == "(")
	{
		_ops.pop();
		return true;
	}
	else if (_ops.top() == "negate")
	{
		double temp = _nums.top();
		_nums.pop();
		temp *= -1;
		_nums.push(temp);
		_ops.pop();
		return true;
	}
	else if (_ops.top() == "!")
	{
		double n = _nums.top(),
			total = 1,
			temp = n;
		_nums.pop();

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

		_nums.push(total);
		_ops.pop();
		return true;
	}
}

void Calc::_parse_binary_op(std::string op)
{
	if (_nums.size() == 1)
		throw LOG("Error: not enough operands for the given operators");

	double num2 = _nums.top();
	_nums.pop();
	double num1 = _nums.top();
	_nums.pop();

	if (op == "^")
	{
		if (num1 == 0 && num2 == 0)
			throw "Indeterminate: 0^0";
		else if (num1 < 0 && num2 < 1 && (int)pow(num2, -1) % 2 == 0)
			throw "Imaginary: even root of a negative";
		_nums.push(pow(num1, num2));
	}
	else if (op == "*")
		_nums.push(num1 * num2);
	else if (op == "/")
	{
		if (num2 == 0)
		{
			if (num1 == 0)
				throw "Indeterminate: 0/0";
			throw "Infinity: n/0";
		}
		_nums.push(num1 / num2);
	}
	else if (op == "+")
		_nums.push(num1 + num2);
	else if (op == "subtract")
		_nums.push(num1 - num2);
	else if (op == "%")
	{
		if (num2 == 0)
			throw "Undefined: n%0";
		_nums.push(fmod(num1, num2));
	}
	else if (op == "==")
		_nums.push(num1 == num2);
	else if (op == "!=")
		_nums.push(num1 != num2);
	else if (op == ">=")
		_nums.push(num1 >= num2);
	else if (op == "<=")
		_nums.push(num1 <= num2);
	else if (op == ">")
		_nums.push(num1 > num2);
	else if (op == "<")
		_nums.push(num1 < num2);
	else
		throw LOG("Undefined operator: " + op);
}

template<class T>
void Calc::_set_symbol(std::map<std::string, T>& hash_table, std::string new_name, T new_symbol)
{
	// erase any existing symbol with the given name
	_vars.erase(new_name);
	_macros.erase(new_name);
	_funcs.erase(new_name);
	
	hash_table.emplace(new_name, new_symbol);
}

bool Calc::_get_symbol_value(std::string& input, int alpha_pos, int alpha_size)
{
	/*
		This function finds the name of one defined symbol within a string of alpha characters
		in the input string, and replaces the name with its value. There may be multiple symbols
		named in the alpha string with no spaces or anything else between them. Precedence is
		given to symbols with longer names, and to symbols further to the left of the string.
		All functions and macros must be immediately followed by an opening parenthesis.
	*/

	// for each substring size of the alpha string
	for (int size = alpha_size; size > 0; size--)
	{
		// for each substring position of the alpha string
		for (int pos = alpha_pos; pos + size <= alpha_pos + alpha_size; pos++)
		{
			if (_find_variable(input, pos, size)
				|| _find_macro(input, pos, size)
				|| _find_function(input, pos, size))
				return true;
		}
	}

	// the character(s) are undefined
	return false;
}

bool Calc::_find_variable(std::string& input, int pos, int size)
{
	std::string name = input.substr(pos, size);

	std::map<std::string, double>::iterator it = _vars.find(name);
	if (it == _vars.end())
		return false;
	else
	{
		// replace the variable name with its value
		input.erase(pos, size);
		std::stringstream ss;
		ss.setf(std::ios::fixed);
		ss.precision(_precision);
		ss << " " << it->second << " ";
		input.insert(pos, ss.str());
		return true;
	}
}

bool Calc::_find_macro(std::string& input, int pos, int size)
{
	std::string name = input.substr(pos, size);

	std::map<std::string, Macro>::iterator it = _macros.find(name);
	if (it == _macros.end())
		return false;
	else
	{
		input.erase(pos, size); // erase macro name
		std::vector<std::string> args = _parse_args(input, pos);

		if (it->first == "help")
		{
			if (args.size() && args[0] != "")
				throw _help_with_one_symbol(args[0]);
			throw _help_with_all_symbols();
		}
		if (it->first == "setprecision")
		{
			if (args.size() == 1)
			{
				_set_precision(stold(args[0]));
				throw "";
			}
			else
				throw LOG("Function setprecision requires one argument");
		}

		int param_count = it->second._get_param_vect().size();
		if (args.size() != param_count)
		{
			std::string message = "Error: expected " + std::to_string(param_count) + " argument";
			if (param_count != 1)
				message += "s";
			message += " for function " + it->first;
			throw LOG(message);
		}

		_eval_args(args);
		input.insert(pos, _call_macro(it, args));
		return true;
	}
}

std::string Calc::_call_macro(std::map<std::string, Macro>::iterator it, std::vector<std::string> args)
{
	// get the macro's formula and parameters
	std::string formula = it->second._get_formula();
	std::vector<std::string> params = it->second._get_param_vect();

	// create a new calculator that saves the macro's arguments as variables named by the parameters
	Calc c(this, params, args);

	// evaluate the macro
	std::string result = c._evaluate(formula);
	_rethrow_any_errors(result);

	result.insert(0, " (");
	result.append(") ");
	return result;
}

// only for calling macros
Calc::Calc(Calc* other, std::vector<std::string> params, std::vector<std::string> args)
{
	_final_precision = other->_final_precision + 5;
	_precision = other->_precision + 5;
	_vars = other->_vars;
	_macros = other->_macros;
	_funcs = other->_funcs;

	// create variables for each macro argument
	for (int i = 0; i < args.size(); i++)
		_set_symbol<double>(_vars, params[i], stold(_evaluate(args[i])));
}

bool Calc::_find_function(std::string& input, int pos, int size)
{
	std::string name = input.substr(pos, size);

	std::map<std::string, std::any>::iterator it = _funcs.find(name);
	if (it == _funcs.end())
		return false;
	else
	{
		input.erase(pos, size); // erase function name
		std::vector<std::string> args = _parse_args(input, pos);
		_eval_args(args);
		std::string result = _call_any_function(it->second, name, args);
		input.insert(pos, result); // insert function result
		return true;
	}
}

std::string Calc::_call_any_function(std::any func, std::string function_name, std::vector<std::string> args)
{
	std::string result = "";

	try
	{
		if (func.type().name() == typeid(long double(*)(long double)).name())
		{
			_validate_args(1, args.size(), function_name);
			result = _call(std::any_cast<long double(*)(long double)>(func), function_name, args);
		}
		else if (func.type().name() == typeid(std::string(*)(void)).name())
		{
			_validate_args(0, args.size(), function_name);
			result = _call(std::any_cast<std::string(*)(void)>(func), function_name);
		}
		else if (func.type().name() == typeid(void(*)(int, int, int)).name())
		{
			_validate_args(3, args.size(), function_name);
			_call(std::any_cast<void(*)(int, int, int)>(func), args);
		}
		else if (func.type().name() == typeid(void(*)(double, double, double)).name())
		{
			_validate_args(3, args.size(), function_name);
			_call(std::any_cast<void(*)(double, double, double)>(func), args);
		}
		else
			throw LOG("Code error: The type of function " + function_name + " is not yet supported.");
	}
	catch (const std::bad_any_cast& error)
	{
		throw LOG(error.what());
	}

	return result;
}

std::string Calc::_help_with_vars_and_macros()
{
	std::string message = "";

	std::map<std::string, double>::iterator it;
	for (it = _vars.begin(); it != _vars.end(); it++)
	{
		std::stringstream ss;
		ss.setf(std::ios::fixed);
		ss.precision(_final_precision);
		ss << it->second;
		std::string num = ss.str();

		format_global_output(num, _final_precision);
		message += "\n " + it->first + " = " + num;
	}

	std::map<std::string, Macro>::iterator it2;
	for (it2 = _macros.begin(); it2 != _macros.end(); it2++)
		message += "\n " + it2->first + "(" + it2->second._get_param_str() + ")" + " = " + it2->second._get_formula();

	return message;
}

// throw info about all symbols
std::string Calc::_help_with_all_symbols()
{
	std::string message = _help_with_vars_and_macros();
	message += "\n";

	std::map<std::string, std::any>::iterator it;
	int i = 0;
	for (it = _funcs.begin(); it != _funcs.end(); it++, i++)
	{
		if (i % 10 == 0)
			message += "\n ";
		message += it->first + ", ";
	}

	throw message;
}

// throw info about one symbol
std::string Calc::_help_with_one_symbol(std::string name)
{
	std::string message = "";

	std::map<std::string, double>::iterator it = _vars.find(name);
	if (it != _vars.end())
	{
		std::stringstream ss;
		ss.setf(std::ios::fixed);
		ss.precision(_final_precision);
		ss << it->second;
		std::string num = ss.str();

		format_global_output(num, _final_precision);
		message += "Variable " + it->first + " = " + num;
		throw message;
	}

	std::map<std::string, Macro>::iterator it2 = _macros.find(name);
	if (it2 != _macros.end())
	{
		message += "Function " + it2->first + "(" + it2->second._get_param_str()
			+ ")" + " = " + it2->second._get_formula();
		throw message;
	}

	std::map<std::string, std::any>::iterator it3 = _funcs.find(name);
	if (it3 != _funcs.end())
		throw "C++ Function";

	throw LOG(name + " is undefined");
}

std::string Calc::_call(long double(*func_ptr)(long double), std::string func_name, std::vector<std::string> args)
{
	std::stringstream ss;
	ss << func_ptr(stold(args[0]));
	ss.setf(std::ios::fixed);
	ss.precision(_precision);

	std::string result = ss.str();
	_check_for_scientific_notation(func_name, result);
	_format_output(result);
	return result;
}

std::string Calc::_call(std::string(*func_ptr)(), std::string func_name)
{
	std::string result = func_ptr();
	_check_for_scientific_notation(func_name, result);
	_format_output(result);
	return result;
}

void Calc::_call(void(*func_ptr)(int, int, int), std::vector<std::string> args)
{
	func_ptr(stoi(args[0]), stoi(args[1]), stoi(args[2]));
}

void Calc::_call(void(*func_ptr)(double, double, double), std::vector<std::string> args)
{
	func_ptr(stod(args[0]), stod(args[1]), stod(args[2]));
}

std::vector<std::string> Calc::_parse_args(std::string& input, int pos)
{
	if (input[pos] != '(')
		throw LOG("Error: expected '(' after function name");

	std::string arg_str = _find_args(input, pos);
	return _split_args(arg_str);
}

// get the substring of arguments
std::string Calc::_find_args(std::string& input, int pos)
{
	int parentheses = 1,
		size = 0;
	for (int i = pos + 1; i < input.size() && parentheses > 0; i++)
	{
		if (input[i] == '(')
			parentheses++;
		else if (input[i] == ')')
			parentheses--;
		if (parentheses)
			size++;
	}

	std::string arg_str = input.substr(pos + 1, size - pos);
	input.erase(pos, size - pos + 1);
	if (!parentheses)
		input.erase(pos, 1);

	return arg_str;
}

// split each argument into its own string
std::vector<std::string> Calc::_split_args(std::string arg_str)
{
	std::vector<std::string> args;
	for (int i = 0; i < arg_str.size(); i++)
	{
		if (arg_str[i] == ',')
		{
			args.push_back(arg_str.substr(0, i));
			arg_str.erase(0, i + 1);
		}
	}

	args.push_back(arg_str);
	return args;
}

// throws an error if the wrong number of arguments is given
void Calc::_validate_args(int expected_arg_count, int actual_arg_count, std::string function_name)
{
	if (expected_arg_count != actual_arg_count)
	{
		std::string message = "Error: expected " + std::to_string(expected_arg_count) + " argument";
		if (expected_arg_count != 1)
			message += "s";
		message += " for function " + function_name;
		throw LOG(message);
	}
}

void Calc::_eval_args(std::vector<std::string>& args)
{
	// evaluate each argument
	for (int i = 0; i < args.size(); i++)
	{
		Calc calc(this); // the new calculator MUST have access to any symbols created by the user
		args[i] = calc(args[i]);
		_rethrow_any_errors(args[i]);
	}
}

// This function should be called after the operator() function call of any calculator besides the one in main()
void Calc::_rethrow_any_errors(std::string str)
{
	if (str == "")
		throw LOG("Invalid syntax");
	for (int i = 0; i < str.size(); i++)
	{
		if (is_alpha(str[i]))
			throw LOG(str);
	}
}

// needs the result of calculations
void Calc::_format_output(std::string result)
{
	if (result == "-nan(ind)" || result == "nan")
		throw "Imaginary";

	result.insert(0, "(");
	result.insert(result.size() - 1, ")");
}

// TODO: delete this function after implementing support for scientific notation
void Calc::_check_for_scientific_notation(std::string function_name, std::string& result)
{
	// If the result of a sine call is in scientific notation with
	// a negative exponent, set the result to zero.
	for (int i = 0; i < result.size(); i++)
	{
		if (result[i] == 'e')
		{
			if (function_name == "sin" && i < result.size() - 1 && result[i + 1] == '-')
				result = "0";
			else
				throw LOG("Error: program not yet equipped for scientific notation");
		}
	}
}
