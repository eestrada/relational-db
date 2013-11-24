#if !defined(IMAGE_HPP)
#define IMAGE_HPP

#include <ostream>
#include <vector>
#include <valarray>
#include <stdexcept>

#include <stdio.h>
#include <string.h>
#include <malloc.h>

#include "utils.hpp"
#include "hvector.hpp"


namespace cg
{

template <typename T>
struct pixel
{
    T r, g, b, a;
};

typedef pixel<uint8_t> pixelb;
typedef pixel<uint16_t> pixelh;
typedef pixel<uint32_t> pixeli;
typedef pixel<float> pixelf;

struct image
{
    std::vector<pixelb> pixels;
    size_t width, height;
};

struct colorRGBA : public hvector
{
    const double & r() const {return x;}
    double & r() {return x;}

    const double & g() const {return y;}
    double & g() {return y;}

    const double & b() const {return z;}
    double & b() {return z;}

    const double & a() const {return w;}
    double & a() {return w;}

    std::valarray<uint8_t> to_bytes()
    {
        double r,g,b,a;
        std::valarray<uint8_t> retval(4);

        r = utils::fit(this->r(), 0.0, 1.0, 0.0, 255.0);
        retval[0] = static_cast<uint8_t>(r);

        g = utils::fit(this->g(), 0.0, 1.0, 0.0, 255.0);
        retval[1] = static_cast<uint8_t>(g);

        b = utils::fit(this->b(), 0.0, 1.0, 0.0, 255.0);
        retval[2] = static_cast<uint8_t>(b);

        a = utils::fit(this->a(), 0.0, 1.0, 0.0, 255.0);
        retval[3] = static_cast<uint8_t>(a);

        return retval;
    }
};


////////////////////////////////////////////////////////////
// FUNCTION LoadPPM(char *)
// Load a binary ppm file into an OpenGL texture and return the OpenGL texture reference ID
////////////////////////////////////////////////////////////

GLuint loadPPM(const char *filename) {

    FILE *inFile; //File pointer
	char buffer[100]; //Input buffer
    GLubyte *theTexture; //Texture buffer pointer
    std::shared_ptr<image> retval(new image());
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

    retval->width = width;
    retval->height = height;
    retval->pixels.reserve(width * height);

	//Read maximum pixel value (usually 255)
	do fgets (buffer, sizeof (buffer), inFile);
	while (buffer[0] == '#');
	sscanf (buffer, "%d", &maxVal);

	//Allocate RGBA texture buffer
	int memSize = width * height * 4 * sizeof(GLubyte);
	theTexture = (GLubyte *)malloc(memSize);
    //uint8_t *tmp_ptr = reinterpret_cast<uint8_t*>(&(retval->pixels[0]));

    char b;
    for(auto i = retval->pixels.begin(); i != retval->pixels.end(); ++i)
    {
        b = fgetc(inFile);
        i->r=static_cast<uint8_t>(b);

        b = fgetc(inFile);
        i->g=static_cast<uint8_t>(b);

        b = fgetc(inFile);
        i->b=static_cast<uint8_t>(b);

        if (pixelSize == 4)
        {
            b = fgetc(inFile);
            i->a=static_cast<uint8_t>(b);
        }
        else
        {
            i->a=static_cast<uint8_t>(255);
        }
    }

	// read RGB data and set alpha value
	for (int i = 0; i < memSize; i++) {
		if ((i % 4) < 3 || pixelSize == 4) {
			c = fgetc(inFile);
			theTexture[i]=(GLubyte) c;
        }
		else theTexture[i] = (GLubyte) 255; //Set alpha to opaque
    }
    fclose(inFile);

/*
    bool flip = true;
    if(flip)
    {
        uint32_t *tmpbuff = (uint32_t *)malloc(memSize);
        uint32_t *textureCast = (uint32_t *)theTexture;

        memcpy(tmpbuff, theTexture, memSize);

        for (int i = 0; i < memSize; i++) {}
    }
*/

    GLuint textureID = 0; //OpenGL texture ID to be returned

    glGenTextures(1, &textureID);

    std::cerr << "Generated texture ID: " << textureID << std::endl;

    glBindTexture(GL_TEXTURE_2D, textureID);

    //Set texture parameters
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    //glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    //glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	//Ignore surface color
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

    //Define the texture
    glTexImage2D(GL_TEXTURE_2D, 0, 4, (GLuint)width, (GLuint)height, 0, GL_RGBA, GL_UNSIGNED_BYTE, theTexture);

    //Create mipmaps
    //gluBuild2DMipmaps(GL_TEXTURE_2D, 4, (GLuint)width, (GLuint)height, GL_RGBA, GL_UNSIGNED_BYTE, theTexture);

    free(theTexture);
    return(textureID);
}

} //end namespace

#endif // end include guard

