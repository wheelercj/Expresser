#include "Functions.h"

std::string random_number()
{
	srand((unsigned)time(0)); // having this here causes random number generation to be limited to one random number per second

	std::string result = "0.";
	for (int i = 0; i < 10; i++)
	{
		int r = rand() % 10;
		result += std::to_string(r);
	}  

	return result;
}

void quadratic_formula(double a, double b, double c)
{
	long double radicand = pow(b, 2) - 4 * a * c;
	if (radicand < 0)
		throw "Imaginary";

	radicand = sqrt(radicand);
	std::string ans1 = std::to_string((-b - radicand) / (2 * a));
	std::string ans2 = std::to_string((-b + radicand) / (2 * a));

	format_output(ans1, 5);
	format_output(ans2, 5);
	throw ans1 + " or " + ans2;
}
