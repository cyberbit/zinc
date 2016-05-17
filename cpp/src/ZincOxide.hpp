/*
 * ZincOxide.hpp
 *
 *  Created on: Oct 26, 2015
 *      Author: D.J
 */

#ifndef ZINCOXIDE_HPP_
#define ZINCOXIDE_HPP_

#include <string>

#include "RubiksCube.hpp"
#include "Oxidizer.hpp"

const std::string ALPHABET = "ABCDEFGHIJKLM/NOPQRSTUVWXYZ";
const int NULL_IDX = 13; // Index of character in ALPHABET which is used to replace invalid characters

typedef std::vector<Point> PointVector;

class ZincOxide {
    public:
        ZincOxide(std::string key);
        virtual ~ZincOxide();

        // Accessors
        RubiksCube cube();
        Oxidizer oxy();
        bool autoReset();
        std::string baseState();

        // Mutators
        std::string tests();
        bool resetOxy(std::string key);
        bool resetCube();
        bool setAutoReset(bool value);
        bool setState(std::string state, int step);
        bool setBaseState(std::string state);

        // Encoders
        std::string encode(std::string msg);

        // Decoders
        std::string decode(std::string code);

        // Formatters
        std::string formatPoints(PointVector points);
        std::string translatePoints(RubiksCube state, PointVector points);
        std::string legalizeString(std::string str);

    private:
        std::string m_base_state;
        RubiksCube m_cube;
        Oxidizer m_oxy;
        bool m_reset;
};

#endif /* ZINCOXIDE_HPP_ */
