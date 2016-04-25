// UDPServer1.cpp: implementation of the CUDPServer class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "UDPServer.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CUDPServer::CUDPServer()
{
	
}
CUDPServer::CUDPServer(unsigned short port):
	serviceHandler(NULL)
{
	serverAddr.sin_family      = AF_INET;
	serverAddr.sin_addr.s_addr = INADDR_ANY;
	serverAddr.sin_port        = htons(port);	
	
}
CUDPServer::CUDPServer(const char* bindIP,unsigned short port):
	serviceHandler(NULL)
{
	serverAddr.sin_family      = AF_INET;
	serverAddr.sin_addr.s_addr = inet_addr(bindIP);
	serverAddr.sin_port        = htons(port);	
}
CUDPServer::~CUDPServer()
{
	closesocket(serverSocket);	
}

int CUDPServer::Bind()
{
	serverSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (serverSocket == INVALID_SOCKET){
		printf("error in socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)");
		return CUDPServer::UDP_SOCKET_ERROR_BIND;
	}
	
	if (bind(serverSocket, (sockaddr *) &serverAddr, sizeof(sockaddr)) == SOCKET_ERROR)
	{
		printf("bind(serverSocket, (sockaddr *) &serverAddr, sizeof(sockaddr)) == SOCKET_ERROR");

		return CUDPServer::UDP_SOCKET_ERROR_BIND;
	}
	return 0;
}

int CUDPServer::Send(BYTE *buffer, int len)
{
	//send 
	return sendto(serverSocket, 
		(char*)buffer, 
		len, 
		0, (sockaddr *)
		&clientAddr, sizeof(clientAddr));	
}

int CUDPServer::Recv(BYTE *buffer, int len, int timeout)
{	
	//has timeout functions
	
	int result;
	struct timeval tv;
	fd_set readfds;
	int retLength=0;
	int fromlen = 0;
	FD_ZERO(&readfds);
	FD_SET(serverSocket, &readfds);
	tv.tv_sec=timeout;
	tv.tv_usec=0;

	result = select(serverSocket+1, &readfds, (fd_set*)NULL, (fd_set*)NULL, &tv);
	if(result > 0){
		memset(&clientAddr,0x00,sizeof(clientAddr));
		fromlen=sizeof(sockaddr);
		retLength = recvfrom(serverSocket, (char*)buffer, len, 0, (sockaddr *)&clientAddr, &fromlen);
		//error
	}else if(result == 0){
		//timeout
		return CUDPServer::UDP_SOCKET_RECV_TIMEOUT;
	}else{
		//error
		return CUDPServer::UDP_SOCKET_RECV_FATAL;

	}
	return retLength;
	
}


int CUDPServer::Run()
{
	this->Bind();
	char request[1024]={0};
	char response[1024]={0};

	while(1){
		//recv package
		//reuse a response
		//invoke the serviceobject method
		int state=0;
		memset(request,0,sizeof(request));
		memset(response,0,sizeof(response));

		state=this->Recv((BYTE*)&request,sizeof(request));
		
		if(state==CUDPServer::UDP_SOCKET_RECV_TIMEOUT){
			//printf("recv timeout \n");		
		}else if(state==CUDPServer::UDP_SOCKET_RECV_FATAL){
			//printf("recv fail \n");	
			Sleep(1000);
		}else if(state > 0){
			if(NULL!=this->serviceHandler){
				int returnLength = 0;
				
				serviceHandler->InvokeText(request,state,response,&returnLength);
				state=this->Send((BYTE*)&response,sizeof(response));
				
				if(strncmp("exit",request,strlen("exit")+1)==0){
					serviceHandler->OnEnd();
					break;				
				}
				
			}
		}	
	}
	return 0;
}

void CUDPServer::SetServiceHandler(CServiceObject *handler)
{
	this->serviceHandler=handler;
}
