#include <ostream>
#include "cg/hvector.hpp"

namespace cg
{

hvector::hvector() : x(0.0),y(0.0),z(0.0),w(0.0) {}

hvector::hvector(double v) : x(v),y(v),z(v),w(v) {}

hvector::hvector(const vector3 &other) : x(other.x),y(other.y),z(other.z),w(0.0) {}

hvector::hvector(const vector3 &other, double w_in) : x(other.x),y(other.y),z(other.z),w(w_in) {}

hvector::hvector(const point3 &other) : x(other.x),y(other.y),z(other.z),w(1.0) {}

hvector::hvector(const hvector &other) : x(other.x),y(other.y),z(other.z),w(other.w) {}

hvector::operator vector3()
{
    vector3 v;
    v.x = this->x;
    v.y = this->y;
    v.z = this->z;

    return v;
}

hvector::operator point3()
{
    point3 p(vec_to_pt(this->operator vector3()));

    if(this->w != 0.0)
    {
        p.x *= this->w;
        p.y *= this->w;
        p.z *= this->w;
    }

    return p;
}

} //end namespace

std::ostream & operator<<(std::ostream &out, const cg::hvector &hv)
{
    out << "hvector" << " " << hv.x << " " << hv.y << " " << hv.z << " " << hv.w;
    return out;
}

