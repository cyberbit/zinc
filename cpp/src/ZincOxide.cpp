/*
 * ZincOxide.cpp
 *
 *  Created on: Oct 26, 2015
 *      Author: D.J
 */

#include <iostream>
#include <sstream>

#include "ZincOxide.hpp"
#include "utils.hpp"

using namespace std;

ZincOxide::ZincOxide(string key) : m_base_state(ALPHABET), m_cube(m_base_state), m_oxy(key), m_reset(true) { }

ZincOxide::~ZincOxide() { }

string ZincOxide::encode(std::string msg) {
    RubiksCube state(m_cube);
    PointVector points;

    // Normalize first letter and step cube
    string prev = msg.substr(0, 1);
    points.push_back(m_cube.normalizePoint(m_cube.indexOf(prev)));
    m_oxy.step(m_cube);

    // Normalize distance between letter pairs and step cube
    for (size_t i = 1; i < msg.length(); ++i) {
        points.push_back(m_cube.normalizePoint(m_cube.indexOf(msg.substr(i, 1)) - m_cube.indexOf(prev)));
        prev = msg.substr(i, 1);
        m_oxy.step(m_cube);
    }

    // Translate points from normals to characters in original cube
    string translation = translatePoints(state, points);

    // Reset state, if needed
    if (m_reset) {
        resetOxy(m_oxy.key());
        resetCube();
    }

    return translation;
}

string ZincOxide::formatPoints(PointVector points) {
    stringstream format;

    for (size_t i = 0; i < points.size(); ++i) {
        format << " " << points[i].format();
    }

    return format.str();
}

string ZincOxide::decode(std::string code) {
    RubiksCube state(m_cube);
    PointVector points;
    PointVector msgPoints;

    stringstream msg;

    // Find index of letters in original cube
    for (size_t i = 0; i < code.length(); ++i) {
        points.push_back(state.centralizePoint(state.indexOf(code.substr(i, 1))));
    }

    // Denormalize first letter and step cube
    string prev = m_cube.at(m_cube.denormalizePoint(points[0]));
    msg << prev;
    m_oxy.step(m_cube);

    // Wrap addition of previous letter's new index and next point
    for (size_t i = 1; i < points.size(); ++i) {
        prev = m_cube.at(m_cube.wrapPoint(m_cube.indexOf(prev) + points[i]));
        msg << prev;
        m_oxy.step(m_cube);
    }

    string decoded = msg.str();

    // Reset state, if needed
    if (m_reset) {
        resetOxy(m_oxy.key());
        resetCube();
    }

    return decoded;
}

string ZincOxide::translatePoints(RubiksCube state, PointVector points) {
    stringstream translation;

    // Convert points
    for (size_t i = 0; i < points.size(); ++i) {
        Point *pt = &points[i];

        for (int j = 0; j < pt->dimension(); ++j)
            pt->setIndex(j, pt->index(j) + 1);
    }

    for (size_t i = 0; i < points.size(); ++i) {
        translation << state.at(points[i]);
    }

    return translation.str();
}

bool ZincOxide::resetOxy(string key) {
    m_oxy = Oxidizer(key);

    return true;
}

Oxidizer ZincOxide::oxy() {
    return m_oxy;
}

RubiksCube ZincOxide::cube() {
    return m_cube;
}

bool ZincOxide::resetCube() {
    m_cube = RubiksCube(m_base_state);

    return true;
}

string ZincOxide::legalizeString(string str) {
    // Uppercase string
    str = upperstring(str);

    // Replace invalid characters with ALPHABET[NULL_IDX]
    for (size_t i = 0; i < str.length(); ++i) {
        if (ALPHABET.find(str[i]) == string::npos) {
            str[i] = ALPHABET[NULL_IDX];
        }
    }

    return str;
}

bool ZincOxide::setAutoReset(bool value) {
    m_reset = value;

    return true;
}

bool ZincOxide::autoReset() {
    return m_reset;
}

bool ZincOxide::setState(string state, int step) {
    m_cube = RubiksCube(state);
    m_oxy.setStep(step);

    return true;
}

bool ZincOxide::setBaseState(std::string state) {
    m_base_state = state;

    return true;
}

string ZincOxide::baseState() {
    return m_base_state;
}
