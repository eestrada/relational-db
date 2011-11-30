#ifndef WEBPAGE_HPP
#define WEBPAGE_HPP

#include <string>

class webpage
{
    // Private variables
    private:
        std::string pageURL;
        std::string pageDesc;
        
    public:
    
        //! String object constructor
        webpage(std::string URLstring);
        
        //! Old-style cstring constructor
        webpage(char* URLcstring);
        
        //! copy constructor
        webpage(const webpage & other);
        
        //! destructor
        ~webpage();
        
        //! Assignment operator
        //! @return Reference to oneself
        webpage& operator = (const webpage & other);

        //! Get page URL
        std::string& getURL();        

        //! Set webpage description
        void setDesc(const std::string & descStr);
        
        //! Get webpage description
        std::string& getDesc();
        
    // Private member functions
    private:

};

#endif //WEBPAGE_HPP defined
