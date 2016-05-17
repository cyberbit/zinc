/*
 * ZincCommander.hpp
 *
 *  Created on: Nov 3, 2015
 *      Author: D.J
 */

#ifndef ZINCCOMMANDER_HPP_
#define ZINCCOMMANDER_HPP_

#include "Commander.hpp"
#include "ZincOxide.hpp"

class ZincCommander: public Commander {
    public:
        ZincCommander(ZincOxide &zincOxy);
        virtual ~ZincCommander();

        // Parsers
        bool parse(std::string cmd);

    private:
        ZincOxide &m_zinc;

        // Options
        bool view(std::string option);
};

#endif /* ZINCCOMMANDER_HPP_ */
