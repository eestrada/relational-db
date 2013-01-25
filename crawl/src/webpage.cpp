#include <string>
#include "webpage.hpp"

//! String object constructor
webpage::webpage(std::string URLstring)
{
    pageURL = URLstring;
    pageDesc = "Place holder.";
}

//! Old-style cstring constructor
webpage::webpage(char* URLcstring)
{
    pageURL = URLcstring;
    pageDesc = "Place holder.";
}

//! copy constructor
webpage::webpage(const webpage & other)
{
}

//! destructor
webpage::~webpage()
{
}

//! Assignment operator
//! @return Reference to oneself
webpage & webpage::operator = (const webpage & other)
{
    return *this;
}

//! Get page URL
std::string & webpage::getURL()
{
    return *new std::string("Replace this code with something real!");
}

//! Set webpage description
void webpage::setDesc(const std::string & descStr)
{
}

//! Get webpage description
std::string & webpage::getDesc()
{
    return *new std::string("Replace this code with something real!");    
}
