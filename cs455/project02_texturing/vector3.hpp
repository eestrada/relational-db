#if !defined(VECTOR3_HPP)
#define VECTOR3_HPP

#include <ostream>

namespace cg
{

struct vector
{
    double x, y, z;
};

struct point : public vector
{
};

struct normal : public vector
{
};

struct texcoords : public vector
{
};

} //end namespace

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
