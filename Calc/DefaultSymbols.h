#pragma once

#include "Func.h"
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
	{ "logb", {{ "b", "x" }, "log(x)/log(b)" }},

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
	{ "setprecision", {{ "int" }, "Adjust the number of digits displayed in answers" }}
};

std::map<std::string, std::any> defaultFuncs =
{// { "name", Func("params", pointer_) },
	{ "sqrt", Func("x", sqrt_) },
	{ "cbrt", Func("x", cbrt_) },
	{ "abs", Func("x", abs_) },
	{ "log", Func("x", log_) }, // base e
	{ "round", Func("x", round_) },
	{ "ceil", Func("x", ceil_) },
	{ "floor", Func("x", floor_) },
	{ "erf", Func("x", erf_) }, // the error function
	{ "erfc", Func("x", erfc_) }, // the complementary error function
	{ "tgamma", Func("x", tgamma_) }, // the gamma function
	{ "lgamma", Func("x", lgamma_) }, // the log-gamma function

	{ "sin", Func("x", sin_) },
	{ "cos", Func("x", cos_) },
	{ "tan", Func("x", tan_) },
	{ "asin", Func("x", asin_) },
	{ "acos", Func("x", acos_) },
	{ "atan", Func("x", atan_) },
	{ "sinh", Func("x", sinh_) },
	{ "cosh", Func("x", cosh_) },
	{ "tanh", Func("x", tanh_) },
	{ "asinh", Func("x", asinh_) },
	{ "acosh", Func("x", acosh_) },
	{ "atanh", Func("x", atanh_) },

	{ "rand", Func("", randomNumber) },
	{ "quad", Func("a,b,c", quadraticFormula) }
};
