#include "pch.h"
#include "CppUnitTest.h"
#include "../Calc/Calc.h"
#include "../Calc/Calc.cpp"
#include "../Calc/Symbol.h"
#include "../Calc/Symbol.cpp"
#include "../Calc/DefaultSymbols.hpp"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

// The test methods within each test class run in alphabetical order. They can affect each other.

namespace Tests
{
	Calc c;

	void equal(std::string str1, std::string str2)
	{
		Assert::AreEqual(str1, c.calc(str2));
	}

	void noReturn(std::string input)
	{
		Assert::AreEqual((std::string)"", c.calc(input));
	}

	TEST_CLASS(Ops)
	{
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
			noReturn(" ");
			noReturn("");
			equal("Undefined character(s)", "a");
			equal("Undefined character(s)", "jajvoaierjal;ndvoiasejrlaenafl;jo;ijwer");
			equal("Undefined character(s)", "$5");
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
			equal("0.83333", "5/(4+2)");
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
			equal("0.44444", "4/3^2");
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
			equal("5.19615", "3^1.5");
			equal("1911.96412", "7.5^3.75");
			equal("20194.56524", "3.75^7.5");
			equal("-81", "-3^4");
			equal("81", "(-3)^4");
			equal("-8", "(-2)^3");
			equal("0.0625", "4^-2");
			equal("-0.0625", "-2^-4");
			equal("-0.0625", "-4^-2");
			Assert::AreEqual(c.calc("4^(3^2)"), c.calc("4^3^2"));
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
			equal("-1.41421", "-2^(1/2)");
			equal("0.008", "5^-3");
			equal("11112006825558016", "14^14");
			// equal("437893890380859375", "15^15"); // TODO: figure out why this fails by a small amount
			equal("1606938044258990275541962092341162602522202993782792835301376", "4^100"); // TODO: use scientific notation here instead
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
			equal("8.53973", "3.1415926(2.7182818)");
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
			equal("Invalid syntax", "3= =3");
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
			equal("Invalid syntax", "3! =3");
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
			equal("Invalid syntax", "3> =3");
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
			equal("Invalid syntax", "3< =3");
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
			equal("Infinity", "1/0");
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
			equal("Undefined character(s)", "pei");
			equal("Undefined character(s)", "p ie");
			equal("8.53973", "pi e");
			equal("6.28319", "2pi");
			equal("5.14159", "2+pi");
			equal("0", "e>pi");
			equal("7.38906", "e^2");
		}
		TEST_METHOD(UserVars)
		{
			equal("Undefined character(s)", "five");
			noReturn(" five = 5");
			noReturn("four=4");
			noReturn("three = 3.0000");
			noReturn("num = 5");
			equal("5", "five");
			equal("4", "four");
			equal("5", "num");
			equal("3", "three");
			equal("20", "fivefour");
			equal("9", "five+four");
			equal("Undefined character(s)", "fi ve");
			equal("Undefined character(s)", "Five");
			noReturn("seven = 5^2*2-43");
			noReturn("nine = five + four");
			equal("7", "seven");
			equal("9", "nine");
			noReturn("num = three");
			equal("3", " num ");
			noReturn("eight = 2four");
			equal("8", "eight");
			noReturn("num_A = num");
			equal("3", "num_A");
			noReturn("num_C = num_B = num_A = eight");
			equal("8", "num_B");
			equal("8", "num_A");
			equal("8", "num_C");
			noReturn("a=b=c=3");
			equal("3", "a");
			equal("3", "b");
			equal("3", "c");
			equal("Invalid syntax", "10 = ten");
			equal("Invalid syntax", "ten = 5*2 = 5+5");
			noReturn("bool = 5 > 2");
			equal("1", "bool");
			noReturn("theta = pi/2");
			noReturn("test = theta*3");
			equal("4.71239", "test");
			noReturn("degrees = 180/pi*theta");
			equal("90", "degrees");
			noReturn("pi = 3");
			noReturn("Pi = 4");
			noReturn("PI = 10");
			noReturn("pI = -4");
			noReturn("_pi = -3.1415");
			equal("Invalid syntax", "-pi = -3.14");
			equal("3", "pi");
			equal("4", "Pi");
			equal("10", "PI");
			equal("-4", "pI");
			equal("-3.1415", "_pi");
			equal("3.1415", "-_pi");
			equal("Undefined character(s)", "y = 5x");
			equal("Invalid syntax", "y = 2four = 8");
			noReturn("ans = 7");
			equal("7", "ans");
			equal("1", "ans == 7");
			noReturn("ans = ans == 7");
			equal("0", "ans");
			noReturn("eight = eight");
			equal("8", "eight");
			noReturn("num = 3");
			noReturn("num = num + 2");
			equal("5", "num");

			c.resetSymbols();
		}
		TEST_METHOD(DefaultMacros)
		{
			equal("Invalid syntax", "cone_volume()");
			equal("Invalid syntax", "cone_volume(3)");
			equal("37.69911", "cone_volume(3,4)");
			equal("Invalid syntax", "cone_volume(3,4,5)");
			equal("Variable g = 9.80665", "help(g)");
			equal("Macro acsc(x) = asin(1/x)", "help(acsc)");
			equal("Macro help() = Display info about defined variables and functions", "help(help)");
			equal("C++ Function", "help(sqrt)");
			equal("Macro setprecision(int) = Adjust the number of digits displayed in answers", "help(setprecision)");
			equal("Invalid syntax", "acoth(help)");
			Assert::AreNotEqual((std::string)"-1", c.calc("rand()"));
			Assert::AreNotEqual(c.calc("ans"), c.calc("rand()")); // this test has a low chance of failing when the program is working correctly
			equal("1.1547", "csc(pi/3)");
			equal("Macro cylinder_volume(r,h) = pi*r^2*h", "help(cylinder_volume)");
			equal("549.77871", "cylinder_volume(5, 7");
			equal("1.1884", "csc(cot(pi/4");
			//equal("5.5", "csc(acsc(5.5))"); // this test will fail until trig functions with more precision can be used
			equal("Invalid syntax", "csc (pi/3)");
			equal("2.7207", "sphere_volume(sin(pi/3)");
			equal("3.14159", "pi");
			noReturn("setprecision(15");
			equal("3.141592653589793", "pi");
			noReturn("setprecision(3");
			equal("3.142", "pi");
			noReturn("setprecision(5)");
			equal("3.14159", "pi");
		}
		TEST_METHOD(UserMacros)
		{
			noReturn("f(x)=4x^2+3x+2");
			equal("164", "f(6)");
			equal("219", "f(7)");
			noReturn("g(x)=5x+9");
			equal("14", "g(1)");
			equal("53", "f(2)+g(4)");
			equal("2088", "f(2)g(4)(3)");
			equal("828", "f(g(1))");
			equal("54", "g(f(1))");
			equal("353", "f(f(1");
			noReturn("h(x,y) = f(x)+g(y)");
			equal("Macro h(x,y) = f(x)+g(y)", "help(h)");
			equal("28", "h(1,2)");
			noReturn("g(x)=4x+9");
			equal("26", "h(1,2)");
			equal("21.56637", "g(pi)");
			equal("Invalid syntax", "g");
			equal("Invalid syntax", "var = g(x) = 5x");
			equal("Invalid syntax", "g(x) = f(x) = 5x");
			noReturn("a=9999");
			equal("Invalid syntax", "add (a,b)=a+b");
			noReturn(" add( a , b ) = a + b ");
			equal("60", "add(25,35");
			equal("Invalid syntax", "add(25,35,40)");
			equal("Macro add(a,b) = a + b", "help(add)");
			noReturn("add(a,b,c)=a+b+c");
			equal("6", "add(1,2,3)");
			equal("Invalid syntax", "add(4,5)");
			noReturn("divide(numerator,denominator) = numerator/denominator");
			equal("Invalid syntax", "divide(3/6)");
			equal("0.5", "divide(3,6)");
			noReturn("f(vjoieuor,joiavjoa,iozuboie)=joiavjoavjoieuoriozuboie");
			equal("60", "f(3,4,5)");
			equal("Macro f(vjoieuor,joiavjoa,iozuboie) = joiavjoavjoieuoriozuboie", "help(f)");
			noReturn("h(x,y)=8sin(2x)+7tan(sqrt(y))");
			equal("2.05032", "h(2,16)");
			noReturn("f(x)=jobiajweojfalkfsdjvoiajsejf");
			equal("Macro f(x) = jobiajweojfalkfsdjvoiajsejf", "help(f)");
			equal("Undefined character(s)", "f(5)");
			noReturn("f(x,y) = x + y + z");
			equal("Undefined character(s)", "f(2,4)");
			noReturn("f(x)=38973");
			equal("38973", "f(738684272873)");
			equal("Undefined character(s)", "f(x)==4x");
			equal("Undefined character(s)", "f(x)=");
			equal("Undefined character(s)", "=f(x)");
			equal("Invalid syntax", "f()");
			equal("Invalid syntax", "f() = 3");
			equal("Invalid syntax", "func tion(x) = 4x");
			equal("Invalid syntax", "f(parame ter)=4 * parame ter");
			equal("Invalid syntax", "f(x,,y) = x + y");
			equal("Invalid syntax", "f(,x,y) = x + y");
			equal("Invalid syntax", "f(x,y,) = x + y");
			equal("Invalid syntax", "f(g(x),y) = x + y");
			equal("Invalid syntax", "f(x,x+y) = x + y");
			equal("Invalid syntax", "f((x,y)) = x + y");
			equal("Invalid syntax", "f(3x,y) = x + y");
			equal("3.14159", "pi");
			noReturn("f(pi,y) = pi^2+y");
			equal("5", "f(1,4)");
			equal("3.14159", "pi");

			c.resetSymbols();
		}
		TEST_METHOD(Functions)
		{
			equal("Invalid syntax", "sin(");
			equal("Invalid syntax", "sin(.)");
			equal("Invalid syntax", "sin(sin)");
			equal("Invalid syntax", "sin(4,5)");
			equal("2", "sqrt(4)");
			equal("Imaginary", "sqrt(-4)");
			equal("8", "ceil(7.3");
			equal("9", "floor(9.");
			equal("3", "abs(cbrt(-27))");
			equal("0.95", "sin( asin( 0.95 )");
			equal("Imaginary", "sin( asin( 2.15 )");
			equal("0.72654", "tan(pi/5");
			equal("Invalid syntax", "cos (pi/3)");
			equal("2.71828", "esin(pi/2");
			Assert::AreEqual(c.calc("sin(pi / 3)^3"), c.calc("(sin(pi / 3))^3"));
			equal("1.23474", "acos(acoth(pi))");
			equal("0.97385", "sin(3+(4/5)-2)");
			equal("Invalid syntax", "sin(setprecision(5))");
		}
	};
}
