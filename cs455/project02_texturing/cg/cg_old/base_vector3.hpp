#if !defined(BASE_VECTOR3_HPP)
#define BASE_VECTOR3_HPP

#include "Matrix4x4.hpp"

namespace ede
{

class base_vector3
{
public:
    float x,y,z;
protected:
    float w;

public:
    virtual base_vector3 operator+(const Matrix4x4& m);

    virtual base_vector3 operator+(const base_vector3& v);

    virtual base_vector3 operator-(const base_vector3& v);

    virtual base_vector3 operator*(const base_vector3& v);

    virtual base_vector3 operator*(float f);
};

}

#endif //finish include guard
