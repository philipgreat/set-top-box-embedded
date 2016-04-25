// RemoteLogger.h: interface for the CRemoteLogger class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_REMOTELOGGER_H__D4A49470_1CE9_493A_9BF1_1E4AA1528106__INCLUDED_)
#define AFX_REMOTELOGGER_H__D4A49470_1CE9_493A_9BF1_1E4AA1528106__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "UPPClient.h"
class CRemoteLogger  
{
private:
	char timeString[128];
	SYSTEMTIME m_SystemTime;
	CUDPClient client;
public:
	int Log(char ch);
	int Log(const char *fileName,int line,WCHAR *message);
	int Log(const char *file,int line,const char * message);
	int Log(const char* postion,int line,int value);
	int Log(const char *postion,int j);
	int Log(const char* postion,const char*message);
	int UpdateCurrentTime();
	int Log(WCHAR *message);
	int Log(const char * message);
	int Log(int i);

	CRemoteLogger();
	CRemoteLogger(char *hostName);
	virtual ~CRemoteLogger();

};

#endif // !defined(AFX_REMOTELOGGER_H__D4A49470_1CE9_493A_9BF1_1E4AA1528106__INCLUDED_)
