#ifndef Re_Base_class
#define Re_Base_class

#include "headers.h"

class Re_Base{
protected:
	std::string HTTP_version;
	std::map<std::string, std::string>* headers;
	FILE* body;
	int bodylength;
public:
	Re_Base();
	virtual ~Re_Base();
	void upload_file(const char *path, int len);
	void add(const char* str);
	void put_in_file(FILE * f);
	FILE* get_file() const;
	int get_bodylength() const;
	void include_header(const std::string& str1, const std::string& str2);    
    virtual std::string build() = 0;
    std::map<std::string, std::string>* get_headers() const;
};

std::string get_mime_type(const std::string& str);
std::string from_mime_type(const std::string& str);
std::string date(time_t timer);


#endif
