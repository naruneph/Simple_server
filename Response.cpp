#include "headers.h"
#include "Response.h"


Response::Response(Status stat): status_num(stat){
    HTTP_version = "1.0";
    switch (stat){
    	case OK: description = "OK"; break;
    	case BAD_REQUEST: description = "Bad Request"; break;
    	case FORBIDDEN: description = "Forbidden"; break;
    	case NOT_FOUND: description = "Not Found"; break;
    	case INTERNAL_SERVER_ERROR: description = "Internal Server Error";break;
    	case NOT_IMPLEMENTED:description = "Not Implemented";break;
   		case SERVICE_UNAVAILABLE:description = "Service Unavailable";break;
    	default: break;     
    }
}

std::string Response::build(){

    std::stringstream str;
    str << "HTTP/" << HTTP_version << " " << status_num << " " << description << "\r\n";
    if (headers){
        for(std::map<std::string, std::string>::iterator i = headers->begin(); i != headers->end(); i++){
            str << i->first << ": " << i->second << "\r\n";
        }
    }
    str << "\r\n";
    return str.str();
}
