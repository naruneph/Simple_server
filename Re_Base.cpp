#include "headers.h"
#include "Re_Base.h"

Re_Base::Re_Base(): headers(NULL), body(NULL),bodylength(0){}

void Re_Base::put_in_file(FILE* f){
    if (body){
        fclose(body);
    }
    
    rewind(f);
    body = f;
    fseek(body, 0L, SEEK_END); 
    bodylength = ftell(body);
    rewind(body);

}

Re_Base::~Re_Base(){
    delete headers;
    fclose(body);
    body = NULL;
}

void Re_Base::upload_file(const char *path, int len){
	FILE* ptr = fopen(path, "rb");
	if (body){
        fclose(body);
    }
	body = ptr;
    bodylength = len;   
}

void Re_Base::add(const char* str){
	if(!body){
		 body = tmpfile();
	}
	bodylength += strlen(str);
    fprintf(body, "%s", str);
}

FILE* Re_Base::get_file() const{
    return body;
}

int Re_Base::get_bodylength() const{
	return bodylength;
}

void Re_Base::include_header(const std::string& str1, const std::string& str2){

	if (!headers){
        headers = new std::map<std::string, std::string>();
    }

    headers->insert(std::pair<std::string, std::string>(str1,str2));

}

std::map<std::string, std::string>* Re_Base::get_headers() const{
    return headers;
}

std::string get_mime_type(const std::string& str){

    int point = str.find(".");
    if (point != str.npos){
    	std::string suff = str.substr(point);
        if (suff == ".html"){ return "text/html";}
        if (suff == ".pdf"){return "application/pdf";}
        if (suff == ".jpg" || suff == ".jpeg"){
            return "image/jpeg";
        }
		else{
            return "text/plain";
        }
    }
    else{
    	return "text/plain";
    }
}

std::string from_mime_type(const std::string& mime){
    if (mime == "text/plain") {return ".txt";}
    if (mime == "image/jpeg") {return ".jpg";}
    if (mime == "application/pdf") {return ".pdf";}
    if (mime == "text/html") {return ".html";}
    return ".txt";
}

std::string date(time_t timer){
    struct tm *t = gmtime(&timer);
    char buf[30];
    strftime(buf, 30, "%a, %d %b %Y %X GMT", t);
    return std::string(buf);
}

