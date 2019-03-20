#include "ServerSocket.h"
#include "SocketException.h"


bool ServerSocket::send ( const char* s, int len )const{
  return Socket::send(s, len);
}

ServerSocket::ServerSocket ( int port ){
  if ( ! Socket::create() ){
    throw SocketException ( "Could not create server socket." );
  }

  if ( ! Socket::bind ( port ) ){
    throw SocketException ( "Could not bind to port." );
  }

  if ( ! Socket::listen() ){
    throw SocketException ( "Could not listen to socket." );
  }
}

ServerSocket::~ServerSocket(){}


const ServerSocket& ServerSocket::operator << ( const std::string& s ) const{
  if ( ! Socket::send ( s ) ){
    throw SocketException ( "Could not write to socket." );
  }

  return *this;
}


const ServerSocket& ServerSocket::operator >> ( std::string& s ) const{
  Socket::recv ( s );
  return *this;
}

void ServerSocket::accept ( ServerSocket& sock ){
  if ( ! Socket::accept ( sock ) )
    {
      throw SocketException ( "Could not accept socket." );
    }
}

