#pragma once

#include "Functions.h"
#include "Macro.h"
#include <cmath>
#include <map>
#include <sstream>
#include <string>
#include <any> // requires C++17

// Symbol names must contain only alpha characters and/or underscores

const std::map<std::string, double> default_vars =
{
	{ "ans", 0 },
	{ "phi", 1.618033988749894848204586834365638117720309179805762862135 },
	{ "pi", 3.141592653589793238462643383279502884197169399375105820974 },
	{ "e", 2.718281828459045235360287471352662497757247093699959574966 },
	{ "g", 9.80665 }
};

const std::map<std::string, Macro> default_macros =
{ //{ "name", {{ "parameters" }, "formula" }},
	{ "pow", {{ "x", "y" }, "x^y" }},
	{ "exp", {{ "x" }, "e^x" }},
	{ "log", {{ "x" }, "ln(x)/ln(10)" }},
	{ "lg", {{ "x" }, "ln(x)/ln(2)" }},
	{ "logb", {{ "base", "x" }, "ln(x)/ln(base)" }},

	{ "csc", {{ "radians" }, "1/sin(radians)" }},
	{ "sec", {{ "radians" }, "1/cos(radians)" }},
	{ "cot", {{ "radians" }, "1/tan(radians)" }},
	{ "acsc", {{ "radians" }, "asin(1/radians)" }},
	{ "asec", {{ "radians" }, "acos(1/radians)" }},
	{ "acot", {{ "radians" }, "atan(1/radians)" }},
	{ "csch", {{ "radians" }, "1/sinh(radians)" }},
	{ "sech", {{ "radians" }, "1/cosh(radians)" }},
	{ "coth", {{ "radians" }, "1/tanh(radians)" }},
	{ "acsch", {{ "radians" }, "asinh(1/radians)" }},
	{ "asech", {{ "radians" }, "acosh(1/radians)" }},
	{ "acoth", {{ "radians" }, "atanh(1/radians)" }},
	
	{ "cylinder_volume", {{ "r", "h"}, "pi*r^2*h" }},
	{ "sphere_volume", {{ "r" }, "(4/3)pi*r^3" }},
	{ "cone_volume", {{ "r", "h" }, "(h/3)pi*r^2" }},
	{ "pyramid_volume", {{ "Base_area", "h" }, "Base_area*h/3" }},

	{ "simple_interest", {{ "P", "r", "t" }, "Prt" }}, // principal amount, rate, time
	{ "compound_interest", {{ "P", "r", "t", "n" }, "P(1+r/n)^(nt)" }}, // principal amount, rate, time, number of compounds
	{ "present_value", {{ "C", "r", "n" }, "C/(1+r)^n" }}, // cash flow at period 1, rate of return, number of periods
	{ "future_value", {{ "C", "r", "n" }, "C(1+r)^n" }}, // cash flow at period 0, rate of return, number of periods

	// functions further defined in the Calc class
	{ "help", {{ "" }, "Display info about defined variables and functions" }},
	{ "setprecision", {{ "int" }, "Adjust the number of digits displayed in answers" }}
};

const std::map<std::string, std::any> default_funcs =
{ //{ "function_name", function_pointer },
	{ "sqrt", sqrt_ },		// square root
	{ "cbrt", cbrt_ },		// cube root
	{ "abs", abs_ },		// absolute value
	{ "ln", ln_ },			// log base e
	{ "round", round_ },
	{ "ceil", ceil_ },		// ceiling (rounds up)
	{ "floor", floor_ },	// floor (rounds down)
	{ "erf", erf_ },		// error
	{ "erfc", erfc_ },		// complementary error
	{ "tgamma", tgamma_ },	// gamma
	{ "lgamma", lgamma_ },	// log-gamma

	{ "sin", sin_ },		// sine
	{ "cos", cos_ },		// cosine
	{ "tan", tan_ },		// tangent
	{ "asin", asin_ },		// arcsine
	{ "acos", acos_ },		// arccosine
	{ "atan", atan_ },		// arctangent
	{ "sinh", sinh_ },		// hyperbolic sine
	{ "cosh", cosh_ },		// hyperbolic cosine
	{ "tanh", tanh_ },		// hyperbolic tangent
	{ "asinh", asinh_ },	// hyperbolic arcsine
	{ "acosh", acosh_ },	// hyperbolic arccosine
	{ "atanh", atanh_ },	// hyperbolic arctangent

	{ "rand", random_number }, // generate a random number
	{ "quad", quadratic_formula }
};
