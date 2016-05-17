/*
 * Cubie.cpp
 *
 *  Created on: Oct 21, 2015
 *      Author: D.J
 */

#include <string>

#include "Cubie.hpp"

using namespace std;

Cubie::Cubie(string value) : m_faces(1), m_type(KEY), m_value(value) { }

Cubie::~Cubie() { }

string Cubie::value() const {
    return m_value;
}
