#include <iostream>
#include "Calc.h"

int main()
{
	std::string input;
	Calc calc;
	CLEAR_LOG();

	while (true)
	{
		std::cout << "\n\n>> ";
		std::getline(std::cin, input);

		if (input == "exit" || input == "quit" || input == "EXIT" || input == "QUIT")
			return 0;

		std::string result = calc(input);
		if (result.size())
			std::cout << " = ";
		std:: cout << result;
	}
}
