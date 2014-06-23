#if !defined(EXCEPTIONS_HPP)
#define EXCEPTIONS_HPP

/* Include C++ standard headers */
#include <exception>
#include <stdexcept>
#include <string>

class system_exit : public std::exception
{
public:
    system_exit(const std::string &msg = "", int return_code = 0)
        : what_str(msg), exit_code(return_code) {}
    virtual ~system_exit(){}

    virtual const char* what() const noexcept
    {
        return what_str.c_str();
    }

    virtual int code() const noexcept
    {
        return exit_code;
    }
protected:
    std::string what_str;
    int exit_code;
};


#endif // end include guard
