/*
 * Point.cpp
 *
 *  Created on: Oct 27, 2015
 *      Author: D.J
 */

#include <sstream>

#include "Point.hpp"

using namespace std;

Point::Point(vector<int> indexes) : m_indexes(indexes) { }

Point::~Point() { }

int Point::dimension() const {
    return m_indexes.size();
}

Point Point::operator-(Point p) {
    vector<int> indexes = m_indexes;

    for (int i = 0; i < dimension(); ++i)
        indexes[i] -= p.index(i);

    return Point(indexes);
}

Point Point::operator+(Point p) {
    vector<int> indexes = m_indexes;

    for (int i = 0; i < dimension(); ++i)
        indexes[i] += p.index(i);

    return Point(indexes);
}

int Point::index(int idx) const {
    return m_indexes[idx];
}

bool Point::setIndex(int idx, int value) {
    m_indexes[idx] = value;

    return true;
}

std::string Point::format() const {
    stringstream format;

    format << "(";

    for (int i = 0; i < dimension() - 1; ++i) {
        format << index(i) << ", ";
    }

    format << index(dimension() - 1) << ")";

    return format.str();
}
