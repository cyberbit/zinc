//============================================================================
// Name        : zinc.cpp
// Author      : Daniel Marcolesco, x293z245
// Assignment  : CS 411 Project - Zinc
// Version     : v.1
// Description : Zinc is a text encryption engine.
// Resources   : Colors in utils.cpp use rlutil.h, by tapio
//               (https://github.com/tapio/rlutil). Public license.
//============================================================================

#include <iostream>
#include <string>
#include <sstream>

#include "utils.hpp"
#include "ZincOxide.hpp"
#include "ZincCommander.hpp"

using namespace std;

// Required for utils.hpp
const bool debug = true;

// Version string
const string VERSION = "v1.0";

// Default key
const string DEFAULT_KEY = "ZINCISNOTCOPPER";

int main() {
    stringstream title;

    title << "::::::::: ::::::::::: ::::    :::  :::::::: \n"
          << "     :+:      :+:     :+:+:   :+: :+:    :+:\n"
          << "    +:+       +:+     :+:+:+  +:+ +:+       \n"
          << "   +#+        +#+     +#+ +:+ +#+ +#+       \n"
          << "  +#+         +#+     +#+  +#+#+# +#+       \n"
          << " #+#          #+#     #+#   #+#+# #+#    #+#\n"
          << "######### ########### ###    ####  ######## \n\n"
          << "================= Zinc v.1 =================\n"
          << "==       Written by D.J. Marcolesco       ==\n"
          << "==           cyberbit.github.io           ==\n"
          << "============================================\n\n";

    // Program header
    rlutil::setColor(11);
    cout << title.str();
    rlutil::setColor(15);

    ZincOxide zinc(DEFAULT_KEY);
    ZincCommander com(zinc);

	// Set key
	string key = zinc.legalizeString(get_string("Enter key for session (press ENTER to use default): "));
	if (key != "") {
        zinc.resetOxy(key);
        alert("Key set to " + quote(key) + ".");
	}

	// Initialize program loop
	com.loop();

	return 0;
}
