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

		std::string result = c.calc(input);
		if (result.size())
			std::cout << " = ";
		std:: cout << result;
	}
}
