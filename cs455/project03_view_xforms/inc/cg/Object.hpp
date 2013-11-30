#if !defined(OBJECT_HPP)
#define OBJECT_HPP
#include <memory>
#include <GL/gl.h>

#include "Matrix.hpp"
#include "Geometry.hpp"

namespace obj
{

class object
{
public: // Functions
    cg::Mat4x4 getFinalXform() const;

    virtual void set_geo(std::shared_ptr<cg::Geometry> g_in);
    virtual void set_texid(GLuint texid);
    virtual void draw();

public: // Variables
    cg::Mat4x4 transform;
    std::shared_ptr<object> parent;

protected: // Functions

protected: // Variables

};

class geo : public object
{
public:
    virtual void set_geo(std::shared_ptr<cg::Geometry> g_in);
    virtual void set_texid(GLuint texid);
    virtual void draw();

    std::shared_ptr<cg::Geometry> g;
    GLuint texid;
};

class null : public object
{
};

class camera : public object
{
    virtual void draw();
};

class light : public object
{
    virtual void draw();
};

}
#endif //finish include guard

