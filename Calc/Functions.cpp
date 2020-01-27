#include "Functions.h"

std::string randomNumber()
{
	srand((unsigned)time(0));

	std::string result = "0.";
	for (int i = 0; i < 10; i++)
	{
		int r = rand() % 10;
		result += std::to_string(r);
	}

	return result;
}

void quadraticFormula(int a, int b, int c)
{
	if (pow(b, 2) < 4 * a * c)
		throw "Imaginary";
	long double n = sqrt(pow(b, 2) - 4 * a * c);
	std::string result = "";
	result += std::to_string((-b - n) / (2 * a));
	result += " or ";
	result += std::to_string((-b + n) / (2 * a));
	throw result;
}

long double absValue(long double x)
{
	return abs(x);
}
