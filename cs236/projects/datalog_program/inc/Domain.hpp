#if !defined(__DOMAIN_H__)
#define __DOMAIN_H__
#include <set>
#include <string>

class Domain : public std::set<std::string>
{
private:
public:
    Domain();
    ~Domain();

    std::string toString();
};

#endif //defined __DOMAIN_H__

