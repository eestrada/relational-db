#if !defined(VECTOR3_HPP)
#define VECTOR3_HPP

#include <ostream>
#include "hvector.hpp"
#include "image.hpp"

namespace cg
{

struct vector
{
public:
    double x, y, z;

    operator hvector() const
    {
        return this->to_hvector(0.0);
    }
protected:
    hvector to_hvector(double w) const
    {
        hvector hv;

        hv.x = this->x;
        hv.y = this->y;
        hv.z = this->z;
        hv.w = w;

        return hv;
    }
};


struct point : public vector
{
    operator hvector() const
    {
        return this->to_hvector(1.0);
    }
};

struct normal : public vector
{
};

struct texcoords : public vector
{
    const double & u() const {return x;}
    double & u() {return x;}

    const double & v() const {return y;}
    double & v() {return y;}

    const double & w() const {return z;}
    double & w() {return z;}

};

struct colorRGB : public vector
{
    operator hvector() const
    {
        return this->to_hvector(1.0);
    }

    operator colorRGBA() const
    {

        colorRGBA clr;

        clr.x = this->x;
        clr.y = this->y;
        clr.z = this->z;
        clr.w = 1.0;

        return clr;
    }

    const double & r() const {return x;}
    double & r() {return x;}

    const double & g() const {return y;}
    double & g() {return y;}

    const double & b() const {return z;}
    double & b() {return z;}
};

typedef vector vector3;
typedef point point3;
} //end namespace


cg::vector hvector_to_vector(const cg::hvector &hv)
{
    cg::vector v;

    v.x = hv.x;
    v.y = hv.y;
    v.z = hv.z;

    return v;
}

// Output convenience functions
inline std::ostream & operator<<(std::ostream &out, const cg::point &p)
{
    out << "v" << " " << p.x << " " << p.y << " " << p.z;
    return out;
}

inline std::ostream & operator<<(std::ostream &out, const cg::normal &n)
{
    out << "vn" << " " << n.x << " " << n.y << " " << n.z;
    return out;
}

inline std::ostream & operator<<(std::ostream &out, const cg::texcoords &tex)
{
    out << "vt" << " " << tex.x << " " << tex.y << " " << tex.z;
    return out;
}

#endif // end include guard
