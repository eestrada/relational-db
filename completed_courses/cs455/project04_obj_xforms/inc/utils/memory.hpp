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
    explicit shared_ptr(U* p) : ptr(p), counter(new size_t())
    {
        counter = 1;
    }

    ~shared_ptr()
    {
        delete_helper();
    }
public: //variables
protected: //functions
    void delete_helper()
    {
        if(ptr == NULL && counter != NULL)
        {
            throw bool();
        }
        else if(ptr != NULL && counter == NULL)
        {
            throw bool();
        }
        else if(ptr != NULL &&  counter != NULL)
        {
            if(*counter != 0)
            {
                --(*counter);
                if(*counter == 0)
                {
                    delete ptr;
                    ptr = NULL;

                    delete counter;
                    counter = NULL;
                }
            }
        }
    }
protected: //variables
    T* ptr;
    size_t* counter;
};

} // End namespace ptr

#endif // end include guard
