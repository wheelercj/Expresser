#pragma once

#include "Functions.h"
#include "Macro.h"
#include <cmath>
#include <map>
#include <sstream>
#include <string>
#include <any> // requires C++17

// Symbol names must contain only alpha characters and/or underscores

const std::map<std::string, double> defaultVars =
{
	{ "ans", 0 },
	{ "phi", 1.618033988749894848204586834365638117720309179805762862135 },
	{ "pi", 3.141592653589793238462643383279502884197169399375105820974 },
	{ "e", 2.718281828459045235360287471352662497757247093699959574966 },
	{ "g", 9.80665 }
};

const std::map<std::string, Macro> defaultMacros =
{ //{ "name", {{ "parameters" }, "formula" }},
	{ "pow", {{ "x", "y" }, "x^y" }},
	{ "exp", {{ "x" }, "e^x" }},
	{ "log", {{ "x" }, "ln(x)/ln(10)" }},
	{ "lg", {{ "x" }, "ln(x)/ln(2)" }},
	{ "logb", {{ "b", "x" }, "ln(x)/ln(b)" }},

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

	{ "simple_interest", {{ "P", "r", "t" }, "Prt" }}, // principal amount, rate, time
	{ "compound_interest", {{ "P", "r", "t", "n" }, "P(1+r/n)^(nt)" }}, // principal amount, rate, time, number of compounds
	{ "present_value", {{ "C", "r", "n" }, "C/(1+r)^n" }}, // cash flow at period 1, rate of return, number of periods
	{ "future_value", {{ "C", "r", "n" }, "C(1+r)^n" }}, // cash flow at period 0, rate of return, number of periods

	// functions further defined in the Calc class
	{ "help", {{ "" }, "Display info about defined variables and functions" }},
	{ "setprecision", {{ "int" }, "Adjust the number of digits displayed in answers" }}
};

const std::map<std::string, std::any> defaultFuncs =
{
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

	{ "rand", randomNumber }, // generate a random number
	{ "quad", quadraticFormula }
};
