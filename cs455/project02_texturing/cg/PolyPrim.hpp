#if !defined(POLYPRIM_HPP)
#define POLYPRIM_HPP

#include <vector>
#include "Vertex.hpp"

namespace ede
{

class PolyPrim
{
private:
    std::vector<Vertex> vertarray;

public:
    const std::vector<Vertex>& getVertArray();
    void appendVert(const Vertex& newVert);
};

}
#endif //finish include guard

