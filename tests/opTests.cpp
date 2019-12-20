#include "pch.h"
#include "CppUnitTest.h"
#include "../Calc/Main.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace opTests
{
	void equal(std::string str1, std::string str2)
	{
		Assert::AreEqual(str1, calc(str2));
	}

	TEST_CLASS(opTests) // TODO: figure out how to know whether these tests cover all possibilities
	{					  // TODO: figure out how to find the range of the calculator
	public:

		TEST_METHOD(Syntax)
		{
			equal("3", "    1      +         2  ");
			equal("8.15", "8+.15");
			equal("8.3", "0.30 + 8");
			equal("Invalid syntax", ".");
			equal("Invalid syntax", ".+3");
			equal("Invalid syntax", "3+.");
			equal("Invalid syntax", "192.168.0.1");
			equal("Invalid syntax", "+/");
			equal(" ", " ");
			equal(" ", "");
			equal("Undefined character", "a");
			equal("Undefined character", "11+12g");
			equal("Undefined character", "jajvoaierjal;ndvoiasejrlaenafl;jo;ijwer");
			equal("Undefined character", "$5");
		}
		TEST_METHOD(Add)
		{
			equal("-100", "-25+-75");
			equal("-2", "-1+-1");
			equal("0", "0 + 0");
			equal("1", " 1 + 0 ");
			equal("2", "1+1");
			equal("4", "0+4   ");
			equal("5", "4+1+0");
			equal("5.859874", "3.1415926 + 2.7182818");
			equal("6", "8+-2");
			equal("7", "3+4");
			equal("8", "2 + 6");
			equal("9.15", "9 + 0.15");
			equal("10", "2+3 + 1 + 4");
			equal("11", "1+1+1+1+1+1+1+1+1+1+1");
			equal("12", "-365+377");
			equal("39222222", "9384729+29837493");
			equal("Invalid syntax", "6++7");
			equal("Invalid syntax", "4+2+");
			equal("Invalid syntax", "+4+2");
		}
		TEST_METHOD(Subtract)
		{
			equal("-3", "-1-2");
			equal("0", "0-0");
			equal("0", "1-1");
			equal("0", "1---1");
			equal("0.423311", "3.1415926-2.7182818");
			equal("4", "6 - 2");
			equal("5", " 4--1");
			equal("5", "--2+3");
			equal("6", "-5--11");
			equal("7", "------------7");
		}
		TEST_METHOD(Multiply)
		{
			equal("Invalid syntax", "*");
			equal("-24", "-2*3*4");
			equal("-18", "9* -2");
			equal("0", "0*0");
			equal("0", "1*0");
			equal("0", "4*3*2*1*0*1*2*3*4");
			equal("1", "1*1");
			equal("4", "-2*-2");
			equal("6", "2*3");
			equal("8.539734", "3.1415926 * 2.7182818");
			Assert::AreNotEqual((std::string)"pie", calc("3.1415926 * 2.7182818"));
			equal("100", "10*10");
			equal("576", "4*2*9*4*2");
		}
		TEST_METHOD(Divide)
		{
			equal("Indeterminate", "0/0");
			equal("Infinity", "3/0");
			equal("-0.625", "5/-8");
			equal("-0.5", "-1/2");
			equal("0", "0/4");
			equal("0.5", "1/2");
			equal("1", "3/3");
			equal("1.155727", "3.1415926 / 2.7182818");
			equal("2", "-4/-2");
			equal("5", "10 / 2");
			equal("12", "12/1");
		}
		TEST_METHOD(Exponent)
		{
			equal("Indeterminate", "0^0");
			equal("Imaginary", "(-2)^(1/2)");
			equal("-8", "-2^3");
			equal("-8", "(-2)^3");
			equal("-4", "-2^2");
			equal("-1.414214", "-2^(1/2)");
			equal("0.008", "5^-3");
			equal("0.16", "(5/2)^-2");
			equal("0.4", "(5/2)^-1");
			equal("1", "25^0");
			equal("1", "1^2^3");
			equal("1.66559", "30^0.15");
			equal("3", "9^(1/2)");
			equal("5", "5 ^ 1");
			equal("8.320335", "576^(1/3)");
			equal("9", "3^2");
			equal("22.459158", "3.141592654^2.718281828");
			equal("32", "4^3/2");
			equal("62", "4^3-2");
			equal("66", "4^3+2");
			equal("128", "4^3*2");
			equal("262144", "4^3^2");
			Assert::AreNotEqual(std::to_string(4096), calc("4^3^2"));
			equal("11112006825558016", "14^14");
			// equal("437893890380859375", "15^15"); // TODO: figure out why this fails by a small amount
		}
		TEST_METHOD(Parentheses)
		{
			equal("-18", "(-6)3");
			equal("-15", "3(-5)");
			equal("-10", "-1(10)");
			equal("-9", "(-6)-3");
			equal("1", "(((((((((1))");
			equal("2", "((2))");
			equal("3", "1+(2)");
			equal("4", "2(2");
			equal("6", "3(2)");
			equal("8", "(4)2");
			equal("8.539734", "3.1415926(2.7182818)");
			equal("10", "(10)(1)");
			equal("12", "4*(3)");
			equal("24", "(((1)2)3)4");
			equal("Invalid syntax", ")");
		}
		TEST_METHOD(Factorial)
		{
			equal("1", "1!");
			equal("1", "0!");
			equal("2", "2!");
			equal("6", "3 !");
			equal("9", "3!+3");
			equal("36", "3!^2");
			equal("120", "5!");
			equal("720", "(3!)!");
			equal("3628800", "10!");
			equal("Invalid syntax", "3!!"); // https://en.wikipedia.org/wiki/Double_factorial
			equal("Invalid syntax", "!");
			equal("Invalid syntax", "!4");
			equal("Invalid syntax", "3+!");
			equal("Undefined", "2.5!");
			equal("Complex infinity", "(-2)!");
		}
		TEST_METHOD(Modulus)
		{
			equal("Invalid syntax", "%");
			equal("Invalid syntax", "2%");
			equal("Invalid syntax", "%2");
			equal("Undefined", "0%0");
			equal("Undefined", "2%0");
			equal("0", "0%2");
			equal("0", "2%2");
			equal("2", "2%3");
			equal("1", "3%2");
			equal("1", "7%2");
			equal("2", "2%7");
			equal("2.5", "2.5%5");
			equal("0", "3%1.5");
			equal("0", "7.5%3.75");
			equal("3.75", "3.75%7.5");
			equal("-3", "-3%4");
			equal("0", "4%-2");
			equal("-2", "-2%-4");
			equal("0", "-4%-2");
			equal("1", "2+3%4");
			equal("1", "2--3%4");
			equal("1", "5-4%2");
			equal("5", "5-(4%2)");
			equal("4", "4%3+2");
			equal("1", "3%4-2");
			equal("1", "(3%4)-2");
			equal("1", "4%3%2");
			Assert::AreNotEqual((std::string)"0", calc("4%3%2"));
			equal("2", "2%3%4");
			equal("Invalid syntax", "4%%2");
			equal("Invalid syntax", "4%+2");
			equal("Invalid syntax", "4+%2");
			equal("Invalid syntax", "4-%2");
		}
		TEST_METHOD(Precedence)
		{
			equal("-382.00476", "53.28394 + 392.48 - 1.5^3(65.23 * 3.76)");
			equal("-20.064815", "-3+4*-5-6(-7/8)/-9^2--3");
			equal("-1.8", "(1-2)^3*4/5+6-7");
			equal("0.025", "(1)/(5)/(8)");
			equal("1", "1");
			equal("10", "1+(2+(3+(4)))");
			equal("16", "2^(4)");
			equal("17.5", "((4*5)(7/8))");
			equal("19.935185", "3+4*5-6(7/8)/9^2-3");
			equal("20.935185", "3 + 4 * 5 - 6 ( 7 / 8 ) / 9 ^ 2 - 2");
			equal("306.25", "((4*5)^2(7/8)^2)");
			equal("1024", "4^(3+2)");
			equal("1461.333333", "9-8+7/6*5^4(3-1)+2");
			equal("8", "2+3!");
			equal("12", "2*3!");
			equal("64", "2^3!");
			equal("0.015625", "2^-3!");
		}
		TEST_METHOD(Errors)
		{
			equal("Invalid syntax", "5-+3");
			equal("Invalid syntax", "8 -   + 1");
			equal("Invalid syntax", "*4+2");
			equal("Invalid syntax", "3*--*4");
			equal("Invalid syntax", "(3+5/(2*4)))");
		}
	};
}
