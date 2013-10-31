#if !defined(VECTOR4_HPP)
#define VECTOR4_HPP

namespace ede
{

class Vector4
{
public:
    float x,y,z,w, &r, &g, &b, &a;

    Vector4() : x(), y(), z(), w(), r(x), g(y), b(z), a(w) {}
    Vector4(float all) : x(all), y(all), z(all), w(all), r(x), g(y), b(z), a(w) {}
    Vector4(float xin, float yin, float zin, float win) : 
        x(xin), y(yin), z(zin), w(win), r(x), g(y), b(z), a(w) {}

};

}
#endif //finish include guard
