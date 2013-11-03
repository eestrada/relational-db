/* Include C++ standard headers */
#include <stdexcept>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

// TODO: Possibly place X11 and GL in namespaces. This should help distinguish what 
// functions are coming from where (most are clear, but some are pretty 
// ambiguous).

#include <stdio.h>
#include <malloc.h>
//#include <GL/glut.h>
//#include <glut.h>
//#include "texture.h"

//#include <unistd.h>
//#include <X11/Xlib.h>
//#include <X11/Xutil.h>

#include <GL/freeglut.h>
//#include <GL/gl.h>
//#include <GL/glu.h>


/* Include my headers */

#include "objparser.hpp"

/* Global vars */


namespace ede
{
const unsigned int BUFFER_MODE = GLUT_DOUBLE;
const int XCONST = 512, YCONST = 512;

std::vector<cg::trimesh> meshlist;

/* report GL errors, if any, to stderr */
//void checkError(const char *functionName)
void checkGlError(const std::string &functionName)
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

std::string load_file_as_str(const std::string &fname)
{
        std::ifstream file;
        file.exceptions(std::ifstream::failbit);

        try
        {
            file.open(fname.c_str());
        }
        catch(std::ios_base::failure &e)
        {
            std::cerr << "When opening file \"" << fname;
            std::cerr << "\" the following exception occured: ";
            std::cerr << e.what() << std::endl;

            throw e;
        }
 
        std::stringstream fileData;
        fileData << file.rdbuf();
        file.close();
 
        return fileData.str();
}

void test_obj_parser()
{
    //std::istringstream strm(load_file_as_str("test.obj"));

    //auto tm = cg::objparser::parse(strm);

    auto tm = cg::objparser::parse_file("test.obj");

    std::cout << *tm;
}


////////////////////////////////////////////////////////////
// Load OpenGL textures from binary ppm files
////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////
// FUNCTION LoadPPM(char *)
// Load a binary ppm file into an OpenGL texture and return the OpenGL texture reference ID
////////////////////////////////////////////////////////////

GLuint loadPPM(const char *filename) {

    FILE *inFile; //File pointer
	char buffer[100]; //Input buffer
    GLubyte *theTexture; //Texture buffer pointer
	unsigned char c; //Input character
	int width, height, maxVal, pixelSize; //Image characteristics from ppm file


	//Try to open the file for reading
	if( (inFile = fopen(filename, "rb")) == NULL) {
		fprintf (stderr, "cannot open %s\n", filename);
		exit(-1);
	}

	//Read file type identifier (magic number)
	fgets(buffer, sizeof(buffer), inFile);
	if ((buffer[0] != 'P') || (buffer[1] != '6')) {
		fprintf (stderr, "not a binary ppm file %s\n", filename);
		exit(-1);
    }

	if(buffer[2] == 'A')
		pixelSize = 4;
	else
		pixelSize = 3;

	//Read image size
	do fgets(buffer, sizeof (buffer), inFile);
	while (buffer[0] == '#');
	sscanf (buffer, "%d %d", &width, &height);

	//Read maximum pixel value (usually 255)
	do fgets (buffer, sizeof (buffer), inFile);
	while (buffer[0] == '#');
	sscanf (buffer, "%d", &maxVal);

	//Allocate RGBA texture buffer
	int memSize = width * height * 4 * sizeof(GLubyte);
	theTexture = (GLubyte *)malloc(memSize);

	// read RGB data and set alpha value
	for (int i = 0; i < memSize; i++) {
		if ((i % 4) < 3 || pixelSize == 4) {
			c = fgetc(inFile);
			theTexture[i]=(GLubyte) c;
        }
		else theTexture[i] = (GLubyte) 255; //Set alpha to opaque
    }
    fclose(inFile);

    GLuint textureID = 0; //OpenGL texture ID to be returned

    glGenTextures(1, &textureID);

    std::cerr << "Generated texture ID: " << textureID << std::endl;

    glBindTexture(GL_TEXTURE_2D, textureID);

    //Set texture parameters
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
	//Ignore surface color
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

    //Define the texture
    glTexImage2D(GL_TEXTURE_2D, 0, 4, (GLuint)width, (GLuint)height, 0, GL_RGBA, GL_UNSIGNED_BYTE, theTexture);

    //Create mipmaps
    gluBuild2DMipmaps(GL_TEXTURE_2D, 4, (GLuint)width, (GLuint)height, GL_RGBA, GL_UNSIGNED_BYTE, theTexture);

    free(theTexture);
    return(textureID);
}

void draw()
{
    glBegin(GL_TRIANGLES);
        //while(false)
        //{
            glVertex3f(0.0, 0.0,0.0);
            glVertex3f(0.0, 1.0,0.0);
            glVertex3f(1.0, 1.0,0.0);

            glTexCoord2f(0.0, 0.0);
            glTexCoord2f(0.0, 1.0);
            glTexCoord2f(1.0, 1.0);
        //}
    glEnd();
}

void display(void)
{
    glClear (GL_COLOR_BUFFER_BIT);

    glClearColor ( 1, 0.5, 0.0, 1 );
    glClear ( GL_COLOR_BUFFER_BIT );
    draw ();
    glFlush ();

    if(BUFFER_MODE == GLUT_DOUBLE)
        glutSwapBuffers ();

    checkGlError ("display");
}

void idle(void)
{
    checkGlError ("idle");
}

void reshape(int x, int y)
{
    glutReshapeWindow(XCONST, YCONST);
    checkGlError ("reshape");
}


void initGL(void)
{
    /*
    GLuint texid;

    glGenTextures(1, &texid);

    glBindTexture(GL_TEXTURE_2D, texid);

    GLubyte test[] = {255, 0, 0};

    glTexImage2D(   GL_TEXTURE_2D, //target
                    0, //MIPMAP level
                    GL_RGB, //internal Format
                    1, //width
                    1, //height
                    0, //border width
                    GL_RGB, //format
                    GL_UNSIGNED_BYTE, //type
                    test); //data

    // Linear Filtering
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    */

    //GLuint tmp = loadPPM("./test.ppm");
    loadPPM("./test.ppm");

    glEnable(GL_TEXTURE_2D);
    glShadeModel(GL_SMOOTH);
    //glClearColor(0.0, 0.0, 0.0, 0.5);
    //glClearDepth(1.0);
    //glEnable(GL_DEPTH_TEST);
    //glDepthFunc(GL_LEQUEL);
    //glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

    checkGlError("init");
}

// Since we are inside a namespace the compiler/linker will not complain
// about the function being named main.
int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode (BUFFER_MODE | GLUT_RGB);

    //glutInitContextVersion (3, 1);
    //glutInitContextFlags (GLUT_COMPATIBILITY_PROFILE | GLUT_DEBUG);
    //glutInitContextFlags (GLUT_FORWARD_COMPATIBLE | GLUT_CORE_PROFILE | GLUT_DEBUG);

    glutInitWindowSize (XCONST, YCONST); 
    glutInitWindowPosition (0, 0);
    glutCreateWindow ("OpenGL 2.1 context via FreeGLUT");
    //int main_window_id = glutCreateWindow ("OpenGL 2.1 context via FreeGLUT");

    //std::cerr << "Main window ID: " << main_window_id << std::endl;

    // test obj file parser
    test_obj_parser();

    //dumpInfo ();
    initGL();
    glutDisplayFunc(display); 
    glutIdleFunc(display); 
    glutReshapeFunc(reshape);
    //glutKeyboardFunc(keyboard);
    glutMainLoop();
    return 0;
}

}

int main(int argc, char **argv)
{
    int retval = 0;

    try
    {
        retval = ede::main(argc, argv);
    }
    catch(std::exception &e)
    {
        std::cerr << "ZOINKS! There was an unexpected exit due to the following exception: ";
        std::cerr << e.what() << std::endl;
        retval = -1;
    }

    return retval;

}
