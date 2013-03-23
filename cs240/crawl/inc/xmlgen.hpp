#ifndef XMLGEN_HPP
#define XMLGEN_HPP

#include <string>
#include "webpage.hpp"

class xmlgen
{
private:
    std::string start_url;

public:
    //! No arg constructor
    xmlgen();
    
    //! Destructor
    ~xmlgen();
    
    //! Replace problematic characters with acceptable XML replacements.
    std::string convertToXml(const std::string & str);
};

#endif //XMLGEN_HPP defined
