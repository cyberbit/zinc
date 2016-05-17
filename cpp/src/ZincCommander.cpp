/*
 * ZincCommander.cpp
 *
 *  Created on: Nov 3, 2015
 *      Author: D.J
 */

#include <iostream>
#include <iomanip>
#include <stdexcept>

#include "ZincCommander.hpp"
#include "ZincOxide.hpp"
#include "utils.hpp"

using namespace std;

const vector<string> commands = {
    "help",
    "encode",
    "decode",
    "reset",
    "view",
    "set",
    "exit"
};

const vector<string> commandDescriptions = {
    "Show this message",
    "Encode message",
    "Decode message",
    "Reset cube to base state",
    "View option",
    "Set option",
    "Terminate program"
};

const vector<string> options = {
    "key",
    "state",
    "base_state",
    "auto_reset"
};

const vector<string> optionDescriptions = {
    "Session key",
    "Cube state",
    "Base cube state",
    "Reset cube to base state after encoding/decoding"
};

ZincCommander::ZincCommander(ZincOxide &zincOxy) : Commander("zinc > "), m_zinc(zincOxy) { }

ZincCommander::~ZincCommander() { }

bool ZincCommander::parse(string input) {
    vector<string> args = split(input);

    string cmd, verb;

    try {
        cmd = args.at(0);
        verb = args.at(1);
    } catch (const out_of_range &e) {
        verb = "";
    }

    // Trim command input
    rtrim(cmd);

    if (cmd == "exit") {
        alert("Type " + quote("exit") + " only to quit.");
    }

    else if (cmd == "help") {
        menu("These commands are available: ", commands, commandDescriptions);

        return true;
    }

    else if (cmd == "set") {
        if (verb == "") {
            alert("To set an option directly from the prompt, simply type \"set [option]\".");

            menu("These options are available: ", options, optionDescriptions);

            verb = get_string("Type an option name to set, or ENTER to cancel: ");
        }

        if (verb == "key") {
            alert("WARNING: Setting the key will force a step reset!", 14);

            // View option
            view(verb);

            string key = m_zinc.legalizeString(get_string("Enter new key for session, or ENTER to keep current: "));
            if (key != "") {
                m_zinc.resetOxy(key);
                alert("Key set to \"" + key + "\", step reset to 0.");
            }
        }

        else if (verb == "state") {
            stringstream ss;
            ss << "WARNING: The state string must contain all of the characters included in\n"
               << "     the current alphabet:\n\n"
               << "     " << ALPHABET << "\n\n"
               << "     Note that this WILL NOT BE VALIDATED, so invalid input WILL cause a crash!\n"
               << "     Ideally, you should only use an exported state string (\"view state\")\n"
               << "     to avoid typing errors.";

            alert(ss.str(), 14);

            // View option
            view(verb);

            bool cancel = false;

            string state = "";
            do {
                state = m_zinc.legalizeString(get_string("Enter new state string, or ENTER to cancel: "));

                if (state == "") cancel = true;
            } while (state.length() != 27 && !cancel);

            int step = -1;
            if (!cancel) {
                step = get_int("Enter step, or -1 to cancel: ");
                clear_line();

                if (step < 0) cancel = true;
            }

            if (!cancel) {
                m_zinc.setState(state, step);

                alert("State set.");
            }
        }

        else if (verb == "base_state") {
            stringstream ss;
            ss << "WARNING: The state string must contain all of the characters included in\n"
               << "     the current alphabet:\n\n"
               << "     " << ALPHABET << "\n\n"
               << "     Note that this WILL NOT BE VALIDATED, so invalid input WILL cause a crash!\n"
               << "     Ideally, you should only use an exported state string (\"view state\")\n"
               << "     to avoid typing errors.";

            alert(ss.str(), 14);

            // View option
            view(verb);

            bool cancel = false;

            string state = "";
            do {
                state = m_zinc.legalizeString(get_string("Enter new base state string, or ENTER to cancel: "));

                if (state == "") cancel = true;
            } while (state.length() != 27 && !cancel);

            if (!cancel) {
                m_zinc.setBaseState(state);

                alert("Base state set.");
            }
        }

        else if (verb == "auto_reset") {
            // View option
            view(verb);

            string input = "x";
            do {
                input = upperstring(get_string("Auto reset cube state after encoding/decoding? (y/n, or ENTER to cancel)"));
            } while (input != "Y" && input != "N" && input != "");

            if (input == "Y") {
                m_zinc.setAutoReset(true);

                alert("Auto reset ENABLED.");
            }
            else if (input == "N") {
                m_zinc.setAutoReset(false);

                alert("Auto reset DISABLED.");
            }
        }

        else if (verb != "") {
            error("Unknown option " + quote(verb));
        }
    }

    else if (cmd == "view") {
        if (verb == "") {
            alert("To view an option directly from the prompt, simply type \"view [option]\".");

            menu("These options are available: ", options, optionDescriptions);

            verb = get_string("Type an option name to view, or ENTER to cancel: ");
        }

        view(verb);
    }

    else if (cmd == "reset") {
        m_zinc.resetOxy(m_zinc.oxy().key());
        m_zinc.resetCube();

        alert("State reset.");

        return true;
    }

    else if (cmd == "flags") {
        return true;
    }

    else if (cmd == "encode") {
        string msg = m_zinc.legalizeString(get_string("Type message to encode, or ENTER to cancel: "));

        if (msg != "") {
            string encoded = m_zinc.encode(msg);

            cout << "Your encoded message is below:\n";
            cout << encoded << "\n";
        }

        return true;
    }

    else if (cmd == "decode") {
        string encoded = m_zinc.legalizeString(get_string("Type message to decode, or ENTER to cancel: "));

        if (encoded != "") {
            string decoded = m_zinc.decode(encoded);

            cout << "Your decoded message is below:\n";
            cout << decoded << "\n";
        }

        return true;
    }

    else {
        error("Unknown command: " + quote(cmd));
        menu("These commands are available: ", commands, commandDescriptions);
    }

    return false;
}

bool ZincCommander::view(string option) {
    if (option == "key") {
        cout << "Current key is " << quote(m_zinc.oxy().key()) << ".\n";
    }

    else if (option == "state") {
        cout << "Current state:\n"
             << "   Step: " << m_zinc.oxy().step() << "\n"
             << "   State: " << m_zinc.cube().formatInline() << "\n";
    }

    else if (option == "base_state") {
        cout << "Base state:\n"
             << "   State: " << m_zinc.baseState() << "\n";
    }

    else if (option == "auto_reset") {
        string enabled = m_zinc.autoReset() ? "ENABLED" : "DISABLED";

        cout << "Automatic cube state reset is currently " << enabled << ".\n";
    }

    else if (option != "") {
        error("Unknown option " + quote(option));

        return false;
    }

    return true;
}
