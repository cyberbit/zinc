/**
 * utils.cpp
 *
 *  Created on: Sep 6, 2015
 *      Author: Daniel Marcolesco, x293z245
 *  Assignment: 2
 */

#include <ctime>
#include <cstring>
#include <iostream>
#include <cstdlib>
#include <sstream>
#include <iterator>

#include "rlutil.h"

#include "utils.hpp"

using namespace std;

/**
 * Output
 */

// Output program header
void header(string file = "Unknown program") {
    // Program header
    time_t today = time(NULL);
    cout << file << " - " << asctime(localtime(&today)) << endl;
}

// Pause console
void pause() {
    cin.clear();
    cout << "\nPress any key to continue...";
    cin.ignore();
}

/**
 * Input
 */

// Read an integer
int get_int(string prompt) {
    char str[MAX_INPUT];
    int num;
    bool valid_number = true;
    char *end_ptr;
    do {
        if (!valid_number) error("You must enter a number.");
        cout << prompt;
        cin >> str;
        num = strtol(str, &end_ptr, 10);

        if (end_ptr != (str + strlen(str))) valid_number = false;
        else valid_number = true;
    } while (!valid_number);

    return num;
}

// Read a long
long get_long(string prompt) {
    char str[MAX_INPUT];
    long num;
    bool valid_number = true;
    char *end_ptr;
    do {
        if (!valid_number) error("You must enter a number.");
        cout << prompt;
        cin >> str;
        num = strtol(str, &end_ptr, 10);

        if (end_ptr != (str + strlen(str))) valid_number = false;
        else valid_number = true;
    } while (!valid_number);

    return num;
}

// Read a float
float get_float(string prompt) {
    char str[MAX_INPUT];
    float num;
    bool valid_number = true;
    char *end_ptr;
    do {
        if (!valid_number) error("You must enter a number.");
        cout << prompt;
        cin >> str;
        num = strtof(str, &end_ptr);

        if (end_ptr != (str + strlen(str))) valid_number = false;
        else valid_number = true;
    } while (!valid_number);

    return num;
}

// Read a double
double get_double(string prompt) {
    char str[MAX_INPUT];
    double num;
    bool valid_number = true;
    char *end_ptr;
    do {
        if (!valid_number) error("You must enter a number.");
        cout << prompt;
        cin >> str;
        num = strtod(str, &end_ptr);

        if (end_ptr != (str + strlen(str))) valid_number = false;
        else valid_number = true;
    } while (!valid_number);

    return num;
}

// Read a string. Colors from rlutil (https://github.com/tapio/rlutil)
string get_string(string prompt, int color) {
    string str;
    rlutil::setColor(color);
    cout << prompt;
    rlutil::setColor(15);
    getline(cin, str);

    return str;
}

// Clear line
void clear_line() {
    // Storage for next character
    char next;

    // Iterate input buffer through a newline
    do cin.get(next);
    while (next != '\n');
}

// Trim whitespace from end of string
void rtrim(string &s) {
    s.erase(s.find_last_not_of(" \n\r\t") + 1);
}

/*string error(string msg, string prefix, bool newline) {
	stringstream stream;

	if (newline) stream << "\n\n";

	stream << prefix << msg;

	if (newline) stream << "\n\n";

	return stream.str();
}*/

// Generate error. Colors from rlutil (https://github.com/tapio/rlutil)
int error(string msg, bool fatal, bool negateFatal) {
    // Fatal error
    if (fatal) {
        alert("FATAL ERROR: " + msg + ", terminating program", 12);
        rlutil::setColor(15);
        return negateFatal ? -1 : 0;
    }

    // Normal error
    else {
        alert("ERROR: " + msg, 12);
        return 1;
    }
}

string _assert(bool check, string exp) {
	stringstream stream;

	if (debug) {
		if (check) stream << "Assert success: " << exp << "\n";
		else stream << error("Assert failure: " + exp + "\n");
	} else {
		if (check) stream << "done.\n";
		else stream << error("Assert failure!\n");
	}

	return stream.str();
}

string upperstring(string s) {
    for (size_t i = 0; i < s.length(); ++i) {
        s[i] = toupper(s[i]);
    }

    return s;
}

// Alert the user. Colors from rlutil (https://github.com/tapio/rlutil)
void alert(string msg, int color) {
    rlutil::setColor(color);
    cout << "\n *** " << msg << "\n\n";
    rlutil::setColor(15);
}

string quote(string s) {
    return "\"" + s + "\"";
}

// Split string (via http://stackoverflow.com/a/5607650/3402854)
vector<string> split(string s) {
    istringstream iss(s);

    vector<string> strings {
        istream_iterator<string>{iss},
        istream_iterator<string>{}
    };

    return strings;
}

void menu(std::string msg, std::vector<std::string> items, std::vector<std::string> list) {
    if (items.size() != list.size()) {
        error("UTILS: Menu parameters not the same size!");
        return;
    }

    cout << msg << "\n";

    // Grab max item length
    size_t max = 0;
    for (size_t i = 0; i < items.size(); ++i) {
        if (items[i].length() > max) max = items[i].length();
    }

    for (size_t i = 0; i < items.size(); ++i) {
        cout << "   " << setw(max) << items[i] << "  " << list[i] << "\n";
    }
}
