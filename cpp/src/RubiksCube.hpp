/*
 * RubiksCube.hpp
 *
 *  Created on: Oct 23, 2015
 *      Author: D.J
 */

#ifndef RUBIKSCUBE_HPP_
#define RUBIKSCUBE_HPP_

#include <string>

#include "Cube.hpp"

enum SliceType {
    FRONT, CROSS, BACK, // Slice 0, 1, 2
    LEFT, PIECE, RIGHT, // Column 0, 1, 2 from slice 0, 1, 2
    TOP, MIDDLE, GROUND // Row 0, 1, 2 from slice 0, 1, 2
};

class RubiksCube: public Cube {
    public:
        RubiksCube(std::string values);
        virtual ~RubiksCube();

        // Accessors
        static int typeIndex(SliceType type);
        Direction directionOf(std::string value);

        // Mutators
        bool rotateSlice(SliceType type, Rotation rot);

        // Formatters
        std::string formatDirection(Direction dir);
        Point normalizePoint(Point pt);
        Point denormalizePoint(Point pt);
        Point centralizePoint(Point pt);
        Point wrapPoint(Point pt);

    private:
        Slice makeSlice(Axis axis, int index);
};

#endif /* RUBIKSCUBE_HPP_ */
