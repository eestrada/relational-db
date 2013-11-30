#include <GL/gl.h>
#include "cg/Object.hpp"

namespace obj
{

cg::Mat4x4 object::getFinalXform() const
{
    if (parent != NULL)
    {
        cg::Mat4x4 pxform = parent->getFinalXform();
        return transform * pxform;
    }
    else
    {
        return transform;
    }
}

void object::set_texid(GLuint texid){}

void object::set_geo(std::shared_ptr<cg::Geometry> g_in){}

void object::draw()
{
}

void geo::set_geo(std::shared_ptr<cg::Geometry> g_in)
{
    this->g = g_in;
}

void geo::set_texid(GLuint texid)
{
    this->texid = texid;
}

void geo::draw()
{
    glBindTexture(GL_TEXTURE_2D, this->texid);
    this->g->draw(this->getFinalXform());
}

void camera::draw()
{
}

void light::draw()
{
}

} // end namespace obj

