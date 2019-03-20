simple_server_objects = ServerSocket.o Socket.o simple_server_main.o help.o Response.o Request.o Re_Base.o

all: simple_server 

simple_server: $(simple_server_objects)
	g++ -std=c++11 -o simple_server $(simple_server_objects)



Socket: Socket.cpp
ServerSocket: ServerSocket.cpp
Re_Base: Re_Base.cpp
Request: Request.cpp
Response: Response.cpp
help: help.cpp
simple_server_main: simple_server_main.cpp
.cpp.o:
	g++ -c -o $@ -std=c++11 $<  


clean:
	rm -f *.o simple_server 
