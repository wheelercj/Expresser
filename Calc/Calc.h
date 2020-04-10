#pragma once

#include "DefaultSymbols.hpp"
#include <stack>

class Calc
{
public:
	Calc();
	~Calc();
	Calc(int new_precision); // for loading only the default symbols
	Calc(Calc*);
	std::string operator()(std::string input);
	std::string _evaluate(std::string input);
	void _reset_symbols();
	void _set_precision(int num);
	int _get_precision();
private:
	int _final_precision = 5;
	int _precision = _final_precision + 5;

	void _detect_assignment(std::string& input);
	void _parse_symbol_definition(std::string& input, int eq_pos, int name_size);
	std::string _parse_input(std::string str);

	std::stack<double> _nums;
	std::stack<std::string> _ops;
	void _parse_num(std::string& input, int& pos);
	void _parse_alpha(std::string& input, int& pos);
	void _parse_op(std::string& input, int& pos);
	enum _types { NONE, OP, NUM };
	int _last_type_pushed = NONE;
	void _push_op_onto_empty_stack(int& pos, std::string new_op, int op_size);
	void _push_op_onto_nonempty_stack(std::string input, int& pos, std::string new_op, int op_size);
	void _push_open_parenthesis(std::string input, int& pos);
	void _push_minus(int& pos);
	void _pop_and_evaluate_ops_and_nums();
	bool _parse_unary_op();
	void _parse_binary_op(std::string op);

	std::map<std::string, double> _vars = default_vars;
	std::map<std::string, Macro> _macros = default_macros;
	std::map<std::string, std::any> _funcs = default_funcs;
	std::stack<std::string> _vars_being_defined;
	template<class T> void _set_symbol(std::map<std::string, T>& hash_table, std::string new_name, T new_symbol);
	bool _get_symbol_value(std::string& input, int alpha_pos, int alpha_size);
	bool _find_variable(std::string& input, int pos, int size);
	bool _find_macro(std::string& input, int pos, int size);
	std::string _call_macro(std::map<std::string, Macro>::iterator it, std::vector<std::string> args);
	Calc(Calc* other, std::vector<std::string> params, std::vector<std::string> args); // only for calling macros
	bool _find_function(std::string& input, int pos, int size);
	void _resolve_function_type(std::any func, std::string& input, int pos, int size);
	
	std::string _help_with_vars_and_macros();
	std::string _help_with_all_symbols();
	std::string _help_with_one_symbol(std::string);

	// function adapters
	void _call(long double(*func_ptr)(long double), std::string& input, int pos, int size);
	void _call(std::string(*func_ptr)(), std::string& input, int pos, int size);
	void _call(void(*func_ptr)(int, int, int), std::string& input, int pos, int size);

	// adapter library
	void _clean_input_with_no_args(std::string& input, std::string name, int arg_pos);
	std::vector<std::string> _split_arg_string(std::string& input, int arg_pos);
	template <class T, class ...Ts> std::vector<std::string> _split_args(std::string& input, int pos, int size);
	void _eval_args(std::vector<std::string>& args);
	void _rethrow_any_errors(std::string str);
	void _insert_function_result(std::string& input, int pos, int size, std::string result);
};
