#ifndef Socket_class
#define Socket_class

#include "headers.h"

const int MAXHOSTNAME = 200;
const int MAXCONNECTIONS = 5;
const int MAXRECV = 500;

class Socket{
  int m_sock;
  sockaddr_in m_addr;

public:
  Socket();
  virtual ~Socket();

  // Server 
  bool create();
  bool bind (const int port);
  bool listen() const;
  bool accept (Socket&) const;

  // Client 
  bool connect (const std::string host, const int port);

  // Data 
  bool send (const std::string) const;
  int recv (std::string&) const;
  bool send ( const char* s, int len )const;

  void set_non_blocking (const bool);

  bool is_valid() const { return m_sock != -1; }

  void get_cl_addr(sockaddr_in& p){p = m_addr; return;}

};


#endif
