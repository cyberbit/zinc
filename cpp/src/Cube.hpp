/*
 * Cube.hpp
 *
 *  Created on: Oct 21, 2015
 *      Author: D.J
 */

#ifndef CUBE_HPP_
#define CUBE_HPP_

#include <string>
#include <vector>

#include "Slice.hpp"

enum Direction {
    NORTH_WEST, NORTH, NORTH_EAST, // Row 0
    WEST, ORIGIN, EAST,            // Row 1
    SOUTH_WEST, SOUTH, SOUTH_EAST  // Row 2
};

typedef std::vector<Direction> DirectionVector;

class Cube {
    public:
        Cube(std::string values, int width);
        virtual ~Cube();

        // Accessors
        Slice *slice(int slice);
        int width();
        Point indexOf(std::string value);
        std::string at(Point pt);

        // Mutators
        bool rotateView(Direction dir);

        // Formatters
        std::string format();
        std::string formatInline();

    protected:
        std::vector<Slice> m_slices;
};

#endif /* CUBE_HPP_ */
