# How to Contribute

Thanks for your interest! The main goals of this project are for contributors to learn software engineering techniques and principles, and to help them prepare for a career in software engineering or a closely related field. As such, contributions are welcome provided the following:
1. Contributors make an effort to create their contributions themselves, and only search online for answers to specific questions as a last resort. Feel free to ask for help from fellow contributors, professors, school classmates, etc.
2. Contributors help others understand and learn from their contributions with thorough documentation.
3. Contributors follow the [code of conduct](https://github.com/wheelercj/Expresser/blob/master/docs/CODE_OF_CONDUCT.md).

## Why contribute?
* Learn software engineering skills not taught in classes at LAVC such as automated testing, version control, and the ability to work with a team.
* Prepare your portfolio for your transfer application and/or for future job interviews. Contributing to open source projects looks great! Sometimes your portfolio is even more important than what classes you've taken and what degrees you have.
* Get more practice, which is essential to becoming a good software engineer.
* This project is organized so that you only have to understand a tiny part of it to be able to contribute.

## How to contribute code
1. Start by creating a [fork](https://guides.github.com/activities/forking/) of the repository.
2. Find a problem to fix or feature to add that will be important to users. Looking at the project's [to do list](https://github.com/wheelercj/Expresser/projects/2) or [issues](https://github.com/wheelercj/Expresser/issues) might help. One of the easiest ways to add a new feature to the program is by creating a calculator function (see the next section).
3. Create a new branch off of the `develop` branch with a descriptive name.
4. Follow the steps in the [GitHub flow guide](https://guides.github.com/introduction/flow/). Merge your commits to `develop`.

### How to create a new calculator function
1. Add the function's info to the `README.md`.
1. Open the file `DefaultSymbols.hpp`.
2. If your function is a combination of features the program already has, then it can be expressed as a string and can be added to the `default_macros` map. That's it, the function is implemented!
3. Otherwise, you will need to write a C++ function for this new calculator function. Start by adding the function name and [function pointer](https://www.cprogramming.com/tutorial/function-pointers.html) to the `default_funcs` map in `DefaultSymbols.hpp`.
4. Open the file `Functions.h` and add the function prototype.
5. Open the file `Functions.cpp` and add the function definition.
6. If there is already another calculator function of the same type (same number of parameters, type of each parameter, and return type), then you're done!
7. Otherwise, open the file `Calc.h`, scroll down to the overloaded `_call` function prototypes, and create a new one. Only the type of the function pointer should be different for each `_call` function.
8. Open the file `Calc.cpp` and define the new `_call` function. Take a look at the other `_call` functions as a guide for how to write this one. The purpose of these functions is to adapt the function's input(s) and output to and from strings (a lot of the program works with strings, but the calculator functions don't have to).
9. Scroll up to the function `_resolve_function_type` and add your new function type following the format there.

## How to report a bug
1. If the bug is a security vulnerability, send the bug report to stemclublavc@gmail.com instead of posting it on GitHub.
2. Otherwise, search the [issues](https://github.com/wheelercj/Expresser/issues) to see if someone else already reported the bug.
3. If the bug has not already been reported, [create a new bug report](https://github.com/wheelercj/Expresser/issues/new?assignees=&labels=bug&template=bug_report.md&title=) with as much relevant detail as possible.

## How to request a feature or enhancement
1. Search the [issues](https://github.com/wheelercj/Expresser/issues) to see if someone else already requested the feature. You can add comments to existing feature requests.
2. If the feature has not been requested, [create a new feature request](https://github.com/wheelercj/Expresser/issues/new?assignees=&labels=enhancement&template=feature_request.md&title=) with as much relevant detail as possible.

## FAQs
* **Why doesn't the project use `using namespace std;`?**  
	  Programs can become complicated enough that names for objects or functions have to be reused by different namespaces. Instead of trying to predict which members of a namespace might be reused in the future, or trying to find the problem when something goes wrong, it is usually best to distinguish a namespace as a prefix, e.g. `std::cout`.
* **What does the `.hpp` filetype do?**  
	  The `.hpp` filetype is the same as `.h`. This project is following the convention that a header file without a corresponding source file will use `.hpp`.

## Suggested viewing/reading
* [Intro to GitHub and Git](https://www.youtube.com/watch?v=vR-y_2zWrIE&list=PLWKjhJtqVAbkFiqHnNaxpOPhh9tSWMXIF)
* [Guide to writing commit messages](https://chris.beams.io/posts/git-commit/)
* [How to debug with breakpoints](https://www.youtube.com/watch?v=ZDnbBah_LRk&list=PLiQwzrQTcfRx4Yh53q79ypeIWZgY3jK0w&index=4&t=22s)
* This project uses a lot of [function pointers](https://www.cprogramming.com/tutorial/function-pointers.html) and [hash tables](https://www.youtube.com/watch?v=KyUTuwz_b7Q&list=PLiQwzrQTcfRx4Yh53q79ypeIWZgY3jK0w&index=12&t=0s), a.k.a. maps.
* [Guide to using Git](https://git-scm.com/book/en/v2)
* [Guide to unit testing in Visual Studio](https://devblogs.microsoft.com/cppblog/cpp-testing-in-visual-studio/)
* [A Successful Git Branching Model](https://nvie.com/posts/a-successful-git-branching-model/)
