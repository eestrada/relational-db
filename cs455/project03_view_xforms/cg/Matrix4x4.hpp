#if !defined(MATRIX4X4_HPP)
#define MATRIX4X4_HPP

#include <stdexcept>

namespace cg
{

template<size_t COL, size_t ROW>
class Matrix
{
private:
    double mat[COL][ROW];
    size_t col, row;

public:
    Matrix(float ident);

    Matrix transposed();
    {
        for()
        {
            for
        }
    }

    double & at(size_t col, size_t row)
    {
        if(col < COL && row < ROW)
            return mat[col][row];
        else
            throw std::out_of_range("Matrix indices out of range");
    }

    const double & at(size_t col, size_t row) const;
    {
        if(col < COL && row < ROW)
            return mat[col][row];
        else
            throw std::out_of_range("Matrix indices out of range");
    }
};

class Mat4x4
{
private:
    double mat[4][4];

public:
    Matrix4x4(double ident);

    double getVal(int col, int row)
    {
        return mat[col][row];
    }

    void setVal(int col, int row, double val)
};

}
#endif //finish include guard


