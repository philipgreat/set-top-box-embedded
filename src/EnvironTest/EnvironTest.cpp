// EnvironTest.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdlib.h>
#include <stdio.h>
#include <windows.h>

#include "SystemTaskExecutor.h"

#ifndef  _WIN32_WCE
#pragma comment(lib,"ws2_32")
#include <Winsock2.h>
#else
#pragma comment(lib,"ws2")
#include <Winsock.h>
#endif
#include <windows.h>
#include <winsock.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "..\\ServiceFramework\\UDPServer.h"
#include "DocumentServerObject.h"

#include "PowerPointProcessor.h"
#include "MSWordProcessor.h"
#include "ByteBuffer.h"
#include "DocumentHandle.h"
#include "TCPClient.h"
#include "PowerPointHandler.h"
#include "SmartDocumentDispatcher.h"
int start_server();
void errexit(const char *format, ...);
int test_dispatch(int argc, char* argv[]);


int test_dispatch(int argc, char* argv[])
{
	//CoUnInitialize(NULL);
	if(argc<2){
		printf("usage: pget <fileaname>\n");
		return 0;
	}
	init_environment();
	SmartDocumentDispatcher *dispatcher=NULL;
	try{
		dispatcher = new SmartDocumentDispatcher;
		dispatcher->proc("f:\\document\\06.ppt","not good thing");
		dispatcher->proc("f:\\document\\06.ppt","not good thing");	
		
	
	}catch(Exception &e){	
		e.report();
	}
	if(dispatcher)delete dispatcher;
	//proc.processDocument(argv[1]);

	return 0;
}

int main(int argc, char* argv[])
{
	init_environment();
	//return test_dispatch(argc,argv);
	return start_server();
	return 0;
}


void errexit(const char *format, ...)
{
	va_list	args;	
	va_start(args, format);
	vfprintf(stderr, format, args);
	va_end(args);
	WSACleanup();
	exit(1);
}


int start_server()
{

	WSADATA wsadata;
	
	printf("UDPSERVER Pid = %u Build at %s, %s\n",
		::GetCurrentProcessId(),
		__TIME__,
		__DATE__
		);
	if (WSAStartup(MAKEWORD(2,2), &wsadata) != 0)
		errexit("WSAStartup failed\n");
	
	CUDPServer server(8800);
	server.SetServiceHandler(new DocumentServerObject());
	server.Run();
	WSACleanup();
	return 0;

}