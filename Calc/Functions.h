#pragma once

#include "Func.h"
#include <map>
#include <string>
#include <any> // requires C++17
#include <ctime>

std::string randomNumber();
void quadraticFormula(int a, int b, int c);
long double absValue(long double x);

class Functions
{
private:
	std::map<std::string, std::any> funcs =
	{// { "name", Func("params", pointer) },
		{ "sqrt", Func("x", sqrt) },
		{ "cbrt", Func("x", cbrt) },
		{ "abs", Func("x", absValue) },
		{ "log", Func("x", log) }, // base e
		{ "round", Func("x", round) },
		{ "ceil", Func("x", ceil) },
		{ "floor", Func("x", floor) },
		{ "erf", Func("x", erf) }, // the error function
		{ "erfc", Func("x", erfc) }, // the complementary error function
		{ "tgamma", Func("x", tgamma) }, // the gamma function
		{ "lgamma", Func("x", lgamma) }, // the log-gamma function

		{ "sin", Func("x", sin) },
		{ "cos", Func("x", cos) },
		{ "tan", Func("x", tan) },
		{ "asin", Func("x", asin) },
		{ "acos", Func("x", acos) },
		{ "atan", Func("x", atan) },
		{ "sinh", Func("x", sinh) },
		{ "cosh", Func("x", cosh) },
		{ "tanh", Func("x", tanh) },
		{ "asinh", Func("x", asinh) },
		{ "acosh", Func("x", acosh) },
		{ "atanh", Func("x", atanh) },
		{ "rand", Func("", randomNumber) },
		{ "quad", Func("a,b,c", quadraticFormula) }
	};
};
