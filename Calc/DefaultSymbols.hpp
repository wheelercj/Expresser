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
		{ "help", {{ "optional_name" }, "Display info about defined variables and functions" }},
		{ "setprecision", {{ "int" }, "Adjust the number of digits displayed in answers" }},
		{ "rand", {{ "_" }, "Generate a random number" }},
		{ "delete", {{ "name" }, "Delete a variable or function" }}
	};

	const std::unordered_map<std::string, Function> defaultFuncs =
	{ // name, function pointer
		{ "sqrt", &sqrt },
		{ "cbrt", &cbrt },
		{ "abs", &abs },
		{ "log", &log },
		{ "round", &round },
		{ "ceil", &ceil },
		{ "floor", &floor },
		{ "erf", &erf }, // the error function
		{ "erfc", &erfc }, // the complementary error function
		{ "tgamma", &tgamma }, // the gamma function
		{ "lgamma", &lgamma }, // the log-gamma function

		{ "sin", &sin },
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

		/* // TODO: create functions:
			use functions sinl, cosl, etc. instead of sin, cos, etc. for more precision
			display an answer as a fraction instead of a float
			reset all settings to defaults
			functions such as sin^2(x)
			log functions with bases other than Euler's number
		*/
	};
}
