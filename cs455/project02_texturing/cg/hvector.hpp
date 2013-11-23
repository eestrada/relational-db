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

};

struct colorRGBA : public hvector
{
    const double & r() const {return x;}
    double & r() {return x;}

    const double & g() const {return y;}
    double & g() {return y;}

    const double & b() const {return z;}
    double & b() {return z;}

    const double & a() const {return w;}
    double & a() {return w;}

    std::valarray<uint8_t> to_bytes()
    {
        double r,g,b,a;
        std::valarray<uint8_t> retval(4);

        r = utils::fit(this->r(), 0.0, 1.0, 0.0, 255.0);
        retval[0] = static_cast<uint8_t>(r);

        g = utils::fit(this->g(), 0.0, 1.0, 0.0, 255.0);
        retval[1] = static_cast<uint8_t>(g);

        b = utils::fit(this->b(), 0.0, 1.0, 0.0, 255.0);
        retval[2] = static_cast<uint8_t>(b);

        a = utils::fit(this->a(), 0.0, 1.0, 0.0, 255.0);
        retval[3] = static_cast<uint8_t>(a);

        return retval;
    }
};

} //end namespace

inline std::ostream & operator<<(std::ostream &out, const cg::hvector &hv)
{
    out << "hvector" << " " << hv.x << " " << hv.y << " " << hv.z << " " << hv.w;
    return out;
}

#endif // end include guard
