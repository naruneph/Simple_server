#include "headers.h"
#include "Request.h"

Request::Request(const std::string & URI, const std::string & method): URI(URI), method(method){ HTTP_version = "1.0";}

std::string Request::build(){
	std::stringstream str;
	str << method << " " << URI << " " << "HTTP/" << HTTP_version << "\r\n";
	if (headers){
        for(std::map<std::string, std::string>::iterator i = headers->begin(); i != headers->end(); i++){
            str << i->first << ": " << i->second << "\r\n";
        }
    }

    str << "\r\n";
    return str.str();
}
