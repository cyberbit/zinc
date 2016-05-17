/*
 * Commander.hpp
 *
 *  Created on: Nov 3, 2015
 *      Author: D.J
 */

#ifndef COMMANDER_HPP_
#define COMMANDER_HPP_

#include "rlutil.h"

#include <vector>
#include <string>

class Commander {
    public:
        Commander(std::string prompt = "> ");
        virtual ~Commander();

        // Input
        std::string prompt();
        void loop();

        // Virtuals
        virtual bool parse(std::string cmd) = 0;

    private:
        std::string m_prompt;
        std::vector<std::string> m_flags;
};

#endif /* COMMANDER_HPP_ */
