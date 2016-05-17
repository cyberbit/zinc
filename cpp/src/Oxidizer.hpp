/*
 * Oxidizer.hpp
 *
 *  Created on: Oct 28, 2015
 *      Author: D.J
 */

#ifndef OXIDIZER_HPP_
#define OXIDIZER_HPP_

#include <string>
#include <vector>

#include "RubiksCube.hpp"

class Oxidizer {
    public:
        Oxidizer(std::string key = "");
        virtual ~Oxidizer();

        // Accessors
        std::string key() const;
        int step() const;

        // Mutators
        bool step(RubiksCube &cube);
        bool setStep(int step);

        // Formatters
        Point rotationOf(Direction dir); // Returns SliceType and Rotation

    private:
        std::string m_key;
        int m_step;
};

#endif /* OXIDIZER_HPP_ */
