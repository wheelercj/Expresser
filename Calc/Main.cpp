#include <iostream>
#include "Calc.h"

int main()
{
	std::string input;
	Calc c;

	while (true)
	{
		std::cout << "\n\n>> ";
		std::getline(std::cin, input);

		if (input == "exit" || input == "quit" || input == "EXIT" || input == "QUIT")
			return 0;

		std::cout << c.calc(input);
	}
}
