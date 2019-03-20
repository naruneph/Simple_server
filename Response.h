#ifndef Response_class
#define Response_class

#include "headers.h"
#include "Re_Base.h"

class Response: public Re_Base{
protected:
    int status_num;
    std::string description;
public:
	enum Status{
		OK = 200,
	    BAD_REQUEST = 400,
	    FORBIDDEN = 403,
	    NOT_FOUND = 404,
	    INTERNAL_SERVER_ERROR = 500,
	    NOT_IMPLEMENTED = 501,
	    SERVICE_UNAVAILABLE = 503,
	};
	        
	Response(Status stat = OK);
	std::string build();
};


#endif
