/* Include C++ standard headers */
#include <stdexcept>

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

// TODO: Possibly place X11 and GL in namespaces. This should help distinguish what 
// functions are coming from where (most are clear, but some are pretty 
// ambiguous).

//#include <unistd.h>
//#include <X11/Xlib.h>
//#include <X11/Xutil.h>

#include <GL/freeglut.h>

#include <GL/gl.h>
#include <GL/glu.h>

/* report GL errors, if any, to stderr */
//void checkError(const char *functionName)
void checkError(const std::string &functionName)
{
    GLenum error;
    while (( error = glGetError() ) != GL_NO_ERROR) {
        std::cerr << "GL error 0x";
        std::cerr << std::hex << error << std::dec;
        std::cerr << " detected in ";
        std::cerr << functionName << std::endl ;
        //fprintf (stderr, "GL error 0x%X detected in %s\n", error, functionName);
    }
}

std::string loadFile(const std::string &fname)
{
        std::ifstream file;
        file.exceptions(std::ifstream::failbit);

        try
        {
            file.open(fname.c_str());
        }
        catch(std::exception &e)
        {
            std::cerr << "The following exception occured when opening file: ";
            std::cerr << fname << std::endl;
            std::cerr << e.what() << std::endl;

            throw e;
        }
 
        std::stringstream fileData;
        fileData << file.rdbuf();
        file.close();
 
        return fileData.str();
}

void display(void)
{
    glClear (GL_COLOR_BUFFER_BIT);

    glClearColor ( 1, 0.5, 0.0, 1 );
    glClear ( GL_COLOR_BUFFER_BIT );
    //triangle ();
    glFlush ();
    //checkError ("display");
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);

    glutInitContextVersion (3, 1);
    glutInitContextFlags (GLUT_FORWARD_COMPATIBLE | GLUT_CORE_PROFILE | GLUT_DEBUG);

    glutInitWindowSize (1024, 576); 
    glutInitWindowPosition (0, 0);
    glutCreateWindow ("OpenGL 3.1 context via FreeGLUT");

    //dumpInfo ();
    //init ();
    glutDisplayFunc(display); 
    //glutReshapeFunc(reshape);
    //glutKeyboardFunc (keyboard);
    glutMainLoop();
    return 0;
}

