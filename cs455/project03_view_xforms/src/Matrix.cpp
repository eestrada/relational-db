#include "cg/Matrix.hpp"
#include "utils/exceptions.hpp"
#include <iostream>
#include <cmath>

namespace cg
{

namespace matrix
{

Mat4x4 inverted(const Mat4x4 &m)
{
    throw err::not_implemented("Mat4x4 inverted(const Mat4x4 &m)");
    return Mat4x4();
}

Mat4x4 rotate(double x, double y, double z, double radians)
{
    throw err::not_implemented("Mat4x4 rotate(double x, double y, double z, double radians)");
    return Mat4x4();
}

Mat4x4 rotate_x(double radians)
{
    Mat4x4 tmp;
    tmp.at(1,1) = std::cos(radians);
    tmp.at(2,2) = std::cos(radians);
    tmp.at(1,2) = std::sin(radians);
    tmp.at(2,1) = -std::sin(radians);
    //std::cerr << "The Mat4x4 rotated along the X axis is \n" << tmp << std::endl;
    return tmp;
}

Mat4x4 rotate_y(double radians)
{
    Mat4x4 tmp;
    tmp.at(0,0) = std::cos(radians);
    tmp.at(2,2) = std::cos(radians);
    tmp.at(2,0) = std::sin(radians);
    tmp.at(0,2) = -std::sin(radians);
    //std::cerr << "The Mat4x4 rotated along the Y axis is \n" << tmp << std::endl;
    return tmp;
}

Mat4x4 rotate_z(double radians)
{
    Mat4x4 tmp;
    tmp.at(0,0) = std::cos(radians);
    tmp.at(1,1) = std::cos(radians);
    tmp.at(1,0) = -std::sin(radians);
    tmp.at(0,1) = std::sin(radians);
    //std::cerr << "The Mat4x4 rotated along the Y axis is \n" << tmp << std::endl;
    return tmp;
}

Mat4x4 translate(double x, double y, double z)
{
    Mat4x4 tmp;

    tmp.at(3, 0) = x;
    tmp.at(3, 1) = y;
    tmp.at(3, 2) = z;

    return tmp;
}

Mat4x4 scale(double x, double y, double z)
{
    Mat4x4 tmp;

    tmp.at(0, 0) = x;
    tmp.at(1, 1) = y;
    tmp.at(2, 2) = z;

    return tmp;
}

Mat4x4 uniform_scale(double s)
{
    return scale(s,s,s);
}

}

}

