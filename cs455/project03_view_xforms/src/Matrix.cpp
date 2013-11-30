#include "cg/Matrix.hpp"
#include "utils/exceptions.hpp"

namespace cg
{

namespace matrix
{

Mat4x4 inverted(const Mat4x4 &m)
{
    throw err::exception("Function 'Mat4x4 inverted(const Mat4x4 &m)' is not yet implemented");
    return Mat4x4();
}

Mat4x4 rotate(double x, double y, double z, double radians)
{
    throw err::exception("Function 'Mat4x4 rotate(double radians)' is not yet implemented");
    return Mat4x4();
}

Mat4x4 rotate_x(double radians)
{
    throw err::exception("Function 'Mat4x4 rotate_x(double radians)' is not yet implemented");
    return Mat4x4();
}

Mat4x4 rotate_y(double radians)
{
    throw err::exception("Function 'Mat4x4 rotate_y(double radians)' is not yet implemented");
    return Mat4x4(5.0);
}

Mat4x4 rotate_z(double radians)
{
    throw err::exception("Function 'Mat4x4 rotate_z(double radians)' is not yet implemented");
    return Mat4x4();
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

