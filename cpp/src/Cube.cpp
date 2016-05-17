/*
 * Cube.cpp
 *
 *  Created on: Oct 21, 2015
 *      Author: D.J
 */

#include <iostream>
#include <sstream>

#include "Cube.hpp"

using namespace std;

Cube::Cube(string values, int width) {
    int area = width * width;

    for (size_t i = 0; i < values.length(); i += area) {
        m_slices.push_back(Slice(values.substr(i, area), width));
    }
}

Cube::~Cube() { }

std::string Cube::at(Point pt) {
    int x = pt.index(0),
        y = pt.index(1),
        z = pt.index(2);

    return slice(x)->row(y)[z].value();
}

bool Cube::rotateView(Direction dir) {
    /*switch (dir) {
        case
    }*/

    return true;
}

string Cube::format() {
    stringstream format;

    for (int i = 0; i < width(); ++i) { // i = row index
        for (int j = 0; j < width(); ++j) // j = slice index
            format << slice(j)->formatRow(i) << "  ";

        format << "\n";
    }

    return format.str();
}

Slice *Cube::slice(int slice) {
    return &m_slices[slice];
}

int Cube::width() {
    return slice(0)->width();
}

Point Cube::indexOf(std::string value) {
    CubieVector row;
    vector<int> indexes;

    // Storage for short circuit state
    bool found = false;

    // Iterate slices
    for (int i = 0; i < width(); ++i) {
        if (found) break;

        // Iterate rows
        for (int j = 0; j < width(); ++j) {
            if (found) break;

            row = slice(i)->row(j);

            // Iterate cubies
            for (int k = 0; k < width(); ++k) {
                // Found value
                if (row[k].value() == value) {
                    // Store indexes
                    indexes.push_back(i);
                    indexes.push_back(j);
                    indexes.push_back(k);

                    // Break out of loop
                    found = true;
                    break;
                }
            }
        }
    }

    return Point(indexes);
}

string Cube::formatInline() {
    stringstream format;
    for (int i = 0; i < width(); ++i)
        format << slice(i)->state();

    return format.str();
}
