/*
 * Slice.hpp
 *
 *  Created on: Oct 21, 2015
 *      Author: D.J
 */

#ifndef SLICE_HPP_
#define SLICE_HPP_

#include <string>
#include <vector>

#include "Cubie.hpp"
#include "Point.hpp"

typedef std::vector<Cubie> CubieVector;
typedef std::vector<CubieVector> CubieMatrix;

enum Rotation { CLOCKWISE, COUNTER_CLOCKWISE, HALF };
enum Axis { HORIZONTAL, VERTICAL };

class Slice {
    public:
        // Class methods
        Slice(std::string values, int width);
        Slice(CubieMatrix cubies);
        virtual ~Slice();

        // Accessors
        int width() const;
        CubieVector row(int row);
        CubieVector column(int column);

        // Mutators
        bool setRow(CubieVector row, int idx);
        bool setColumn(CubieVector column, int idx);
        bool rotate(Rotation rot = CLOCKWISE); // Rotate slice

        // Formatters
        std::string formatRow(int row);
        std::string format(); // Returns string of values
        std::string state(); // Returns slice state

        // Helpers
        static CubieMatrix _transpose(CubieMatrix cubies);
        static CubieMatrix _reverse(CubieMatrix cubies, Axis axis);

    private:
        int m_width; // Slice width (default is 3, all slices in Cube should be same width)
        CubieMatrix m_cubies; // Cubies in slice
};

#endif /* SLICE_HPP_ */
