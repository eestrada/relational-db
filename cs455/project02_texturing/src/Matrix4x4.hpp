#if !defined(MATRIX4X4_HPP)
#define MATRIX4X4_HPP

namespace cg
{

template<unsigned char COL, unsigned char ROW>
class Matrix
{
private:
    float mat[COL][ROW];
    size_t col, row;

public:
    Matrix(float ident);

    getVal(int col, int row);

    setVal(int col, int row, float val);

    float & index(size_t col, size_t row);

    const float & index(size_t col, size_t row) const;
};

class Mat4x4
{
private:
    float mat[4][4];

public:
    Matrix4x4(float ident);

    getVal(int col, int row);

    setVal(int col, int row, float val);
};

}
#endif //finish include guard


