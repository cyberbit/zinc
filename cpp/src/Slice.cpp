/*
 * Slice.cpp
 *
 *  Created on: Oct 21, 2015
 *      Author: D.J
 */

#include <vector>
#include <string>
#include <iostream>
#include <sstream>

#include "Slice.hpp"

using namespace std;

Slice::Slice(string values, int width) {
    m_width = width;

    // Storage for row
    CubieVector row;

    for (size_t i = 0; i < values.length(); ++i) {
        row.push_back(values.substr(i, 1));

        // End of row
        if ((i + 1) % width == 0) {
            m_cubies.push_back(row);
            row.clear();
        }
    }
}

Slice::Slice(CubieMatrix cubies) {
    m_width = cubies.size();
    m_cubies = cubies;
}

Slice::~Slice() { }

CubieVector Slice::row(int row) {
    return m_cubies[row];
}

bool Slice::rotate(Rotation rot) {
    switch (rot) {
        case CLOCKWISE:
            m_cubies = _reverse(_transpose(m_cubies), HORIZONTAL);

            break;
        case COUNTER_CLOCKWISE:
            m_cubies = _reverse(_transpose(m_cubies), VERTICAL);

            break;
        case HALF:
            m_cubies = _reverse(_reverse(m_cubies, HORIZONTAL), VERTICAL);

            break;
    }

    return true;
}

string Slice::format() {
    stringstream format;

    for (size_t i = 0; i < m_cubies.size(); ++i)
        format << formatRow(i) << "\n";

    return format.str();
}

CubieMatrix Slice::_transpose(CubieMatrix cubies) {
    CubieMatrix transposedCubies = cubies;

    for (size_t i = 0; i < cubies.size(); ++i)
        for (size_t j = 0; j < cubies[i].size(); ++j)
            transposedCubies[j][i] = cubies[i][j];

    return transposedCubies;
}

string Slice::formatRow(int row) {
    stringstream format;

    for (size_t i = 0; i < m_cubies[row].size(); ++i)
        format << " " << m_cubies[row][i].value();

    return format.str();
}

CubieMatrix Slice::_reverse(CubieMatrix cubies, Axis axis) {
    int width = cubies.size();
    CubieMatrix reversedCubies = cubies;

    switch (axis) {
        case HORIZONTAL:
            for (int i = 0; i < width; ++i)
                for (int j = 0; j < width; ++j)
                    reversedCubies[i][width - j - 1] = cubies[i][j];

            break;
        case VERTICAL:
            for (int i = 0; i < width; ++i)
                for (int j = 0; j < width; ++j)
                    reversedCubies[width - i - 1][j] = cubies[i][j];

            break;
    }

    return reversedCubies;
}

CubieVector Slice::column(int col) {
    return _transpose(m_cubies)[col];
}

int Slice::width() const {
    return m_width;
}

bool Slice::setRow(CubieVector row, int idx) {
    m_cubies[idx] = row;

    return true;
}

bool Slice::setColumn(CubieVector column, int idx) {
    m_cubies = _transpose(m_cubies);
    m_cubies[idx] = column;
    m_cubies = _transpose(m_cubies);

    return true;
}

std::string Slice::state() {
    stringstream format;

    for (size_t i = 0; i < m_cubies.size(); ++i)
        for (size_t j = 0; j < m_cubies[i].size(); ++j)
            format << m_cubies[i][j].value();

    return format.str();
}
