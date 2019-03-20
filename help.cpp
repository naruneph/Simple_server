#include "headers.h"
#include "help.h"
#include "Re_Base.h"

std::string gimme_word(std::string& str){
	std::string delimiter;
	size_t pos = 0;
	std::string token;

	size_t p1 = str.find(" ");
	size_t p2 = str.find("\r\n");

	if (p1 != std::string::npos){
		if(p1<p2){
			pos = p1;
			delimiter = " ";
		}
		if(p2<p1){
			pos = p2;
			delimiter = "\r\n";
		}
		token = str.substr(0, pos);   	
    	str.erase(0, pos + delimiter.length());
    	return token;
	}
	else{
		if(p2 == 0){
			delimiter = "\r\n";
			return delimiter;
		}
		else{
			pos = p2;
			token = str.substr(0, pos); 
			str.erase(0, pos + delimiter.length());
            return token;
		}
	}
}


Response::Status Request_parser(std::string& URI, std::string& query_str,std::string& http_rfr,std::string& usr_agnt,bool& flag, struct stat& filestats, std::string& str){
	std::string method;


    method = gimme_word(str);
	Response::Status code;
	if (method == "HEAD" || method == "POST" || method == "PUT" || method == "DELETE"){
        code = Response::NOT_IMPLEMENTED;
    }
    if (method != "GET"){
        code = Response::BAD_REQUEST;
    }
    else{
    	code = Response::OK;
    }

    if (code == Response::OK){
        std::string path;
    	path = gimme_word(str.erase(0,1));

        int queryIndex = path.find("?");

        if (queryIndex != URI.npos){
            URI = path.substr(0, queryIndex);
            query_str = path.substr(queryIndex+1, path.size());
        }else{
            URI=path;
            query_str = "";
        }

        int refIndex =str.find("Referer: ");
        if (refIndex != str.npos){
            std::string tmpstr1;
            tmpstr1 = str.substr(refIndex+9);
            http_rfr = tmpstr1.substr(0,tmpstr1.find("\r\n"));
        }

        int usrIndex =str.find("User-Agent: ");
        if (usrIndex != str.npos){
            std::string tmpstr2;
            tmpstr2 = str.substr(usrIndex+12);
            usr_agnt = tmpstr2.substr(0,tmpstr2.find("\r\n"));
        }



        if (URI.find("cgi-bin")==0){
            flag = true;
        }



    	int ret = stat(URI.data(), &filestats);
    	if (ret == -1){
            code = Response::NOT_FOUND;
        }
        else if (!(filestats.st_mode & S_IRUSR)){
            code = Response::FORBIDDEN;
        }

    }

    return code;
}


void Response_creator(Response &resp, Response::Status code, const std::string& URI, struct stat *filestats){
	resp.include_header("Date" , date(time(NULL)));
    resp.include_header("Server","Model HTTP Server/1.0");

    switch(code){
    case Response::OK:
        resp.upload_file(URI.data(), filestats->st_size);
        resp.include_header("CONTENT_TYPE" , get_mime_type(URI));
        resp.include_header("Last-modified", date(filestats->st_mtime));
        break;
    case Response::BAD_REQUEST:
        resp.add("400 BAD_REQUEST");
        resp.include_header("CONTENT_TYPE","text/html");
        break;
    case Response::FORBIDDEN:
        resp.add("403 FORBIDDEN");
        resp.include_header("CONTENT_TYPE","text/html");
        break;
    case Response::NOT_FOUND:
        resp.add("404 NOT_FOUND");
        resp.include_header("CONTENT_TYPE","text/html");
        break;
    case Response::INTERNAL_SERVER_ERROR:
        resp.add("500 INTERNAL_SERVER_ERROR");
        resp.include_header("CONTENT_TYPE","text/html");
        break;
    case Response::NOT_IMPLEMENTED:
        resp.add("501 NOT_IMPLEMENTED");
        resp.include_header("Allow","GET");
        resp.include_header("CONTENT_TYPE","text/html");
        break;
    case Response::SERVICE_UNAVAILABLE:
        resp.add("503 SERVICE_UNAVAILABLE");
        resp.include_header("CONTENT_TYPE","text/html");
        break;
    }
    resp.include_header("CONTENT_LENGTH", std::to_string(resp.get_bodylength()));

    return;
}