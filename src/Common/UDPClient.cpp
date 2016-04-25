// UDPClient1.cpp: implementation of the CUDPClient class.
//
//////////////////////////////////////////////////////////////////////

#include "UDPClient.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CUDPClient::CUDPClient()
{
	
}
CUDPClient::CUDPClient(const char* serverName,unsigned short serverPort)
{
	
	this->serverName=new char[20];
	//this->serverName=serverName;
	memcpy(this->serverName,serverName,20);
	this->serverPort=serverPort;
	closesocket(this->clientSocket);
}
CUDPClient::~CUDPClient()
{
	closesocket(this->clientSocket);
	delete this->serverName;
}

int CUDPClient::Connect()
{
	serverAddr.sin_addr.s_addr = inet_addr(serverName);
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port   = htons(serverPort);
	this->clientSocket = socket(AF_INET, SOCK_DGRAM, 0);
	int connstate = 0;
	connstate = connect(this->clientSocket,(struct sockaddr*)&serverAddr,sizeof(serverAddr));
	return connstate;
	
}

int CUDPClient::Send(BYTE *buffer, int len)
{
	struct sockaddr_in serverAddrUse;	
	serverAddrUse = serverAddr;
	int ret=sendto(this->clientSocket, 
		(char *)buffer, len, 0, 
		(struct sockaddr *)&serverAddrUse,
		sizeof(serverAddrUse));
	//printf("clientsocket = %d server port = %d\n",this->clientSocket,serverAddr.sin_port);
	return ret;
}

int CUDPClient::Recv(BYTE *buffer, int len, int timeout)
{
	int n = 0;
	int fromlen = 0;


	int result = 0;
	struct timeval tv;

	fd_set readfds ;
	FD_ZERO(&readfds);
	FD_SET(clientSocket, &readfds);
	tv.tv_sec=0;
	tv.tv_usec=10*1000;
	
	result = select(clientSocket+1, &readfds, (fd_set*)NULL, (fd_set*)NULL, &tv);	
	//this machanical works well under ce, setsockopt does not work well under 
	//berkely options ;)
	if(result>0){
		fromlen=sizeof(sockaddr);
		struct sockaddr_in serverAddrUse;
		serverAddrUse = serverAddr;
		n=recvfrom(clientSocket, (char*)buffer, len, 0, (sockaddr *)&serverAddrUse, &fromlen);
		//printf(" recv clientsocket = %d server port = %d\n",this->clientSocket,serverAddr.sin_port);
	}else if(result ==0){
		//timeout
		//printf("wait time out n = %d \n",result );
	}else{
		//error. in udp ,this case should not occur!!!	
	}
	return n;
}
#ifdef _WIN32
BOOL CUDPClient::InitEnv()
{
	WSADATA wsadata;	
	if (WSAStartup(MAKEWORD(2,2), &wsadata) != 0){
		return FALSE;
	}
	return TRUE;
}
#endif