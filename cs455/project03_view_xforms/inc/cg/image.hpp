#if !defined(IMAGE_HPP)
#define IMAGE_HPP

#include <ostream>
#include <vector>
#include <valarray>
#include <stdexcept>

#include <cstdlib>
#include <cstdio>
#include <cstring>

#include "utils.hpp"
#include "hvector.hpp"


namespace cg
{

namespace image
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

struct bitmap
{
    std::vector<uint8_t> data;
    size_t width, height;

    const uint8_t *raw() const
    {
        return &(this->data[0]);
    }
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
// Load OpenGL textures from binary ppm files
////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////
// FUNCTION LoadPPM(char *)
// Load a binary ppm file into an OpenGL texture and return the OpenGL texture reference ID
////////////////////////////////////////////////////////////

bitmap loadPPM(const std::string &filename)
{
    FILE *inFile; //File pointer
	char buffer[100]; //Input buffer
	unsigned char c; //Input character
	int width, height, maxVal, pixelSize; //Image characteristics from ppm file

    std::unique_ptr<GLubyte[]> theTexture;
    bitmap image;

	//Try to open the file for reading
	if( (inFile = std::fopen(filename.c_str(), "rb")) == NULL) {
        std::string errstr = "cannot open " + filename + "\n";
        throw err::system_exit(errstr, -1);
	}

	//Read file type identifier (magic number)
	std::fgets(buffer, sizeof(buffer), inFile);
	if ((buffer[0] != 'P') || (buffer[1] != '6')) {
        std::string errstr = "not a binary ppm file " + filename + "\n";
        throw err::system_exit(errstr, -1);
    }

	if(buffer[2] == 'A') pixelSize = 4;
	else pixelSize = 3;

	//Read image size
	do std::fgets(buffer, sizeof (buffer), inFile);
	while (buffer[0] == '#');
	std::sscanf (buffer, "%d %d", &width, &height);
    image.width = width;
    image.height = height;

	//Read maximum pixel value (usually 255)
	do std::fgets (buffer, sizeof (buffer), inFile);
	while (buffer[0] == '#');
	std::sscanf (buffer, "%d", &maxVal);

	//Allocate RGBA texture buffer
	int memSize = width * height * 4 * sizeof(GLubyte);

    // By adding one, the vector shouldn't hit its limit and reallocate unnessecarily
    image.data.reserve(memSize + 1); 

	// read RGB data and set alpha value
	for (int i = 0; i < memSize; i++) {
		if ((i % 4) < 3 || pixelSize == 4) {
			c = std::fgetc(inFile);
			image.data.push_back((GLubyte) c);
        }
		else image.data.push_back((GLubyte) 255); //Set alpha to opaque
    }
    std::fclose(inFile);

    return image;
}

} //end namespace image
} //end namespace cg

#endif // end include guard

