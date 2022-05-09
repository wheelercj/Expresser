#pragma once

#include "DebugLogger.hpp"
#include <string>
#include <vector>
#include <sstream>

bool is_num(char ch);
bool is_alpha(char ch);
bool is_op(char ch);
int get_num_size(std::string str);
int get_alpha_size(std::string str);
int get_op_size(std::string str);
bool has_precedence(std::string op1, std::string op2);

void remove_edge_spaces(std::string& str);
void validate_input(std::string& input);
void format_global_output(std::string& str, int precision);
std::vector<std::string> read_params(std::string str);
