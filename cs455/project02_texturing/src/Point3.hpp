#if !defined(POINT3_HPP)
#define POINT3_HPP

#include "base_vector3.hpp"

namespace ede
{

class Point3 : public base_vector3
{
private:
    void ctorHelper();
    void dtorHelper();
};

}

#endif //finish include guard

