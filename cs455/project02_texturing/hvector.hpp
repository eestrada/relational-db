#if !defined(HVECTOR_HPP)
#define HVECTOR_HPP

#include <ostream>
#include <vector>

namespace cg
{

struct hvector
{
    double x, y, z, w;
};

struct color : public hvector
{
    double &r, &g, &b, &a;
    color() : r(x), g(y), b(z), a(w) {}
};

} //end namespace

#endif // end include guard
