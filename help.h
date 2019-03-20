#pragma once

#include "headers.h"
#include "Response.h"
#include "Request.h"
#include "Socket.h"


std::string gimme_word(std::string& str);
void Response_creator(Response &resp, Response::Status code, const std::string& URI, struct stat *filestats);
Response::Status Request_parser(std::string& URI, std::string& query_str,std::string& http_rfr,std::string& usr_agnt,bool& flag, struct stat& filestats, std::string& str);