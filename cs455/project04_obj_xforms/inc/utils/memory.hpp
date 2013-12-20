#if !defined(MEMORY_HPP)
#define MEMORY_HPP

namespace ptr
//namespace std
{

template <typename T>
class shared_ptr
{
public: //typedefs
public: //functions
    shared_ptr(){}
    template <typename U>
    explicit shared_ptr(U* p) : ptr(p), counter(new size_t()){}
    ~shared_ptr(){}
public: //variables
protected: //functions
protected: //variables
    T* ptr;
    size_t* counter;
};

} // End namespace ptr

#endif // end include guard
