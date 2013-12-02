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

    virtual void set_geo(std::shared_ptr<cg::Geometry> g_in);
    virtual void set_texid(GLuint texid);
    virtual void draw();

public: // Variables
    cg::Mat4x4 transform;
    std::shared_ptr<object> parent;
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
public:
    virtual void enable_draw(bool enable=true);
    virtual void draw();
protected:
    bool drawable;
};

class camera : public object
{
public:
    virtual void draw();
};

class light : public object
{
public:
    virtual void draw();
};

}
#endif //finish include guard

