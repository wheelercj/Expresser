#include "pch.h"
#include "CppUnitTest.h"
#include "../Calc/Calc.cpp"
#include "../Calc/Macro.cpp"
#include "../Calc/Common.cpp"
#include "../Calc/Functions.cpp"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

// The test methods within each test class run in alphabetical order. They can affect each other.

namespace Tests
{
	Calc calc(5);

	void equal(std::string str1, std::string str2)
	{
		Assert::AreEqual(str1, calc(str2));
	}

	void no_return(std::string input)
	{
		Assert::AreEqual((std::string)"", calc(input));
	}

	TEST_CLASS(Ops)
	{
	public:

		TEST_METHOD(Syntax)
		{
			equal("3", "    1      +         2  ");
			equal("8.15", "8+.15");
			equal("8.3", "0.30 + 8");
			equal("Invalid use of a period", ".");
			equal("Invalid use of a period", ".+3");
			equal("Invalid use of a period", "3+.");
			equal("Error: multiple periods in one number", "192.168.0.1");
			equal("Invalid syntax: +/", "+/");
			no_return(" ");
			no_return("");
			equal("Undefined character: a", "a");
			equal("Undefined characters: jajvoai", "jajvoaierjal;ndvoiasejrlaenafl;jo;ijwer");
			equal("Undefined character: $", "$5");
			equal("-382.00476", "53.28394 + 392.48 - 1.5^3(65.23 * 3.76)");
			equal("-20.06481", "-3+4*-5-6(-7/8)/-9^2--3");
			equal("-1.8", "(1-2)^3*4/5+6-7");
			equal("19.93519", "3+4*5-6(7/8)/9^2-3");
			equal("20.93519", "3 + 4 * 5 - 6 ( 7 / 8 ) / 9 ^ 2 - 2");
			equal("306.25", "((4*5)^2(7/8)^2)");
			equal("1461.33333", "9-8+7/6*5^4(3-1)+2");
			equal("80", "20 4");
			equal("24", "20 +4");
			equal("23", "3+4 5");
		}
		TEST_METHOD(Add)
		{
			equal("Error: not enough operands for the given operators", "+");
			equal("Error: not enough operands for the given operators", "2+");
			equal("Error: not enough operands for the given operators", "+2");
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
			equal("Invalid syntax: ++", "4++2");
			equal("Invalid syntax: +*", "4+*2");
			equal("Invalid syntax: *+", "4*+2");
			equal("Invalid syntax: -+", "4-+2");
			equal("Error: not enough operands for the given operators", "2+3+");
			equal("Error: not enough operands for the given operators", "+2+3");

			equal("10", "2*3+4");
			equal("-2", "2*-3+4");
			equal("3.25", "5/4+2");
			equal("0.83333", "5/(4+2)");
			equal("10", "4+3*2");
			equal("5", "3+4/2");
			equal("3.5", "(3+4)/2");
		}
		TEST_METHOD(Subtract)
		{
			equal("Error: not enough operands for the given operators", "-");
			equal("Error: not enough operands for the given operators", "2-");
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
			equal("Invalid syntax: -*", "4-*2");
			equal("-8", "4*-2");
			equal("0", "1---1");
			equal("7", "------------7");
			equal("Invalid syntax: -*", "3*---*4");
			equal("Error: not enough operands for the given operators", "2+3-");

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
			equal("Error: not enough operands for the given operators", "*");
			equal("Error: not enough operands for the given operators", "2*");
			equal("Error: not enough operands for the given operators", "*2");
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
			equal("Invalid syntax: **", "4**2");
			equal("Invalid syntax: *+", "4*+2");
			equal("Invalid syntax: +*", "4+*2");
			equal("Invalid syntax: -*", "4-*2");
			equal("Error: not enough operands for the given operators", "2+3*");
			equal("Error: not enough operands for the given operators", "*2+3");

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
			equal("Error: not enough operands for the given operators", "/");
			equal("Error: not enough operands for the given operators", "2/");
			equal("Error: not enough operands for the given operators", "/2");
			equal("Indeterminate: 0/0", "0/0");
			equal("Infinity: n/0", "2/0");
			equal("0", "0/2");
			equal("1", "2/2");
			equal("0.66667", "2/3");
			equal("1.5", "3/2");
			equal("3.5", "7/2");
			equal("0.28571", "2/7");
			equal("0.5", "2.5/5");
			equal("2", "3/1.5");
			equal("2", "7.5/3.75");
			equal("0.5", "3.75/7.5");
			equal("-0.75", "-3/4");
			equal("-2", "4/-2");
			equal("0.5", "-2/-4");
			equal("2", "-4/-2");
			equal("0.66667", "4/3/2");
			equal("0.16667", "2/3/4");
			equal("Invalid syntax: //", "4//2");
			equal("Invalid syntax: /*", "4/*2");
			equal("Invalid syntax: */", "4*/2");
			equal("Invalid syntax: -/", "4-/2");
			equal("Error: not enough operands for the given operators", "2+3/");
			equal("Error: not enough operands for the given operators", "/2+3");

			equal("2", "2^3/4");
			equal("0.03125", "2^-3/4");
			equal("312.5", "5^4/2");
			equal("25", "5^(4/2)");
			equal("0.44444", "4/3^2");
			equal("0.1875", "3/4^2");
			equal("0.5625", "(3/4)^2");
		}
		TEST_METHOD(Exponent)
		{
			equal("Error: not enough operands for the given operators", "^");
			equal("Error: not enough operands for the given operators", "2^");
			equal("Error: not enough operands for the given operators", "^2");
			equal("Indeterminate: 0^0", "0^0");
			equal("1", "2^0");
			equal("0", "0^2");
			equal("4", "2^2");
			equal("8", "2^3");
			equal("9", "3^2");
			equal("49", "7^2");
			equal("128", "2^7");
			equal("97.65625", "2.5^5");
			equal("5.19615", "3^1.5");
			equal("1911.96412", "7.5^3.75");
			equal("20194.56524", "3.75^7.5");
			equal("-81", "-3^4");
			equal("81", "(-3)^4");
			equal("-8", "(-2)^3");
			equal("0.0625", "4^-2");
			equal("-0.0625", "-2^-4");
			equal("-0.0625", "-4^-2");
			Assert::AreEqual(calc("4^(3^2)"), calc("4^3^2"));
			equal("Invalid syntax: ^^", "4^^2");
			equal("Invalid syntax: ^*", "4^*2");
			equal("Invalid syntax: *^", "4*^2");
			equal("Invalid syntax: -^", "4-^2");
			equal("Error: not enough operands for the given operators", "2+3^");
			equal("Error: not enough operands for the given operators", "^2+3");

			equal("162", "2*3^4");
			equal("-162", "2*-3^4");
			equal("0.3125", "5/4^2");
			equal("1.5625", "(5/4)^2");
			equal("128", "4^3*2");
			equal("40.5", "3^4/2");
			equal("9", "3^(4/2)");

			equal("Imaginary: even root of a negative", "(-2)^(1/2)");
			equal("3", "9^(1/2)");
			equal("-1.41421", "-2^(1/2)");
			equal("0.008", "5^-3");
			equal("11112006825558016", "14^14");
			// equal("437893890380859375", "15^15"); // TODO: figure out why this fails by a small amount
			equal("1606938044258990275541962092341162602522202993782792835301376", "4^100"); // TODO: use scientific notation here instead
		}
		TEST_METHOD(Parentheses)
		{
			equal("Error: not enough operands for the given operators", "(");
			equal("Error: missing an opening parenthesis", ")");
			equal("Error: missing an opening parenthesis", "2)");
			equal("Error: missing an opening parenthesis", ")2");
			equal("Error: not enough operands for the given operators", "3(");
			equal("2", "(2");
			equal("0", "0(0");
			equal("0", "2(0");
			equal("0", "0(2)");
			equal("6", "2(3");
			equal("12.5", "(5)2.5");
			equal("8", "4((2");
			equal("Invalid syntax: (*", "4(*2");
			equal("8", "4*(2");
			equal("2", "4-(2");
			equal("-18", "(-6)3");
			equal("-15", "3(-5)");
			equal("-10", "-1(10)");
			equal("-9", "(-6)-3");
			equal("1", "(((((((((1))");
			equal("2", "((2))");
			equal("3", "1+(2)");
			equal("8.53973", "3.1415926(2.7182818)");
			equal("10", "(10)(1)");
			equal("24", "(((1)2)3)4");
			equal("27", "(1+2)^3");
			equal("Error: missing an opening parenthesis", "(3+5/(2*4)))");
		}
		TEST_METHOD(Factorial)
		{
			equal("Error: expected an operand before the factorial operator", "!");
			equal("Error: expected an operand before the factorial operator", "!2");
			equal("1", "0!");
			equal("1", "1!");
			equal("2", "2!");
			equal("6", "3!");
			equal("-6", "-3!");
			equal("Complex infinity", "(-3)!");
			equal("Undefined", "2.5!");
			equal("720", "(3!)!");
			equal("36", "3!^2");
			equal("64", "2^3!");
		}
		TEST_METHOD(Modulus)
		{
			equal("Error: not enough operands for the given operators", "%");
			equal("Error: not enough operands for the given operators", "2%");
			equal("Error: not enough operands for the given operators", "%2");
			equal("Undefined: n%0", "0%0");
			equal("Undefined: n%0", "2%0");
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
			Assert::AreNotEqual((std::string)"0", calc("4%3%2"));
			equal("2", "2%3%4");
			equal("Invalid syntax: %%", "4%%2");
			equal("Invalid syntax: %+", "4%+2");
			equal("Invalid syntax: +%", "4+%2");
			equal("Invalid syntax: -%", "4-%2");
			equal("Error: not enough operands for the given operators", "2+3%");
			equal("Error: not enough operands for the given operators", "%2+3");

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
			equal("Error: not enough operands for the given operators", "==");
			equal("Error: not enough operands for the given operators", "1==");
			equal("Error: not enough operands for the given operators", "==2");
			equal("Error: not enough operands for the given operators", "2+3==");
			equal("Error: not enough operands for the given operators", "==2+3");
			equal("Error: not enough operands for the given operators", "3===3");
			equal("Error: not enough operands for the given operators", "3>==3");
			equal("Invalid character before assignment operator: 3", "3= =3");
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
			equal("Error: not enough operands for the given operators", "!=");
			equal("Error: not enough operands for the given operators", "1!=");
			equal("Error: not enough operands for the given operators", "!=2");
			equal("Error: not enough operands for the given operators", "2+3!=");
			equal("Error: not enough operands for the given operators", "!=2+3");
			equal("Invalid syntax: >!", "3>!=3");
			equal("Invalid character before assignment operator: 3", "3! =3");
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
			equal("Error: not enough operands for the given operators", ">=");
			equal("Error: not enough operands for the given operators", "1>=");
			equal("Error: not enough operands for the given operators", ">=2");
			equal("Error: not enough operands for the given operators", "2+3>=");
			equal("Error: not enough operands for the given operators", ">=2+3");
			equal("Invalid syntax: >>", "3>>=3");
			equal("Invalid character before assignment operator: 3", "3> =3");
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
			equal("Error: not enough operands for the given operators", "<=");
			equal("Error: not enough operands for the given operators", "1<=");
			equal("Error: not enough operands for the given operators", "<=2");
			equal("Error: not enough operands for the given operators", "2+3<=");
			equal("Error: not enough operands for the given operators", "<=2+3");
			equal("Invalid syntax: ><", "3><=3");
			equal("Invalid character before assignment operator: 3", "3< =3");
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
			equal("Error: not enough operands for the given operators", ">");
			equal("Error: not enough operands for the given operators", "1>");
			equal("Error: not enough operands for the given operators", ">2");
			equal("Error: not enough operands for the given operators", "2+3>");
			equal("Error: not enough operands for the given operators", ">2+3");
			equal("Invalid syntax: >>", "3>>3");
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
			equal("Error: not enough operands for the given operators", "<");
			equal("Error: not enough operands for the given operators", "1<");
			equal("Error: not enough operands for the given operators", "<2");
			equal("Error: not enough operands for the given operators", "2+3<");
			equal("Error: not enough operands for the given operators", "<2+3");
			equal("Invalid syntax: <<", "3<<3");
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
	TEST_CLASS(Symbols)
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
			equal("Infinity: n/0", "1/0");
			equal("100", "ans"); // ans ignores error messages
		}
		TEST_METHOD(DefaultVars)
		{
			equal("3.14159", "pi");
			equal("2.71828", "e");
			equal("8.53973", "pie");
			equal("8.53973", "pi*e");
			equal("5.85987", "pi+e");
			equal("22.45916", "pi^e");
			equal("8.53973", "epi");
			equal("Undefined character: p", "pei");
			equal("Undefined character: p", "p ie");
			equal("8.53973", "pi e");
			equal("6.28319", "2pi");
			equal("5.14159", "2+pi");
			equal("0", "e>pi");
			equal("7.38906", "e^2");
		}
		TEST_METHOD(UserVars)
		{
			calc._reset_symbols();

			equal("Undefined characters: fiv", "five");
			no_return(" five = 5");
			no_return("four=4");
			no_return("three = 3.0000");
			no_return("num = 5");
			equal("5", "five");
			equal("4", "four");
			equal("5", "num");
			equal("3", "three");
			equal("20", "fivefour");
			equal("9", "five+four");
			equal("Undefined characters: fi", "fi ve");
			equal("Undefined characters: Fiv", "Five");
			no_return("seven = 5^2*2-43");
			no_return("nine = five + four");
			equal("7", "seven");
			equal("9", "nine");
			no_return("num = three");
			equal("3", " num ");
			no_return("eight = 2four");
			equal("8", "eight");
			no_return("num_A = num");
			equal("3", "num_A");
			no_return("num_C = num_B = num_A = eight");
			equal("8", "num_B");
			equal("8", "num_A");
			equal("8", "num_C");
			no_return("a=b=c=3");
			equal("3", "a");
			equal("3", "b");
			equal("3", "c");
			equal("Invalid character before assignment operator: 1", "10 = ten");
			equal("Invalid character before assignment operator: 5", "ten = 5*2 = 5+5");
			no_return("bool = 5 > 2");
			equal("1", "bool");
			no_return("theta = pi/2");
			no_return("test = theta*3");
			equal("4.71239", "test");
			no_return("degrees = 180/pi*theta");
			equal("90", "degrees");
			no_return("pi = 3");
			no_return("Pi = 4");
			no_return("PI = 10");
			no_return("pI = -4");
			no_return("_pi = -3.1415");
			equal("Invalid character before assignment operator: -", "-pi = -3.14");
			equal("3", "pi");
			equal("4", "Pi");
			equal("10", "PI");
			equal("-4", "pI");
			equal("-3.1415", "_pi");
			equal("3.1415", "-_pi");
			equal("Undefined character: x", "y = 5x");
			equal("Invalid character before assignment operator: 2", "y = 2four = 8");
			no_return("ans = 7");
			equal("7", "ans");
			equal("1", "ans == 7");
			no_return("ans = ans == 7");
			equal("0", "ans");
			no_return("eight = eight");
			equal("8", "eight");
			no_return("num = 3");
			no_return("num = num + 2");
			equal("5", "num");

			calc._reset_symbols();
		}
		TEST_METHOD(DefaultMacros)
		{
			equal("1", "logb(10,10");
			equal("0.69897", "logb(10,5");
			equal("Error: expected 2 arguments for function cone_volume", "cone_volume()");
			equal("Error: expected 2 arguments for function cone_volume", "cone_volume(3)");
			equal("37.69911", "cone_volume(3,4)");
			equal("Error: expected 2 arguments for function cone_volume", "cone_volume(3,4,5)");
			equal("Variable g = 9.80665", "help(g)");
			equal("Function acsc(radians) = asin(1/radians)", "help(acsc)");
			equal("Function help() = Display info about defined variables and functions", "help(help)");
			equal("C++ Function", "help(sqrt)");
			equal("Function setprecision(int) = Adjust the number of digits displayed in answers", "help(setprecision)");
			equal("Error: expected '(' after function name", "acoth(help)");
			equal("1.1547", "csc(pi/3)");
			equal("Function cylinder_volume(r,h) = pi*r^2*h", "help(cylinder_volume)");
			equal("549.77871", "cylinder_volume(5, 7");
			equal("1.1884", "csc(cot(pi/4");
			//equal("5.5", "csc(acsc(5.5))"); // this test will fail until trig functions with more precision can be used
			equal("Error: expected '(' after function name", "csc (pi/3)");
			equal("2.7207", "sphere_volume(sin(pi/3)");
			equal("3.14159", "pi");
			no_return("setprecision(15");
			equal("3.141592653589793", "pi");
			no_return("setprecision(3");
			equal("3.142", "pi");
			no_return("setprecision(5)");
			equal("3.14159", "pi");
		}
		TEST_METHOD(UserMacros)
		{
			no_return("f(x)=4x^2+3x+2");
			equal("164", "f(6)");
			equal("219", "f(7)");
			no_return("g(x)=5x+9");
			equal("14", "g(1)");
			equal("53", "f(2)+g(4)");
			equal("2088", "f(2)g(4)(3)");
			equal("828", "f(g(1))");
			equal("54", "g(f(1))");
			equal("353", "f(f(1");
			no_return("h(x,y) = f(x)+g(y)");
			equal("Function h(x,y) = f(x)+g(y)", "help(h)");
			equal("28", "h(1,2)");
			no_return("g(x)=4x+9");
			equal("26", "h(1,2)");
			equal("21.56637", "g(pi)");
			equal("Error: expected '(' after function name", "g");
			equal("Multiple simultaneous definitions are only possible with variables", "var = g(x) = 5x");
			equal("Multiple simultaneous definitions are only possible with variables", "g(x) = f(x) = 5x");
			no_return("a=9999");
			equal("Invalid space before parameter(s)", "add (a,b)=a+b");
			no_return(" add( a , b ) = a + b ");
			equal("60", "add(25,35");
			equal("Error: expected 2 arguments for function add", "add(25,35,40)");
			equal("Function add(a,b) = a + b", "help(add)");
			no_return("add(a,b,c)=a+b+c");
			equal("6", "add(1,2,3)");
			equal("Error: expected 3 arguments for function add", "add(4,5)");
			no_return("divide(numerator,denominator) = numerator/denominator");
			equal("Error: expected 2 arguments for function divide", "divide(3/6)");
			equal("0.5", "divide(3,6)");
			no_return("f(vjoieuor,joiavjoa,iozuboie)=joiavjoavjoieuoriozuboie");
			equal("60", "f(3,4,5)");
			equal("Function f(vjoieuor,joiavjoa,iozuboie) = joiavjoavjoieuoriozuboie", "help(f)");
			no_return("h(x,y)=8sin(2x)+7tan(sqrt(y))");
			equal("2.05032", "h(2,16)");
			no_return("f(x)=jobiajweojfalkfsdjvoiajsejf");
			equal("Function f(x) = jobiajweojfalkfsdjvoiajsejf", "help(f)");
			equal("Undefined characters: jobi", "f(5)"); // ends at 'a' because 'a' was defined earlier
			no_return("f(x,y) = x + y + z");
			equal("Undefined character: z", "f(2,4)");
			no_return("f(x)=38973");
			equal("38973", "f(738684272873)");
			equal("Undefined character: x", "f(x)==4x");
			equal("Undefined character: x", "f(x)=");
			equal("Undefined character: x", "=f(x)");
			equal("Invalid syntax", "f()");
			equal("Invalid syntax: unnamed parameter", "f() = 3");
			equal("Invalid space before assignment operator", "func tion(x) = 4x");
			equal("Invalid space in parameter name", "f(parame ter)=4 * parame ter");
			equal("Invalid syntax: unnamed parameter", "f(x,,y) = x + y");
			equal("Invalid syntax: unnamed parameter", "f(,x,y) = x + y");
			equal("Invalid syntax: unnamed parameter", "f(x,y,) = x + y");
			equal("Invalid character in parameter list: (", "f(g(x),y) = x + y");
			equal("Invalid character in parameter list: +", "f(x,x+y) = x + y");
			equal("Invalid character in parameter list: (", "f((x,y)) = x + y");
			equal("Invalid character in parameter list: 3", "f(3x,y) = x + y");
			equal("3.14159", "pi");
			no_return("f(pi,y) = pi^2+y");
			equal("5", "f(1,4)");
			equal("3.14159", "pi");
			no_return("f(x) = exp(2x)");
			equal("403.42879", "f(3)");

			calc._reset_symbols();
		}
		TEST_METHOD(Functions)
		{
			equal("Invalid syntax", "sin(");
			equal("Invalid syntax", "sin()");
			equal("Invalid use of a period", "sin(.)");
			equal("Error: expected '(' after function name", "sin(sin)");
			equal("Error: expected 1 argument for function sin", "sin(4,5)");
			equal("0", "sin(pi)");
			equal("2", "sqrt(4)");
			equal("Imaginary", "sqrt(-4)");
			equal("1", "ln(e)");
			equal("1.60944", "ln(5");
			equal("8", "ceil(7.3");
			equal("9", "floor(9.");
			equal("3", "abs(cbrt(-27))");
			equal("0.95", "sin( asin( 0.95 )");
			equal("Imaginary", "sin( asin( 2.15 )");
			equal("0.72654", "tan(pi/5");
			equal("Error: expected '(' after function name", "cos (pi/3)");
			equal("2.71828", "esin(pi/2");
			Assert::AreEqual(calc("sin(pi / 3)^3"), calc("(sin(pi / 3))^3"));
			equal("1.23474", "acos(acoth(pi))");
			equal("0.97385", "sin(3+(4/5)-2)");
			equal("Invalid syntax", "sin(setprecision(5))");
			Assert::AreNotEqual((std::string)"Error: missing an opening parenthesis", calc("rand()+1"));
			Assert::AreNotEqual((std::string)"Error: not enough operands for the given operators", calc("1+rand()"));
			equal("Error: expected 0 arguments for function rand", "rand(8)");
			equal("Imaginary", "quad(1,2,3)");
			equal("-4.791288 or -0.208712", "quad(1,5,1)");
			equal("1.236068 or -3.236068", "quad(-1,-2,4)");
		}
	};
}
