/*
 * Oxidizer.cpp
 *
 *  Created on: Oct 28, 2015
 *      Author: D.J
 */

#include "Oxidizer.hpp"

using namespace std;

Oxidizer::Oxidizer(string key) : m_key(key), m_step(0) { }

Oxidizer::~Oxidizer() { }

bool Oxidizer::step(RubiksCube &cube) {
    int idx = m_step % m_key.length();

    // Grab slice and rotation for next letter of key
    Point sliceRotation = rotationOf(cube.directionOf(m_key.substr(idx, 1)));

    // Cast types
    SliceType type = static_cast<SliceType>(sliceRotation.index(0));
    Rotation rot = static_cast<Rotation>(sliceRotation.index(1));

    cube.rotateSlice(type, rot);

    // Increment step
    ++m_step;

    return true;
}

int Oxidizer::step() const {
    return m_step;
}

bool Oxidizer::setStep(int step) {
    if (step >= 0) {
        m_step = step;

        return true;
    }

    return false;
}

Point Oxidizer::rotationOf(Direction dir) {
    vector<int> sliceRotation;

    SliceType type;
    Rotation rot;

    switch (dir) {
        case ORIGIN:
            type = FRONT;
            rot = CLOCKWISE;
            break;
        case NORTH:
        case NORTH_EAST:
            type = TOP;
            rot = (dir == NORTH) ? COUNTER_CLOCKWISE : CLOCKWISE; // NORTH_EAST
            break;
        case EAST:
        case SOUTH_EAST:
            type = RIGHT;
            rot = (dir == EAST) ? CLOCKWISE : COUNTER_CLOCKWISE; // SOUTH_EAST
            break;
        case SOUTH:
        case SOUTH_WEST:
            type = GROUND;
            rot = (dir == SOUTH) ? CLOCKWISE : COUNTER_CLOCKWISE; // SOUTH_WEST
            break;
        case WEST:
        case NORTH_WEST:
            type = LEFT;
            rot = (dir == WEST) ? COUNTER_CLOCKWISE : CLOCKWISE; // NORTH_WEST
            break;
    }

    sliceRotation.push_back(type);
    sliceRotation.push_back(rot);

    return Point(sliceRotation);
}

std::string Oxidizer::key() const {
    return m_key;
}
