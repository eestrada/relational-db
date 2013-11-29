#if !defined(MATRIX4X4_HPP)
#define MATRIX4X4_HPP

#include <stdexcept>

namespace cg
{


class Mat4x4
{
private:
    double *val_ptr;

public:
    Mat4x4(double identity=1.0): val_ptr(new double[16])
    {
        this->at(0,0) = identity;
        this->at(1,1) = identity;
        this->at(2,2) = identity;
        this->at(3,3) = identity;
    }

    Mat4x4(const Mat4x4 &other): val_ptr(new double[16])
    {
        *this = other;
    }

    ~Mat4x4() {delete[] val_ptr;}
    
    Mat4x4 &operator=(const Mat4x4 &other)
    {
        if(&other != this)
        {
            for(int i = 0; i < 16; ++i)
            {
                this->val_ptr[i] = other[i];
            }
        }
        return *this;
    }

    double &operator[](int index)
    {
        return val_ptr[index];
    }

    const double &operator[](int index) const
    {
        return val_ptr[index];
    }

    double & at(int col, int row)
    {
        if(col > 3 or row > 3 or col < 0 or row < 0)
            throw err::exception("Matrix out of range");
        return val_ptr[(col * 4) + row];
    }

    const double & at(int col, int row) const
    {
        if(col > 3 or row > 3 or col < 0 or row < 0)
            throw err::exception("Matrix out of range");
        return val_ptr[(col * 4) + row];
    }

    void setVal(int col, int row, double val);

    Mat4x4 operator*(const Mat4x4 &other);

    Mat4x4 operator*=(const Mat4x4 &other);
};

/*
template<size_t COL, size_t ROW>
class Matrix
{
private:
    double mat[COL][ROW];
    size_t col, row;

public:
    Matrix(float ident);

    Matrix transposed()
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
*/
}
#endif //finish include guard


