/*
 * Commander.cpp
 *
 *  Created on: Nov 3, 2015
 *      Author: D.J
 */

#include "Commander.hpp"
#include "utils.hpp"

using namespace std;

Commander::Commander(string prompt) : m_prompt(prompt) { }

Commander::~Commander() { }

string Commander::prompt() {
    string cmd = get_string(m_prompt, 7);
    return cmd;
}

void Commander::loop() {
    bool stop = false;

    do {
        string readStr = this->prompt();

        if (readStr == "") continue;

        // Break loop
        else if (readStr == "exit") stop = true;
        else {
            this->parse(readStr);
        }
    } while (!stop);
}
