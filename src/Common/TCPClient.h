// TCPClient.h: interface for the CTCPClient class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TCPCLIENT_H__DD87CDA3_F4D2_486A_8F49_C3FB82A30A80__INCLUDED_)
#define AFX_TCPCLIENT_H__DD87CDA3_F4D2_486A_8F49_C3FB82A30A80__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CTCPClient  
{
private:
	int connectionTimeout;//milliseconds
	int sendTimeout;//milliseconds
	int recvTimeout;//milliseconds
public:
	int connect(char *hostName,unsigned short port);
	CTCPClient();
	virtual ~CTCPClient();

};

#endif // !defined(AFX_TCPCLIENT_H__DD87CDA3_F4D2_486A_8F49_C3FB82A30A80__INCLUDED_)
