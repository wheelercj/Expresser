#pragma once

#include "Symbol.h"
#include <list>
#include <ctime>
#include <sstream>

// Variable and function names must not contain numbers

class Symbols
{
private:
	std::string help();
	std::string random();

public:
	const std::list<Variable> vars =
	{ // name, value
		{ "ans", 0 },
		{ "phi", 1.618033988749894848204586834365638117720309179805762862135 },
		{ "pi", 3.141592653589793238462643383279502884197169399375105820974 },
		{ "e", 2.718281828459045235360287471352662497757247093699959574966 },
		{ "g", 9.80665 }
	};

	const std::list<StrFunction> strFuncs =
	{ // name, parameters, string-based function
		{ "help", { "" }, help() },
		{ "rand", { "" }, random() },

		{ "csc", { "x" }, "1/sin(x)" },
		{ "sec", { "x" }, "1/cos(x)" },
		{ "cot", { "x" }, "1/tan(x)" },
		{ "acsc", { "x" }, "1/asin(x)" },
		{ "asec", { "x" }, "1/acos(x)" },
		{ "acot", { "x" }, "1/atan(x)" },
		{ "acsch", { "x" }, "1/asinh(x)" },
		{ "asech", { "x" }, "1/acosh(x)" },
		{ "acoth", { "x" }, "1/atanh(x)" },
	};

	const std::list<CppFunction> cppFuncs =
	{ // name, function pointer
		{ "sqrt", &sqrt },
		{ "cbrt", &cbrt },
		{ "abs", &abs },
		{ "ln", &log }, // TODO: implement other log functions
		{ "round", &round },
		{ "ceil", &ceil },
		{ "floor", &floor },
		{ "erf", &erf }, // the error function
		{ "erfc", &erfc }, // the complementary error function
		{ "tgamma", &tgamma }, // the gamma function
		{ "lgamma", &lgamma }, // the log-gamma function

		{ "sin", &sin }, // TODO: implement functions such as sin^2(x)
		{ "cos", &cos },
		{ "tan", &tan },
		{ "asin", &asin },
		{ "acos", &acos },
		{ "atan", &atan },
		{ "sinh", &sinh },
		{ "cosh", &cosh },
		{ "tanh", &tanh },
		{ "asinh", &asinh },
		{ "acosh", &acosh },
		{ "atanh", &atanh }
	};
};
