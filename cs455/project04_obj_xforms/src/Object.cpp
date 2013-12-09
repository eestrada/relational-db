#include <GL/gl.h>
#include "cg/Object.hpp"

namespace obj
{

std::shared_ptr<object> object::scene_camera = std::shared_ptr<object>();

object::object() : transform(1.0), parent() {}

cg::Mat4x4 object::getFinalXform() const
{
    if (parent != NULL)
    {
        cg::Mat4x4 pxform = parent->getFinalXform();
        // Do child transform THEN parent to get expected result
        return pxform * transform;
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
    cg::Mat4x4 cam_inverted = cg::matrix::inverted(this->scene_camera->getFinalXform());
    this->g->draw(cam_inverted * this->getFinalXform());
}

void null::enable_draw(bool enable)
{
    this->drawable = !enable;
}

void null::draw()
{
    if(!this->drawable)
    {
        cg::Mat4x4 cam_inverted = cg::matrix::inverted(this->scene_camera->getFinalXform());
        cg::Mat4x4 tmp = cam_inverted * this->getFinalXform();
        glBindTexture(GL_TEXTURE_2D, 0);

        cg::point3 pt;
        double size = 1.5;
        glColor4d(0.0, 1.0, 0.0, 1.0);
        glLineWidth(1.0);
        glBegin(GL_LINES);
            pt = tmp * cg::hvector(size, 0.0, 0.0, 1.0);
            glVertex3d(pt.x, pt.y, pt.z);

            pt = tmp * cg::hvector(-size, 0.0, 0.0, 1.0);
            glVertex3d(pt.x, pt.y, pt.z);

            pt = tmp * cg::hvector(0.0, size, 0.0, 1.0);
            glVertex3d(pt.x, pt.y, pt.z);

            pt = tmp * cg::hvector(0.0, -size, 0.0, 1.0);
            glVertex3d(pt.x, pt.y, pt.z);

            pt = tmp * cg::hvector(0.0, 0.0, size, 1.0);
            glVertex3d(pt.x, pt.y, pt.z);

            pt = tmp * cg::hvector(0.0, 0.0, -size, 1.0);
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

