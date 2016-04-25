// UPPClient.h: interface for the CUPPClient class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_UPPCLIENT_H__41997B64_C3BB_4E82_B224_FE4E07AD0FB1__INCLUDED_)
#define AFX_UPPCLIENT_H__41997B64_C3BB_4E82_B224_FE4E07AD0FB1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <windows.h>
#include <Winsock.h>
#ifdef _WIN32_WCE
	#pragma comment(lib,"Ws2")
#else 
	#pragma comment(lib,"ws2_32")
#endif
class CUDPClient  
{
private:
	SOCKET sock;

public:
	void Close();
	int Send(const char* message);
	int Init();
	int Connect(const char* hostName,short port);
	CUDPClient();
	virtual ~CUDPClient();

};

#endif // !defined(AFX_UPPCLIENT_H__41997B64_C3BB_4E82_B224_FE4E07AD0FB1__INCLUDED_)
