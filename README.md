# Expresser

A fast and expressive Computer Algebra System focused on ease of use.
No longer in development; this was made for learning purposes.

To compile the source code, you will need at least a C++17 compiler. [Here](https://drive.google.com/open?id=1mLnwM1aZPquCDheh4-TCCNiOytMtqfzz)'s how to switch compilers in Visual Studio Community 2019.

### Key features
* Easily define your own functions and variables
<details>
<summary>Operators</summary>
  
| Symbol | Operation |
| ------ | --------- |
| `( )` | parentheses |
| `!` | factorial |
| `^` | exponent |
| `*` | multiply |
| `/` | divide |
| `+` | add |
| `-` | either subtract or negate |
| `%` | modulo |
| `=` | set equal to (variable or function name must be on the left side) |
| `==` | is equal to |
| `!=` | is not equal to |
| `>=` | is greater than or equal to |
| `<=` | is less than or equal to |
| `>` | is greater than |
| `<` | is less than |

</details>

<details>
<summary>Default Variables</summary>
  
| Name | Value | Info |
| ---- | ----- | ---- |
| `ans` | 0 | Automatically changes to the latest answer that is not an error message |
| `pi` | 3.141592653589793238462643383279502884197169399375105820974 | |
| `e` | 2.718281828459045235360287471352662497757247093699959574966 | Euler's number |
| `g` | 9.80665 | Acceleration due to gravity near Earth's surface in meters per second squared |
| `phi` | 1.618033988749894848204586834365638117720309179805762862135 | Golden Ratio |

</details>

<details>
<summary>Default Functions</summary>
  
| Name | Parameters | Info |
| ---- | ---------- | ---- |
| `help` | (`variable or function name`) | Get help with a variable or function |
| `help` | ( ) | Get help with all variables and functions |
| `setprecision` | (`x`) | Adjust the precision of answers |
| `sqrt` | (`x`) | Square root |
| `cbrt` | (`x`) | Cube root |
| `abs` | (`x`) | Absolute value |
| `pow` | (`x`, `y`) | Power function |
| `exp` | (`x`) | Exponential function |
| `ln` | (`x`) | Logarithm base e |
| `log` | (`x`) | Logarithm base 10 |
| `lg` | (`x`) | Logarithm base 2 |
| `logb` | (`base`, `x`) | Logarithm base b |
| `round` | (`x`) | Round to the nearest integer |
| `ceil` | (`x`) | Round up |
| `floor` | (`x`) | Round down |
| `sin` | (`radians`) | Sine |
| `cos` | (`radians`) | Cosine |
| `tan` | (`radians`) | Tangent |
| `csc` | (`radians`) | Cosecant |
| `sec` | (`radians`) | Secant |
| `cot` | (`radians`) | Cotangent |
| `asin` | (`radians`) | Inverse sine |
| `acos` | (`radians`) | Inverse cosine |
| `atan` | (`radians`) | Inverse tangent |
| `acsc` | (`radians`) | Inverse cosecant |
| `asec` | (`radians`) | Inverse secant |
| `acot` | (`radians`) | Inverse cotangent |
| `sinh` | (`radians`) | Hyperbolic sine |
| `cosh` | (`radians`) | Hyperbolic cosine |
| `tanh` | (`radians`) | Hyperbolic tangent |
| `csch` | (`radians`) | Hyperbolic cosecant |
| `sech` | (`radians`) | Hyperbolic secant |
| `coth` | (`radians`) | Hyperbolic cotangent |
| `asinh` | (`radians`) | Inverse hyperbolic sine |
| `acosh` | (`radians`) | Inverse hyperbolic cosine |
| `atanh` | (`radians`) | Inverse hyperbolic tangent |
| `acsch` | (`radians`) | Inverse hyperbolic cosecant |
| `asech` | (`radians`) | Inverse hyperbolic secant |
| `acoth` | (`radians`) | Inverse hyperbolic cotangent |
| `rand` | ( ) | Generate a random number |
| `quad` | (`a`, `b`, `c`) | Quadratic formula |
| `erf` | (`x`) | Error function |
| `erfc` | (`x`) | Complementary error function |
| `tgamma` | (`x`) | Gamma function |
| `lgamma` | (`x`) | Log gamma function |
| `cylinder_volume` | (`radius`, `height`) | |
| `sphere_volume` | (`radius`) | |
| `cone_volume` | (`radius`, `height`) | |
| `pyramid_volume` | (`Base area`, `height`) | |
| `simple_interest` | (`Principal amount`, `rate`, `time`) | |
| `compound_interest` | (`Principal amount`, `rate`, `time`, `number of compounds`) | |
| `present_value` | (`Cash flow at period 1`, `rate of return`, `number of periods`) | |
| `future_value` | (`Cash flow at period 0`, `rate of return`, `number of periods`) | |

</details>

![Calc demo](docs/Calc_demo.png)
