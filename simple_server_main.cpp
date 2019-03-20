#include "ServerSocket.h"
#include "SocketException.h"
#include "headers.h"
#include "help.h"
#include "Response.h"
#include "Request.h"


int main (int argc, char** argv){

	try{
 		
    	ServerSocket server ( 30009 );

    	while (true){
    		try{
				ServerSocket new_sock;


		  		server.accept (new_sock);
		  		sockaddr_in cl_addr;
		  		new_sock.get_cl_addr(cl_addr);

			
	  			std::string data, cur;
	  			do{ new_sock >> cur; data+=cur; }while(cur.size()==500);

	  			struct stat filestats;
	  			std::string URI;
	  			std::string QUERY_STRING,HTTP_REFERER,HTTP_USER_AGENT;
	  			bool flag = false;

	  			Response::Status stat = Request_parser(URI,QUERY_STRING,HTTP_REFERER,HTTP_USER_AGENT,flag,filestats,data); 

	  			Response response(stat);

	  			Response_creator(response, stat, URI,& filestats);



	  			//вот тут надо делать обработку cgi
	  			if (flag && (stat == Response::OK)){// да у нас cgi и статус хороший
	  				//переменные окружения которые будут отосланы дочернему процессу
	  				const char *pEnv[16];
	  				
	  				std::string temp0;
	  				temp0 = std::string("CONTENT_TYPE=") + get_mime_type(URI);
	  				pEnv[0] = temp0.c_str();

	  				pEnv[1] = "GATEWAY_INTERFACE=CGI/1.1";

	  				std::string temp2;
	  				char buf[50];
	  				memset (buf, 0,50);
	  				temp2 = std::string("REMOTE_ADDR=") + inet_ntop(AF_INET, &cl_addr.sin_addr,buf,49);
	  				pEnv[2] = temp2.c_str();


	  				std::string temp3;
	  				temp3 = std::string("REMOTE_PORT=") + std::to_string(ntohs(cl_addr.sin_port));
	  				pEnv[3] = temp3.c_str();

	  				std::string temp4;
	  				temp4 = std::string("QUERY_STRING=") + QUERY_STRING;
	  				pEnv[4] = temp4.c_str();

	  				pEnv[5] = "SERVER_ADDR=127.0.0.1";

	  				pEnv[6] = "SERVER_PORT=30009";

	  				pEnv[7] = "SERVER_PROTOCOL=HTTP/1.0";

	  				pEnv[8] ="SERVER_SOFTWARE=Model/1.0" ;

	  				pEnv[9] ="SERVER_NAME=none" ;

	  				std::string temp10;
	  				temp10 = std::string("SCRIPT_NAME=") + URI;
	  				pEnv[10] = temp10.c_str();

	  				std::string temp11;
	  				temp11 = std::string("SCRIPT_FILENAME=") + getcwd(NULL,0) + std::string("/") + URI;
	  				pEnv[11] = temp11.c_str();

	  				std::string temp12;
	  				temp12 = std::string("DOCUMENT_ROOT=") +  getcwd(NULL,0);
	  				pEnv[12] = temp12.c_str() ;

	  				std::string temp13;
	  				temp13 = std::string("HTTP_USER_AGENT=") +  HTTP_USER_AGENT;
	  				pEnv[13] = temp13.c_str() ;

	  				std::string temp14;
	  				temp14 = std::string("HTTP_REFERER=") +  HTTP_REFERER;
	  				pEnv[14] = temp14.c_str();

	  				pEnv[15] = NULL;

	  				// for (int i = 0; i < 15; ++i)
	  				// {
	  				// 	std::cout<<pEnv[i]<<std::endl;
	  				// }

	  				//переменные командной строки для дочернего процесса
	  				const char *args[2];
	  				std::string name =URI;
	  				args[0] = name.c_str(); 	
	  				args[1] = NULL;

	  				FILE* tmpfl = tmpfile();
	  				int fd = fileno(tmpfl);


	  				// дочерний процесс 
	  				int pid = fork();
	  				if(pid == 0){
	  					dup2(fd, 1);
	  					close(fd);

	  					execvpe(args[0], (char**)args, (char**)pEnv);

	  				}


	  				int status;
	  				wait(&status);
					// if (WIFEXITED(status)){
					// 	if (WEXITSTATUS(status)==0){
							
					// 	}
					// }
					// else{
						
					// }

					response.put_in_file(tmpfl);

	  			}

	  			response.include_header("CONTENT_LENGTH", std::to_string(response.get_bodylength()));

	  			new_sock<<response.build();



	  			if ( int len = response.get_bodylength() ){


	  				FILE* f = response.get_file();
	  				rewind (f);
	  				char buf[len];
	  				int i = fread(buf, 1, len, f);

	  				new_sock.send(buf, i);
	  			}

	 		
			}catch(SocketException& e){
				std::cout << "Exception was caught:" << e.description() << "\nExiting.\n";
    		}


		} 		
    }
  	catch ( SocketException& e ){
      std::cout << "Exception was caught:" << e.description() << "\nExiting.\n";
    }
  return 0;
}
