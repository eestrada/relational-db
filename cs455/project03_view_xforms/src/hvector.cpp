#if !defined(HVECTOR_HPP)
#define HVECTOR_HPP

#include <ostream>
#include <vector>
#include <valarray>
#include <stdexcept>

#include "utils.hpp"

namespace cg
{

struct hvector
{
    double x, y, z, w;

    hvector dot(const hvector &other);

    hvector normalized();
};

} //end namespace

inline std::ostream & operator<<(std::ostream &out, const cg::hvector &hv)
{
    out << "hvector" << " " << hv.x << " " << hv.y << " " << hv.z << " " << hv.w;
    return out;
}

#endif // end include guard
