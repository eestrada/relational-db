#if !defined(OBJECT_HPP)
#define OBJECT_HPP
#include <memory>

#include "Matrix4x4.hpp"
#include "Geometry.hpp"

namespace scene
{

class object
{
public: // Functions
    object() : transform(1.0f), parent(NULL){}
    cg::Mat4x4 getFinalXform()
    {
        cg::Mat4x4 retval = transform;
        if (parent != NULL)
        {
            cg::Mat4x4 pxform = parent->getFinalXform();
            return retval * pxform;
        }
        else
        {
            return transform;
        }
    }

    virtual void draw() = 0;

public: // Variables
    cg::Mat4x4 transform;
    object *parent;

protected: // Functions

protected: // Variables

};

class geo : public object
{
public:
    std::shared_ptr<cg::Geometry> g;
    void draw();

protected:

};

class null : public object
{
    virtual void draw(){}
};

class camera : public object
{
    virtual void draw(){}
};

class light : public object
{
    virtual void draw(){}
};

}
#endif //finish include guard

