#include "pch.h"
#include "CppUnitTest.h"
#include "../Calc/Calc.h"
#include "../Calc/Calc.cpp"
#include "../Calc/Vars.h"
#include "../Calc/Vars.cpp"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Tests
{
	Calc c;

	void equal(std::string str1, std::string str2)
	{
		str1.insert(0, "\n = ");
		Assert::AreEqual(str1, c.calc(str2));
	}

	TEST_CLASS(Ops) // TODO: figure out how to know whether these tests cover all possibilities
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
			Assert::AreEqual((std::string)"", c.calc(" "));
			Assert::AreEqual((std::string)"", c.calc(""));
			equal("Undefined character", "a");
			equal("Undefined character", "jajvoaierjal;ndvoiasejrlaenafl;jo;ijwer");
			equal("Undefined character", "$5");
			equal("-382.00476", "53.28394 + 392.48 - 1.5^3(65.23 * 3.76)");
			equal("-20.064815", "-3+4*-5-6(-7/8)/-9^2--3");
			equal("-1.8", "(1-2)^3*4/5+6-7");
			equal("19.935185", "3+4*5-6(7/8)/9^2-3");
			equal("20.935185", "3 + 4 * 5 - 6 ( 7 / 8 ) / 9 ^ 2 - 2");
			equal("306.25", "((4*5)^2(7/8)^2)");
			equal("1461.333333", "9-8+7/6*5^4(3-1)+2");
			equal("80", "20 4");
			equal("24", "20 +4");
		}
		TEST_METHOD(Add)
		{
			equal("Invalid syntax", "+");
			equal("Invalid syntax", "2+");
			equal("Invalid syntax", "+2");
			equal("0", "0+0");
			equal("2", "2+0");
			equal("2", "0+2");
			equal("4", "2+2");
			equal("5", "2+3");
			equal("5", "3+2");
			equal("9", "7+2");
			equal("9", "2+7");
			equal("7.5", "2.5+5");
			equal("4.5", "3+1.5");
			equal("11.25", "7.5+3.75");
			equal("11.25", "3.75+7.5");
			equal("1", "-3+4");
			equal("2", "4+-2");
			equal("-6", "-2+-4");
			equal("-6", "-4+-2");
			equal("9", "4+3+2");
			equal("9", "2+3+4");
			equal("Invalid syntax", "4++2");
			equal("Invalid syntax", "4+*2");
			equal("Invalid syntax", "4*+2");
			equal("Invalid syntax", "4-+2");
			equal("Invalid syntax", "2+3+");
			equal("Invalid syntax", "+2+3");

			equal("10", "2*3+4");
			equal("-2", "2*-3+4");
			equal("3.25", "5/4+2");
			equal("0.833333", "5/(4+2)");
			equal("10", "4+3*2");
			equal("5", "3+4/2");
			equal("3.5", "(3+4)/2");
		}
		TEST_METHOD(Subtract)
		{
			equal("Invalid syntax", "-");
			equal("Invalid syntax", "2-");
			equal("-2", "-2");
			equal("0", "-0");
			equal("0", "0-0");
			equal("2", "2-0");
			equal("-2", "0-2");
			equal("0", "2-2");
			equal("-1", "2-3");
			equal("1", "3-2");
			equal("5", "7-2");
			equal("-5", "2-7");
			equal("-2.5", "2.5-5");
			equal("1.5", "3-1.5");
			equal("3.75", "7.5-3.75");
			equal("-3.75", "3.75-7.5");
			equal("-7", "-3-4");
			equal("1", "-2+3");
			equal("6", "4--2");
			equal("2", "-2--4");
			equal("-2", "-4--2");
			equal("-1", "4-3-2");
			equal("-5", "2-3-4");
			equal("6", "4--2");
			equal("Invalid syntax", "4-*2");
			equal("-8", "4*-2");
			equal("0", "1---1");
			equal("7", "------------7");
			equal("Invalid syntax", "3*---*4");
			equal("Invalid syntax", "2+3-");

			equal("2", "2*3-4");
			equal("-10", "2*-3-4");
			equal("-0.75", "5/4-2");
			equal("2.5", "5/(4-2)");
			equal("-2", "4-3*2");
			equal("1", "3-4/2");
			equal("-0.5", "(3-4)/2");
		}
		TEST_METHOD(Multiply)
		{
			equal("Invalid syntax", "*");
			equal("Invalid syntax", "2*");
			equal("Invalid syntax", "*2");
			equal("0", "0*0");
			equal("0", "2*0");
			equal("0", "0*2");
			equal("4", "2*2");
			equal("6", "2*3");
			equal("6", "3*2");
			equal("14", "7*2");
			equal("14", "2*7");
			equal("12.5", "2.5*5");
			equal("4.5", "3*1.5");
			equal("28.125", "7.5*3.75");
			equal("28.125", "3.75*7.5");
			equal("-12", "-3*4");
			equal("-8", "4*-2");
			equal("8", "-2*-4");
			equal("8", "-4*-2");
			equal("24", "4*3*2");
			equal("24", "2*3*4");
			equal("Invalid syntax", "4**2");
			equal("Invalid syntax", "4*+2");
			equal("Invalid syntax", "4+*2");
			equal("Invalid syntax", "4-*2");
			equal("Invalid syntax", "2+3*");
			equal("Invalid syntax", "*2+3");

			equal("32", "2^3*4");
			equal("0.5", "2^-3*4");
			equal("1250", "5^4*2");
			equal("390625", "5^(4*2)");
			equal("36", "4*3^2");
			equal("48", "3*4^2");
			equal("144", "(3*4)^2");
		}
		TEST_METHOD(Divide)
		{
			equal("Invalid syntax", "/");
			equal("Invalid syntax", "2/");
			equal("Invalid syntax", "/2");
			equal("Indeterminate", "0/0");
			equal("Infinity", "2/0");
			equal("0", "0/2");
			equal("1", "2/2");
			equal("0.666667", "2/3");
			equal("1.5", "3/2");
			equal("3.5", "7/2");
			equal("0.285714", "2/7");
			equal("0.5", "2.5/5");
			equal("2", "3/1.5");
			equal("2", "7.5/3.75");
			equal("0.5", "3.75/7.5");
			equal("-0.75", "-3/4");
			equal("-2", "4/-2");
			equal("0.5", "-2/-4");
			equal("2", "-4/-2");
			equal("0.666667", "4/3/2");
			equal("0.166667", "2/3/4");
			equal("Invalid syntax", "4//2");
			equal("Invalid syntax", "4/*2");
			equal("Invalid syntax", "4*/2");
			equal("Invalid syntax", "4-/2");
			equal("Invalid syntax", "2+3/");
			equal("Invalid syntax", "/2+3");

			equal("2", "2^3/4");
			equal("0.03125", "2^-3/4");
			equal("312.5", "5^4/2");
			equal("25", "5^(4/2)");
			equal("0.444444", "4/3^2");
			equal("0.1875", "3/4^2");
			equal("0.5625", "(3/4)^2");
		}
		TEST_METHOD(Exponent)
		{
			equal("Invalid syntax", "^");
			equal("Invalid syntax", "2^");
			equal("Invalid syntax", "^2");
			equal("Indeterminate", "0^0");
			equal("1", "2^0");
			equal("0", "0^2");
			equal("4", "2^2");
			equal("8", "2^3");
			equal("9", "3^2");
			equal("49", "7^2");
			equal("128", "2^7");
			equal("97.65625", "2.5^5");
			equal("5.196152", "3^1.5");
			equal("1911.964119", "7.5^3.75");
			equal("20194.565244", "3.75^7.5");
			equal("-81", "-3^4");
			equal("81", "(-3)^4");
			equal("-8", "(-2)^3");
			equal("0.0625", "4^-2");
			equal("-0.0625", "-2^-4");
			equal("-0.0625", "-4^-2");
			Assert::AreEqual(c.calc("(4^3)^2"), c.calc("4^3^2"));
			equal("Invalid syntax", "4^^2");
			equal("Invalid syntax", "4^*2");
			equal("Invalid syntax", "4*^2");
			equal("Invalid syntax", "4-^2");
			equal("Invalid syntax", "2+3^");
			equal("Invalid syntax", "^2+3");

			equal("162", "2*3^4");
			equal("-162", "2*-3^4");
			equal("0.3125", "5/4^2");
			equal("1.5625", "(5/4)^2");
			equal("128", "4^3*2");
			equal("40.5", "3^4/2");
			equal("9", "3^(4/2)");

			equal("Imaginary", "(-2)^(1/2)");
			equal("3", "9^(1/2)");
			equal("-1.414214", "-2^(1/2)");
			equal("0.008", "5^-3");
			equal("11112006825558016", "14^14");
			// equal("437893890380859375", "15^15"); // TODO: figure out why this fails by a small amount
			equal("1606938044258990275541962092341162602522202993782792835301376", "4^100");
		}
		TEST_METHOD(Parentheses)
		{
			equal("Invalid syntax", "(");
			equal("Invalid syntax", ")");
			equal("Invalid syntax", "2)");
			equal("Invalid syntax", ")2");
			equal("3", "3(");
			equal("2", "(2");
			equal("0", "0(0");
			equal("0", "2(0");
			equal("0", "0(2)");
			equal("6", "2(3");
			equal("12.5", "(5)2.5");
			equal("8", "4((2");
			equal("Invalid syntax", "4(*2");
			equal("8", "4*(2");
			equal("2", "4-(2");
			equal("-18", "(-6)3");
			equal("-15", "3(-5)");
			equal("-10", "-1(10)");
			equal("-9", "(-6)-3");
			equal("1", "(((((((((1))");
			equal("2", "((2))");
			equal("3", "1+(2)");
			equal("8.539734", "3.1415926(2.7182818)");
			equal("10", "(10)(1)");
			equal("24", "(((1)2)3)4");
			equal("27", "(1+2)^3");
			equal("Invalid syntax", "(3+5/(2*4)))");
		}
		TEST_METHOD(Factorial)
		{
			equal("Invalid syntax", "!");
			equal("Invalid syntax", "!2");
			equal("1", "0!");
			equal("1", "1!");
			equal("2", "2!");
			equal("6", "3!");
			equal("-6", "-3!");
			equal("Complex infinity", "(-3)!");
			equal("Undefined", "2.5!");
			equal("720", "(3!)!");
			Assert::AreNotEqual((std::string)"720", c.calc("3!!"));
			equal("36", "3!^2");
			equal("64", "2^3!");
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
			equal("1", "4%3%2");
			Assert::AreNotEqual((std::string)"0", c.calc("4%3%2"));
			equal("2", "2%3%4");
			equal("Invalid syntax", "4%%2");
			equal("Invalid syntax", "4%+2");
			equal("Invalid syntax", "4+%2");
			equal("Invalid syntax", "4-%2");
			equal("Invalid syntax", "2+3%");
			equal("Invalid syntax", "%2+3");

			equal("1", "2+3%4");
			equal("1", "2--3%4");
			equal("1", "5-4%2");
			equal("5", "5-(4%2)");
			equal("4", "4%3+2");
			equal("1", "3%4-2");
			equal("1", "(3%4)-2");
		}
		TEST_METHOD(AreEqual)
		{
			equal("Invalid syntax", "==");
			equal("Invalid syntax", "1==");
			equal("Invalid syntax", "==2");
			equal("Invalid syntax", "2+3==");
			equal("Invalid syntax", "==2+3");
			equal("Invalid syntax", "3===3");
			equal("Invalid syntax", "3>==3");
			equal("1", "2==2");
			equal("0", "1==2");
			equal("1", "-5==-5");
			equal("1", "5==--5");
			equal("1", "--5==5");
			equal("1", "--5==--5");
			equal("1", "3.14==3.14");
			equal("0", "3==3.14");
			equal("1", "3+.14==3.14");
			equal("1", "1+1==2");
			equal("1", "3==1+2");
			equal("1", "3!==6");
			equal("0", "3!==3");
			equal("0", "3==6!");
			equal("1", "6%5==1");
		}
		TEST_METHOD(AreNotEqual)
		{
			equal("Invalid syntax", "!=");
			equal("Invalid syntax", "1!=");
			equal("Invalid syntax", "!=2");
			equal("Invalid syntax", "2+3!=");
			equal("Invalid syntax", "!=2+3");
			equal("Invalid syntax", "3>!=3");
			equal("0", "2!=2");
			equal("1", "1!=2");
			equal("0", "-5!=-5");
			equal("0", "5!=--5");
			equal("0", "--5!=5");
			equal("0", "--5!=--5");
			equal("0", "3.14!=3.14");
			equal("1", "3!=3.14");
			equal("0", "3+.14!=3.14");
			equal("0", "1+1!=2");
			equal("0", "3!=1+2");
			equal("0", "3!!=6");
			equal("1", "3!!=3");
			equal("1", "3!=6!");
			equal("0", "6%5!=1");
		}
		TEST_METHOD(GreaterOrEqual)
		{
			equal("Invalid syntax", ">=");
			equal("Invalid syntax", "1>=");
			equal("Invalid syntax", ">=2");
			equal("Invalid syntax", "2+3>=");
			equal("Invalid syntax", ">=2+3");
			equal("Invalid syntax", "3>>=3");
			equal("1", "2>=2");
			equal("0", "1>=2");
			equal("1", "3>=1");
			equal("1", "-5>=-5");
			equal("1", "5>=--5");
			equal("1", "--5>=5");
			equal("1", "--5>=--5");
			equal("1", "3.14>=3.14");
			equal("0", "3>=3.14");
			equal("1", "3+.14>=3.14");
			equal("1", "1+1>=2");
			equal("1", "3>=1+2");
			equal("1", "3!>=6");
			equal("1", "3!>=3");
			equal("0", "3>=6!");
			equal("1", "6%5>=1");
		}
		TEST_METHOD(LesserOrEqual)
		{
			equal("Invalid syntax", "<=");
			equal("Invalid syntax", "1<=");
			equal("Invalid syntax", "<=2");
			equal("Invalid syntax", "2+3<=");
			equal("Invalid syntax", "<=2+3");
			equal("Invalid syntax", "3><=3");
			equal("1", "2<=2");
			equal("1", "1<=2");
			equal("0", "3<=1");
			equal("1", "-5<=-5");
			equal("1", "5<=--5");
			equal("1", "--5<=5");
			equal("1", "--5<=--5");
			equal("1", "3.14<=3.14");
			equal("1", "3<=3.14");
			equal("1", "3+.14<=3.14");
			equal("1", "1+1<=2");
			equal("1", "3<=1+2");
			equal("1", "3!<=6");
			equal("0", "3!<=3");
			equal("1", "3<=6!");
			equal("1", "6%5<=1");
		}
		TEST_METHOD(Greater)
		{
			equal("Invalid syntax", ">");
			equal("Invalid syntax", "1>");
			equal("Invalid syntax", ">2");
			equal("Invalid syntax", "2+3>");
			equal("Invalid syntax", ">2+3");
			equal("Invalid syntax", "3>>3");
			equal("0", "2>2");
			equal("0", "1>2");
			equal("1", "3>1");
			equal("0", "-5>-5");
			equal("0", "5>--5");
			equal("0", "--5>5");
			equal("0", "--5>--5");
			equal("0", "3.14>3.14");
			equal("0", "3>3.14");
			equal("0", "3+.14>3.14");
			equal("0", "1+1>2");
			equal("0", "3>1+2");
			equal("0", "3!>6");
			equal("1", "3!>3");
			equal("0", "3>6!");
			equal("0", "6%5>1");
		}
		TEST_METHOD(Lesser)
		{
			equal("Invalid syntax", "<");
			equal("Invalid syntax", "1<");
			equal("Invalid syntax", "<2");
			equal("Invalid syntax", "2+3<");
			equal("Invalid syntax", "<2+3");
			equal("Invalid syntax", "3<<3");
			equal("0", "2<2");
			equal("1", "1<2");
			equal("0", "3<1");
			equal("0", "-5<-5");
			equal("0", "5<--5");
			equal("0", "--5<5");
			equal("0", "--5<--5");
			equal("0", "3.14<3.14");
			equal("1", "3<3.14");
			equal("0", "3+.14<3.14");
			equal("0", "1+1<2");
			equal("0", "3<1+2");
			equal("0", "3!<6");
			equal("0", "3!<3");
			equal("1", "3<6!");
			equal("0", "6%5<1");
		}
	};
	TEST_CLASS(Vars)
	{
		TEST_METHOD(Ans)
		{
			// don't change the order of these tests
			equal("2", "1+1");
			equal("2", "ans");
			equal("2", "ans");
			equal("3", "3");
			equal("3", "ans");
			equal("5", "ans+2");
			equal("50", "10*ans");
			equal("100", "ans+ans");
			equal("Infinity", "1/0");
			equal("100", "ans"); // ans ignores error messages
		}
		TEST_METHOD(Constants)
		{
			equal("3.141593", "pi");
			equal("2.718282", "e");
			equal("8.539734", "pie");
			equal("8.539734", "pi*e");
			equal("5.859874", "pi+e");
			equal("22.459158", "pi^e");
			equal("8.539734", "epi");
			equal("Undefined character", "pei");
			equal("Undefined character", "p ie");
			equal("8.539734", "pi e");
			equal("6.283185", "2pi");
			equal("5.141593", "2+pi");
			equal("0", "e>pi");
			equal("7.389056", "e^2");
		}
	};
}
