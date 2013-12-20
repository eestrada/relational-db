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
public: // Constructors
    object();
public: // Functions
    cg::Mat4x4 getFinalXform() const;

    virtual void set_geo(cg::Geometry* g_in);
    virtual void set_texid(GLuint texid);
    virtual void draw() = 0; // This makes this object an abstract class

public: // Variables
    cg::Mat4x4 transform;
    object* parent;
    static object* scene_camera;
};

class geo : public object
{
public:
    virtual void set_geo(cg::Geometry* g_in);
    virtual void set_texid(GLuint texid);
    virtual void draw();

    cg::Geometry* g;
    GLuint texid;
};

class null : public object
{
public:
    virtual void draw();

public: // variables
    static bool drawable;
};

class camera : public object
{
public:
    camera();
    virtual void draw();
    virtual void build_perspective();

public: // Variables
    double fovy, aspect, znear, zfar;
    cg::Mat4x4 perspective;
};

class light : public object
{
public:
    virtual void draw();
};

}
#endif //finish include guard

