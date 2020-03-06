#include "Macro.h"

Macro::Macro(std::vector<std::string> new_params, std::string new_formula)
{
	_params = new_params;
	_formula = new_formula;
}

std::string Macro::_get_formula()
{
	return _formula;
}

std::string Macro::_get_param_str()
{
	std::string param_str = "";
	for (int i = 0; i < _params.size(); i++)
	{
		param_str += _params[i];
		if (i < _params.size() - 1)
			param_str += ",";
	}
	return param_str;
}

std::vector<std::string> Macro::_get_param_vect()
{
	return _params;
}

// returns zero if the symbol is a variable
int find_macro_name_size(std::string& input, int eq_pos)
{
	bool alpha_found = false;
	bool space_after_alpha = false;

	for (int i = 0; i < eq_pos; i++)
	{
		if (is_alpha(input[i]))
		{
			alpha_found = true;
			if (space_after_alpha)
				throw LOG("Invalid space before assignment operator");
		}
		else if (input[i] == ' ')
		{
			if (alpha_found)
				space_after_alpha = true;
		}
		else if (input[i] == '(')
		{
			if (space_after_alpha)
				throw LOG("Invalid space before parameter(s)");
			if (!alpha_found)
				throw LOG("Missing symbol name before assignment operator");

			return i;
			break;
		}
		else
		{
			std::string message = "Invalid character before assignment operator: ";
			message += input[i];
			throw LOG(message);
		}
	}

	if (!alpha_found)
		throw LOG("Missing symbol name before assignment operator");

	return 0;
}
