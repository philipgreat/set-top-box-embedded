// TCPClient.cpp: implementation of the TCPClient class.
//
//////////////////////////////////////////////////////////////////////

#include "TCPClient.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
#ifdef  _WIN32
#pragma comment(lib,"ws2_32")
#include <winsock2.h>
#include <windows.h>
#include <winsock.h>
#else
/*berkerly and unix/unix-like systems*/
#include<errno.h>
#include<netdb.h>
#include<netinet/in.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<sys/socket.h> 
#include<sys/wait.h> 
#include<sys/types.h>
#endif
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
enum SELECT_OPTION{
	SELECT_WRITE=0,	SELECT_READ=1,SELECT_CONNECT=2,
};

static void BuildAddr(struct sockaddr_in * server,const char *hostName, unsigned short port)
{
	struct hostent *site;
	char buffer[1024];
	memset(server,0,sizeof(struct sockaddr_in)); 
	
	server->sin_addr.s_addr = inet_addr(hostName);
	
	if(inet_ntoa(server->sin_addr)==NULL){
		site=gethostbyaddr((char   *)&server->sin_addr.s_addr,4,AF_INET); 
	}else{
		site=gethostbyname(hostName); 
	} 
	if(site==NULL){
		sprintf(buffer,"unkown host '%s' ",hostName);
		throw Exception(buffer);
	}
	memcpy(&server->sin_addr,site->h_addr_list[0],site->h_length);
	server->sin_family = AF_INET;
	server->sin_port   = htons(port);
}


TCPClient::TCPClient()
{
	this->timeout = 5;
}

TCPClient::~TCPClient()
{
	
}

int TCPClient::connect(const char *host, unsigned int port)
{
	int ret = 0;
	char buffer[1024];
	struct   sockaddr_in server;
	if(strlen(host)+1>1024){
		
		return -1;
	}
	this->sock = socket(AF_INET, SOCK_STREAM, 0);
	if(this->sock<=0){
		throw Exception("error create socket: socket(AF_INET, SOCK_STREAM, 0)");
	}
	
	this->port = port;
	strncpy(this->hostName,host,strlen(host)+1);
	BuildAddr(&server,this->hostName,port);
	//returns 0 if succeed
	ret = ::connect(this->sock,(struct sockaddr*)&server,sizeof(server));
	if(ret !=0){
		sprintf(buffer,"connect to '%s:%u' error",host,port);
		throw Exception(buffer);
	}
	return ret;
}

void TCPClient::close()
{
#ifdef _WIN32
	closesocket(this->sock);
#else
	close(this->sock);
#endif
	
}

int TCPClient::send(const char *data, int length)
{
	
	int ret = 0;

	int result = this->waitForPrepared(0);

	if(result>0){
		ret=::send(this->sock, (char *)data, length, 0);
	}else if(result ==0){
		throw Exception("send time out!");
	}else{
		throw Exception("socket error!");
	}
	return ret;
	
}

int TCPClient::recv(char *data, int length)
{
	int ret = 0;

	int result = this->waitForRead();
	if(result>0){
		ret=::recv(this->sock, (char *)data, length, 0);
	}else if(result ==0){
		//timeout
		//printf("wait time out n = %d \n",result );
		throw Exception("recv time out!");
	}else{
		throw Exception("socket error!");
	}


	return ret;
}

void TCPClient::setTimeout(int timeout)
{
	this->timeout = timeout;
}
#ifdef _WIN32
void init_environment()
{
	WSADATA  wsd;
	if (WSAStartup(0x202,&wsd) != 0)
	{
		throw Exception("failed to load windows sock!");
		return;
	}
}
#endif

int TCPClient::waitForPrepared(int method)
{
	int result = 0;
	struct timeval tv;

	fd_set fds ;
	FD_ZERO(&fds);
	FD_SET(this->sock, &fds);
	tv.tv_sec=this->timeout;
	tv.tv_usec=0;
	switch(method){
	case  SELECT_READ:
		result = select(this->sock+1, &fds,  (fd_set*)NULL,(fd_set*)NULL, &tv);
		break;
	case  SELECT_WRITE:
		result = select(this->sock+1, (fd_set*)NULL, &fds, (fd_set*)NULL, &tv);
		break;
	case  SELECT_CONNECT:
		result = select(this->sock+1,  (fd_set*)NULL,(fd_set*)NULL, &fds, &tv);
		break;
	default:
		throw Exception("bad method in waitForPrepared()");
	}
	return result;
}

int TCPClient::waitForRead()
{
	return this->waitForPrepared(SELECT_READ);
}

int TCPClient::waitForWrite()
{
	return this->waitForPrepared(SELECT_WRITE);
}

int TCPClient::waitForConnect()
{
	return this->waitForPrepared(SELECT_CONNECT);
}
