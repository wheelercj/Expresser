#pragma once

#include "Symbol.h"
#include <ctime>
#include <cmath>
#include <unordered_map>

// Symbol names must contain only alpha characters and/or underscores

namespace Symbols
{
	const std::unordered_map<std::string, double> defaultVars =
	{ // name, value
		{ "ans", 0 },
		{ "phi", 1.618033988749894848204586834365638117720309179805762862135 },
		{ "pi", 3.141592653589793238462643383279502884197169399375105820974 },
		{ "e", 2.718281828459045235360287471352662497757247093699959574966 },
		{ "g", 9.80665 }
	};

	const std::unordered_map<std::string, Macro> defaultMacros =
	{ // name, parameters, formula
		{ "csc", {{ "x" }, "1/sin(x)" }},
		{ "sec", {{ "x" }, "1/cos(x)" }},
		{ "cot", {{ "x" }, "1/tan(x)" }},
		{ "acsc", {{ "x" }, "asin(1/x)" }},
		{ "asec", {{ "x" }, "acos(1/x)" }},
		{ "acot", {{ "x" }, "atan(1/x)" }},
		{ "acsch", {{ "x" }, "asinh(1/x)" }},
		{ "asech", {{ "x" }, "acosh(1/x)" }},
		{ "acoth", {{ "x" }, "atanh(1/x)" }},
	  
		{ "cylinder_volume", {{ "r", "h"}, "pi*r^2*h" }},
		{ "sphere_volume", {{ "r" }, "(4/3)pi*r^3" }},
		{ "cone_volume", {{ "r", "h" }, "(h/3)pi*r^2" }},
		{ "pyramid_volume", {{ "base_area", "h" }, "base_area*h/3" }},

		 // functions further defined in the Calc class
		{ "help", {{ "" }, "Display info about defined variables and functions" }},
		{ "setprecision", {{ "int" }, "Adjust the number of digits displayed in answers" }},
		{ "rand", {{ "" }, "Generate a random number" }}
	};

	const std::unordered_map<std::string, Function*> defaultFuncs =
	{ // name, function pointer
		{ "sqrt", &Func<double, double>(&sqrt) },
		{ "cbrt", &Func<double, double>(&cbrt) },
		{ "abs", &Func<double, double>(&abs) },
		{ "log", &Func<double, double>(&log) },
		{ "round", &Func<double, double>(&round) },
		{ "ceil", &Func<double, double>(&ceil) },
		{ "floor", &Func<double, double>(&floor) },
		{ "erf", &Func<double, double>(&erf) }, // the error function
		{ "erfc", &Func<double, double>(&erfc) }, // the complementary error function
		{ "tgamma", &Func<double, double>(&tgamma) }, // the gamma function
		{ "lgamma", &Func<double, double>(&lgamma) }, // the log-gamma function

		{ "sin", &Func<long double, long double>(&sinl) },
		{ "cos", &Func<double, double>(&cos) },
		{ "tan", &Func<double, double>(&tan) },
		{ "asin", &Func<double, double>(&asin) },
		{ "acos", &Func<double, double>(&acos) },
		{ "atan", &Func<double, double>(&atan) },
		{ "sinh", &Func<double, double>(&sinh) },
		{ "cosh", &Func<double, double>(&cosh) },
		{ "tanh", &Func<double, double>(&tanh) },
		{ "asinh", &Func<double, double>(&asinh) },
		{ "acosh", &Func<double, double>(&acosh) },
		{ "atanh", &Func<double, double>(&atanh) },

		{ "help", &Func<std::string, std::string>(&help) },
		{ "help", &Func<std::string, void>(&help) }

		/* // TODO: create functions:
			use functions sinl, cosl, etc. instead of sin, cos, etc. for more precision
			display an answer as a fraction instead of a float
			reset all settings to defaults
			functions such as sin^2(x)
			log functions with bases other than Euler's number
		*/
	};
}
