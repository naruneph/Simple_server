#ifndef ServerSocket_class
#define ServerSocket_class

#include "Socket.h"


class ServerSocket:private Socket{
public:
	ServerSocket ( int port );
	ServerSocket (){};
	virtual ~ServerSocket();

	const ServerSocket& operator << ( const std::string& ) const;
	const ServerSocket& operator >> ( std::string& ) const;
	bool send ( const char* s, int len )const;
	void accept ( ServerSocket& );

	void get_cl_addr(sockaddr_in& ad){Socket::get_cl_addr(ad); return;}

	
};



#endif
