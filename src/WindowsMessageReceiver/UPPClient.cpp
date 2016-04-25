// UPPClient.cpp: implementation of the CUPPClient class.
//
//////////////////////////////////////////////////////////////////////

#include "UPPClient.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CUDPClient::CUDPClient()
{
	WORD wVersionRequested;
	WSADATA wsaData;
	int err;
	
	wVersionRequested = MAKEWORD( 2, 2 );
	err = WSAStartup( wVersionRequested, &wsaData );
	if ( err != 0 ) {
		/* Tell the user that we could not find a usable */
		/* WinSock DLL.                                  */
		//return;
	}

	sock = INVALID_SOCKET;     
	// Datagram window socket
	
	
	
}

CUDPClient::~CUDPClient()
{
	WSACleanup();
}

int CUDPClient::Init()
{
	int iOptVal = 64;                   
	char szMessage[] = "Multicasting message!";                      
	// Sent message string
	TCHAR szError[100];               // Error message string
	if ((sock = socket (AF_INET, SOCK_DGRAM, 0)) == INVALID_SOCKET) 
	{
		wsprintf (szError, TEXT("Allocating socket failed! Error: %d"), 
			WSAGetLastError ());
		MessageBox (NULL, szError, TEXT("Error"), MB_OK);
		return FALSE;
	}
	//full file struct
	return 1;
}
int CUDPClient::Connect(const char *hostName, short port)
{

	
	struct   hostent *he;  
    struct   sockaddr_in svraddr;

	// Winsock implementation
	
	he=gethostbyname(hostName);
	memset(&svraddr,0,sizeof(svraddr));
	svraddr.sin_family=AF_INET;
	svraddr.sin_port=htons(port);
	svraddr.sin_addr=*((struct in_addr *)he->h_addr);
	//TCHAR szError[100];

	//wsprintf (szError, TEXT("Allocating socket failed! Error: %d, Socket: %d "), 
	//		WSAGetLastError (),sock);
	//MessageBox (NULL, szError, TEXT("Error"), MB_OK);


	connect(sock,
		(struct sockaddr *)&svraddr,
		sizeof(struct sockaddr));


	return 0;
}


int CUDPClient::Send(const char *message)
{
	int len=send(sock,message,strlen(message)+1,0);
	return len;
}

void CUDPClient::Close()
{	
	closesocket(sock);
}
