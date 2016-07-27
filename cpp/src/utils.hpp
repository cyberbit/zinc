/**
 * utils.hpp
 *
 *  Created on: Sep 6, 2015
 *      Author: Daniel Marcolesco, x293z245
 *  Assignment: 1
 */

#ifndef UTILS_HPP_
#define UTILS_HPP_

//#include <iostream>
#include <vector>
#include <string>
#include <iomanip>

// Flags
extern const bool debug;
const int MAX_INPUT = 20;

// Unit testing
//std::string error(std::string msg, std::string prefix = "** ERROR: ", bool newline = false);
std::string _assert(bool check, std::string exp);

// Output
void header(std::string file);
int error(std::string msg, bool fatal = false, bool negateFatal = false);
void alert(std::string msg, int color = 15);
void console_pause();

// Input
int get_int(std::string prompt);
long get_long(std::string prompt);
float get_float(std::string prompt);
double get_double(std::string prompt);
std::string get_string(std::string prompt, int color = 15);
void clear_line();

// Formatting
void rtrim(std::string &s);
std::string upperstring(std::string s);
std::string quote(std::string s);
std::vector<std::string> split(std::string s);
void menu(std::string msg, std::vector<std::string> items, std::vector<std::string> list);

#endif /* UTILS_HPP_ */
