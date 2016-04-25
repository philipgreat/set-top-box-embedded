// NetworkUtil.cpp: implementation of the CNetworkUtil class.
//
//////////////////////////////////////////////////////////////////////

#include "NetworkUtil.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CNetworkUtil::CNetworkUtil()
{

}

CNetworkUtil::~CNetworkUtil()
{

}

BOOL CNetworkUtil::SyncTime(const char *host, unsigned short port)
{
	int sock; 
	struct hostent * site; 
	struct sockaddr_in me; 
	BOOL ret = FALSE;

	memset(&me,0,sizeof(struct sockaddr_in)); 
	me.sin_addr.s_addr=inet_addr(host);
	
	if (me.sin_addr.s_addr==(DWORD)-1){
		site = gethostbyname(host);
		memcpy(&me.sin_addr,site->h_addr_list[0],site->h_length);
	}
	sock = socket(AF_INET,SOCK_STREAM,0); 
	//NOTE: found memory error here in pc edition 
	//this is a known bug in windows socket 
	me.sin_family = AF_INET; 
	me.sin_port = htons(port); 
	if(-1==connect(sock,(struct sockaddr *)&me,sizeof(struct sockaddr))){
		ret = FALSE;
	}
	//now we can read and write 
	char recvbuffer[32];
	//it is enough to hold the entire  time string like
	//20:20:10 2005-10-10
	//012345678901234567890
	//          1         2  
	if(recv(sock,recvbuffer,32,0)>0){
		//parse them and then set the system time the server offers
		short year = atoi(recvbuffer+9);
		short month = atoi(recvbuffer+14);
		short day = atoi(recvbuffer+17);
		short hour = atoi(recvbuffer+0);
		short minute = atoi(recvbuffer+3);
		short second = atoi(recvbuffer+6);

		SYSTEMTIME sysTime;
		sysTime.wYear = year;
		sysTime.wMonth = month;
		
		sysTime.wDay = day;
		sysTime.wHour = hour;
		sysTime.wMinute = minute;		
		sysTime.wSecond = second;
		sysTime.wMilliseconds = 0;
		ret =::SetLocalTime(&sysTime);
	}
	closesocket(sock);
	return ret;
}
void CNetworkUtil::InitNetwork()
{
#ifdef _WINDOWS_
	WORD wVersionRequested;
	WSADATA wsaData;
	int err;
	BOOL stateWrite=FALSE;
	wVersionRequested = MAKEWORD( 1, 1 );
	err = WSAStartup( wVersionRequested, &wsaData );
#endif
}

void CNetworkUtil::UninitNetwork()
{
#ifdef _WINDOWS_
	::WSACleanup();
#endif
}
