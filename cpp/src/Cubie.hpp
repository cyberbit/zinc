/*
 * Cubie.hpp
 *
 *  Created on: Oct 21, 2015
 *      Author: D.J
 */

#ifndef CUBIE_HPP_
#define CUBIE_HPP_

#include <string>

enum CubieType { KEY, EDGE, CORNER };

class Cubie {
    public:
        Cubie(std::string value);
        virtual ~Cubie();

        // Accessors
        std::string value() const;

    private:
        int m_faces; // May not be necessary if calculated from m_type
        CubieType m_type;
        std::string m_value;
};

#endif /* CUBIE_HPP_ */
