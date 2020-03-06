#pragma once

#include <string>
#include <ctime>

inline long double sqrt_(long double x) { return sqrt(x); }
inline long double cbrt_(long double x) { return cbrt(x); }
inline long double abs_(long double x) { return abs(x); }
inline long double ln_(long double x) { return log(x); }
inline long double round_(long double x) { return round(x); }
inline long double ceil_(long double x) { return ceil(x); }
inline long double floor_(long double x) { return floor(x); }
inline long double erf_(long double x) { return erf(x); }
inline long double erfc_(long double x) { return erfc(x); }
inline long double tgamma_(long double x) { return tgamma(x); }
inline long double lgamma_(long double x) { return lgamma(x); }
inline long double sin_(long double x) { return sin(x); }
inline long double cos_(long double x) { return cos(x); }
inline long double tan_(long double x) { return tan(x); }
inline long double asin_(long double x) { return asin(x); }
inline long double acos_(long double x) { return acos(x); }
inline long double atan_(long double x) { return atan(x); }
inline long double sinh_(long double x) { return sinh(x); }
inline long double cosh_(long double x) { return cosh(x); }
inline long double tanh_(long double x) { return tanh(x); }
inline long double asinh_(long double x) { return asinh(x); }
inline long double acosh_(long double x) { return acosh(x); }
inline long double atanh_(long double x) { return atanh(x); }

std::string random_number();
void quadratic_formula(int a, int b, int c);
