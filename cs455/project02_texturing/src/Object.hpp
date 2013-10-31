#if !defined(OBJECT_HPP)
#define OBJECT_HPP
#include <Matrix4x4.hpp>
#include <Geometry.hpp>

namespace scene
{

class object
{
public: // Functions
    object() : transform(1.0f), parent(NULL){}

public: // Variables

protected: // Functions
    cg::Mat4x4 getFinalXform();

protected: // Variables
    cg::Mat4x4 transform;
    object *parent;

};

class geo : public object
{
public:
    void setGeo(cg::Geometry *gin);
    cg::Geometry* getGeo();
    bool clearGeo();
    void draw();

protected:
    cg::Geometry *g;

};

class null : public object
{
};

class cam : public object
{
};

class light : public object
{
};

}
#endif //finish include guard

