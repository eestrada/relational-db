#if !defined(VERTEX_HPP)
#define VERTEX_HPP

#include "Point3.hpp"
#include "Vector3.hpp"

namespace ede
{

class Vertex
{
private:
    Point3 *pt;
    Vector3 *nml, *uvw;

public:
    const Point3* getPosition();
    Vector3 getNormal();
    Vector3 getUVW();
};

}
#endif //finish include guard
