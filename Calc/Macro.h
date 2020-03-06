#pragma once

#include "Common.h"
#include <vector>

/*
	A Macro object is not an entire macro. The macro's name is stored
	as the key in a	hash table, so the function that calls macros
	must also not be part of the Macro class.
*/

class Macro
{
private:
	std::vector<std::string> _params;
	std::string _formula;
public:
	Macro(std::vector<std::string> new_params, std::string new_formula);
	std::string _get_formula();
	std::string _get_param_str();
	std::vector<std::string> _get_param_vect();
};

int find_macro_name_size(std::string& input, int eq_pos); // returns zero if the symbol is a variable
