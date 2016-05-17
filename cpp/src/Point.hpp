/*
 * Point.hpp
 *
 *  Created on: Oct 27, 2015
 *      Author: D.J
 */

#ifndef POINT_HPP_
#define POINT_HPP_

#include <vector>
#include <string>

class Point {
    public:
        Point(std::vector<int> indexes);
        virtual ~Point();

        // Operators
        Point operator-(Point p);
        Point operator+(Point p);

        // Accessors
        int dimension() const;
        int index(int idx) const;

        // Mutators
        bool setIndex(int idx, int value);

        // Formatters
        std::string format() const;

    private:
        std::vector<int> m_indexes;
};

#endif /* POINT_HPP_ */
