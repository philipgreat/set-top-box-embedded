// TCPClient.cpp: implementation of the CTCPClient class.
//
//////////////////////////////////////////////////////////////////////

#include "TCPClient.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTCPClient::CTCPClient()
{
	connectionTimeout = 5000;
	this->recvTimeout = 5000;
	this->sendTimeout = 5000;
}

CTCPClient::~CTCPClient()
{

}

int CTCPClient::connect(char *hostName, unsigned short port)
{
	return 0;
}
