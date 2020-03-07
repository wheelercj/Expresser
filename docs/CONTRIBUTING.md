# How to Contribute

Thanks for your interest! The main goals of this project are for contributors to learn software engineering techniques and principles, and to help them prepare for a career in software engineering or a closely related field. As such, contributions are welcome provided the following:
1. Contributors make an effort to create their contributions themselves, and only search online for answers to specific questions as a last resort. Feel free to ask for help from fellow contributors, professors, school classmates, etc.
2. Contributors help their fellow contributors understand their contributions, whether through the project [wiki](https://github.com/wheelercj/Calc/wiki), a linked guide, or how the contributions are written.
3. Contributors follow the [code of conduct](https://github.com/wheelercj/Calc/blob/master/docs/CODE_OF_CONDUCT.md).

## How to contribute code
1. Start by cloning the repository if you haven't already.
2. Find a problem to fix or feature to add that will be important to users. Looking at the project's [to do list](https://github.com/wheelercj/Calc/projects/2) or [issues](https://github.com/wheelercj/Calc/issues) might help.
3. Create a new branch with a short but descriptive name of the topic of the change(s) you will make.
4. Make the changes. Be sure to document the code with plenty of comments. Code quality should be maintained in every commit. Try to follow the project's current style.
5. When the changes are ready to be integrated into the public copy of the project, go back to the original project site and click "Fork".
6. Commit the changes. When writing the commit message:
   1. First, write a subject line that is no longer than 50 characters.
   2. Use the present tense and the imperative mood (e.g. "Add feature", not "Adds feature" or "Added feature").
   3. If there are other relevant details to include, enter a blank line after the subject and then sentences wrapped at 72 characters.
   4. Explain what the commit does and why.
7. When you're ready to submit a pull request, look through the project's [issues](https://github.com/wheelercj/Calc/issues). If you find any issues you've solved, include their numbers in the pull request description.

## How to report a bug
1. If the bug is a security vulnerability, send the bug report to stemclublavc@gmail.com instead of posting it on GitHub.
2. Search the [issues](https://github.com/wheelercj/Calc/issues) to see if someone else already reported the bug.
3. If the bug has not already been reported, [create a new bug report](https://github.com/wheelercj/Calc/issues/new?assignees=&labels=bug&template=bug_report.md&title=) with as much relevant detail as possible.

## How to request a feature or enhancement
1. Search the [issues](https://github.com/wheelercj/Calc/issues) to see if someone else already requested the feature. You can add comments to existing feature requests.
2. If the feature has not been requested, [create a new feature request](https://github.com/wheelercj/Calc/issues/new?assignees=&labels=enhancement&template=feature_request.md&title=) with as much relevant detail as possible.

## FAQs
* **Why doesn't the project use `using namespace std;`?**  
	  Programs can become complicated enough that names for objects or functions have to be reused by different namespaces. Instead of trying to predict which members of a namespace might be reused in the future, or trying to find the problem when something goes wrong, it is usually best to distinguish a namespace as a prefix, e.g. `std::cout`.
* **What does the `.hpp` filetype do?**  
	  The `.hpp` filetype is the same as `.h`. This project is following the convention that a header file without a corresponding source file will use `.hpp`.

## Suggested viewing/reading
* [Intro to GitHub and Git](https://www.youtube.com/watch?v=vR-y_2zWrIE&list=PLWKjhJtqVAbkFiqHnNaxpOPhh9tSWMXIF)
* [Guide to writing commit messages](https://chris.beams.io/posts/git-commit/)
* [How to debug with breakpoints](https://www.youtube.com/watch?v=ZDnbBah_LRk&list=PLiQwzrQTcfRx4Yh53q79ypeIWZgY3jK0w&index=4&t=22s)
* This project uses a lot of [hash tables](https://www.youtube.com/watch?v=KyUTuwz_b7Q&list=PLiQwzrQTcfRx4Yh53q79ypeIWZgY3jK0w&index=12&t=0s), a.k.a. maps.
* [Guide to using Git](https://git-scm.com/book/en/v2)
* [Branching model](https://nvie.com/posts/a-successful-git-branching-model/)
* [Guide to unit testing in Visual Studio](https://devblogs.microsoft.com/cppblog/cpp-testing-in-visual-studio/)
