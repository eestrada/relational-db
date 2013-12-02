#include <GL/gl.h>
#include "cg/Object.hpp"

namespace obj
{

object::object() : transform(1.0), parent() {}

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

void null::enable_draw(bool enable)
{
    this->drawable = enable;
}

void null::draw()
{
    if(drawable)
    {
        cg::Mat4x4 tmp = this->getFinalXform();
        cg::point3 pt;
        glBindTexture(GL_TEXTURE_2D, 0);
        glColor4d(0.0, 1.0, 0.0, 1.0);
        glBegin(GL_LINES);
            pt = tmp * cg::hvector(10.0, 0.0, 0.0, 1.0);
            glVertex3d(pt.x, pt.y, pt.z);

            pt = cg::hvector(-10.0, 0.0, 0.0, 1.0);
            glVertex3d(pt.x, pt.y, pt.z);

            pt = cg::hvector(0.0, 10.0, 0.0, 1.0);
            glVertex3d(pt.x, pt.y, pt.z);

            pt = cg::hvector(10.0, -10.0, 0.0, 1.0);
            glVertex3d(pt.x, pt.y, pt.z);

            pt = cg::hvector(10.0, 0.0, 10.0, 1.0);
            glVertex3d(pt.x, pt.y, pt.z);

            pt = cg::hvector(10.0, 0.0, -10.0, 1.0);
            glVertex3d(pt.x, pt.y, pt.z);
        glEnd();
        glColor4d(1.0, 1.0, 1.0, 1.0);
    }
}

void camera::draw()
{
}

void light::draw()
{
}

} // end namespace obj

