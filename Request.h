#ifndef Request_class
#define Request_class

#include "headers.h"
#include "Re_Base.h"

class Request: public Re_Base{
protected:
   	std::string method;
    std::string URI;
public:
    Request(const std::string & URI, const std::string & method = "GET");
    std::string build();
};

#endif
