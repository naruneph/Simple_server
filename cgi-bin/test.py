#!/usr/bin/env python3

import os

print("<h1>HELLO!!!!</h1>")
print("CONTENT_TYPE=",os.environ["CONTENT_TYPE"])
print("GATEWAY_INTERFACE=", os.environ["GATEWAY_INTERFACE"])
print("REMOTE_ADDR=",os.environ["REMOTE_ADDR"])
print("REMOTE_PORT=",os.environ["REMOTE_PORT"])
print("QUERY_STRING=",os.environ["QUERY_STRING"])
print("SERVER_ADDR=",os.environ["SERVER_ADDR"])
print("SERVER_PORT=",os.environ["SERVER_PORT"])
print("SERVER_PROTOCOL=",os.environ["SERVER_PROTOCOL"])
print("SERVER_SOFTWARE=",os.environ["SERVER_SOFTWARE"])
print("SERVER_NAME=",os.environ["SERVER_NAME"])
print("SCRIPT_NAME=",os.environ["SCRIPT_NAME"])
print("SCRIPT_FILENAME=",os.environ["SCRIPT_FILENAME"])
print("DOCUMENT_ROOT=",os.environ["DOCUMENT_ROOT"])
print("HTTP_USER_AGENT=",os.environ["HTTP_USER_AGENT"])
print("HTTP_REFERER=",os.environ["HTTP_REFERER"])







