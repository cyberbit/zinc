/*
 * RubiksCube.cpp
 *
 *  Created on: Oct 23, 2015
 *      Author: D.J
 */

#include <iostream>
#include <cmath>

#include "RubiksCube.hpp"

using namespace std;

RubiksCube::RubiksCube(string values) : Cube(values, 3) { }

RubiksCube::~RubiksCube() { }

bool RubiksCube::rotateSlice(SliceType type, Rotation rot) {
    Slice temp("000000000", 3);

    switch (type) {
        // Slice 0, 1, 2
        case FRONT:
        case CROSS:
        case BACK:
            slice(typeIndex(type))->rotate(rot);
            break;

        // Column 0, 1, 2
        case LEFT:
        case PIECE:
        case RIGHT:
            temp = makeSlice(VERTICAL, typeIndex(type));

            temp.rotate(rot);

            // Iterate slices and set columns on each
            for (int i = 0; i < width(); ++i)
                slice(i)->setColumn(temp.column(i), typeIndex(type));

            break;

        // Row 0, 1, 2
        case TOP:
        case MIDDLE:
        case GROUND:
            temp = makeSlice(HORIZONTAL, typeIndex(type));

            temp.rotate(rot);

            // Iterate slices and set rows on each
            for (int i = 0; i < width(); ++i)
                slice(i)->setRow(temp.row(i), typeIndex(type));

            break;
    }

    return true;
}

int RubiksCube::typeIndex(SliceType type) {
    switch (type) {
        case FRONT:
        case CROSS:
        case BACK:
            return type - FRONT;
            break;

        case LEFT:
        case PIECE:
        case RIGHT:
            return type - LEFT;
            break;

        case TOP:
        case MIDDLE:
        case GROUND:
            return type - TOP;
            break;
    }

    return -1;
}

Direction RubiksCube::directionOf(string value) {
    Point index = indexOf(value);
    int row = index.index(1);
    int col = index.index(2);
    int dir = -1;

    switch (row) {
        case 0:
            dir = col + NORTH_WEST;
            break;
        case 1:
            dir = col + WEST;
            break;
        case 2:
            dir = col + SOUTH_WEST;
            break;
    }

    return static_cast<Direction>(dir);
}

string RubiksCube::formatDirection(Direction dir) {
    string labels[9] = {
        "NORTH_WEST", "NORTH", "NORTH_EAST",
        "WEST", "ORIGIN", "EAST",
        "SOUTH_WEST", "SOUTH", "SOUTH_EAST"
    };

    return labels[dir];
}

Point RubiksCube::normalizePoint(Point pt) {
    for (int i = 0; i < pt.dimension(); ++i) {
        int idx = pt.index(i);

        if (abs(idx) == 2) {
            pt.setIndex(i, (idx == 2) ? -1 : 1);
        }
    }

    return pt;
}

Point RubiksCube::wrapPoint(Point pt) {
    int dim = pt.dimension();

    for (int i = 0; i < dim; ++i) {
        int idx = pt.index(i);

        if (idx >= dim) pt.setIndex(i, idx % dim);
        else if (idx < 0) pt.setIndex(i, idx + dim);
    }

    return pt;
}

Slice RubiksCube::makeSlice(Axis axis, int idx) {
    CubieMatrix cubies;

    switch (axis) {
        case HORIZONTAL:
            // Add rows
            for (int i = 0; i < width(); ++i)
                cubies.push_back(slice(i)->row(idx));

            break;
        case VERTICAL:
            // Add columns as rows
            for (int i = 0; i < width(); ++i)
                cubies.push_back(slice(i)->column(idx));

            // Transpose
            cubies = Slice::_transpose(cubies);

            break;
    }

    return Slice(cubies);
}

Point RubiksCube::centralizePoint(Point pt) {
    for (int i = 0; i < pt.dimension(); ++i) {
        pt.setIndex(i, pt.index(i) - 1);
    }

    return pt;
}

Point RubiksCube::denormalizePoint(Point pt) {
    for (int i = 0; i < pt.dimension(); ++i)
        if (pt.index(i) == -1) pt.setIndex(i, 2);

    return pt;
}
