#pragma once

#include "DebugLogger.hpp"
#include <string>
#include <vector>
#include <sstream>

bool isNum(char ch);
bool isAlpha(char ch);
bool isOp(char ch);
int getNumSize(std::string str);
int getAlphaSize(std::string str);
int getOpSize(std::string str);
bool hasPrecedence(std::string op1, std::string op2);

void removeEdgeSpaces(std::string& str);
void validateInput(std::string& input);
void formatOutput(std::string& str, int precision);
std::vector<std::string> readParams(std::string str);
