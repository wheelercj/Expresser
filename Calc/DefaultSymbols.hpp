#pragma once

#include "Symbol.h"
#include <list>
#include <ctime>
#include <sstream>
#include <cmath>

// Variable and function names must contain only alpha characters and/or underscores

namespace Symbols
{
	const std::list<Variable> varList =
	{ // name, value
		{ "ans", 0 },
		{ "phi", 1.618033988749894848204586834365638117720309179805762862135 },
		{ "pi", 3.141592653589793238462643383279502884197169399375105820974 },
		{ "e", 2.718281828459045235360287471352662497757247093699959574966 },
		{ "g", 9.80665 }
	};

	const std::list<StrFunction> strFuncList =
	{ // name, parameters, string-based function
		{ "csc", { "x" }, "1/sin(x)" },
		{ "sec", { "x" }, "1/cos(x)" },
		{ "cot", { "x" }, "1/tan(x)" },
		{ "acsc", { "x" }, "1/asin(x)" },
		{ "asec", { "x" }, "1/acos(x)" },
		{ "acot", { "x" }, "1/atan(x)" },
		{ "acsch", { "x" }, "1/asinh(x)" },
		{ "asech", { "x" }, "1/acosh(x)" },
		{ "acoth", { "x" }, "1/atanh(x)" },
	  
		{ "cylinder_volume", { "r", "h"}, "pi*r^2*h" },
		{ "sphere_volume", { "r" }, "(4/3)pi*r^3" },
		{ "cone_volume", { "r", "h" }, "(h/3)pi*r^2" },
		{ "pyramid_volume", { "base_area", "h" }, "base_area*h/3" },

		 // functions further defined in the Calc class
		{ "help", { "" }, "Display info about defined variables and functions" },
		{ "setprecision", { "" }, "Adjust the number of fractional digits displayed in answers" },
		{ "rand", { "" }, "Generate a random number" }
	};

	const std::list<CppFunction> cppFuncList =
	{ // name, function pointer
		{ "sqrt", &sqrt },
		{ "cbrt", &cbrt },
		{ "abs", &abs },
		{ "log", &log }, // TODO: implement other log functions
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

		// TODO: create a function that can display an answer as a fraction instead of a float
	};
}
