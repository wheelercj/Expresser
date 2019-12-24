#include <iostream>
#include "Calc.h"

int main() // TODO: improve the precision of floating point answers (by replacing std::to_string with something else?)
{
	std::string input;
	Calc c;

	while (true)
	{
		std::cout << "\n> ";
		std::getline(std::cin, input);

		if (input == "exit" || input == "quit" || input == "EXIT" || input == "QUIT")
			return 0;

		std::cout << c.calc(input) << std::endl;
	}
}
