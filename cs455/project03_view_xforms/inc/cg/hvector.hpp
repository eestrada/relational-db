#if !defined(HVECTOR_HPP)
#define HVECTOR_HPP

#include <ostream>

//#include "cg_utils.hpp"
#include "vector3.hpp"

namespace cg
{

struct hvector
{
    // Member variables
    double x, y, z, w;

    // Constructors
    hvector();
    hvector(double v);
    hvector(const vector3 &other);
    hvector(const vector3 &other, double w);
    hvector(const point3 &other);
    hvector(const hvector &other);

    // Conversion operators
    operator vector3();
    operator point3();
};

} //end namespace

std::ostream & operator<<(std::ostream &out, const cg::hvector &hv);

#endif // end include guard
