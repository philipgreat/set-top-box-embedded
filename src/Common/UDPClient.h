// UDPClient1.h: interface for the CUDPClient class.
//
//////////////////////////////////////////////////////////////////////
/*===========================================================*\
  文件: UDPClient.h	
  版权: 青牛(北京)技术有限公司
  日期: 2005-09-05
  描述: UDP客户端的包装类
  参考: CCertificateManager
  作者: zhangxl@channel.com
  修订记录:	

\*===========================================================*/
#if !defined(AFX_UDPCLIENT1_H__591B0F63_A6A9_4BD6_A7C6_F2646A84D291__INCLUDED_)
#define AFX_UDPCLIENT1_H__591B0F63_A6A9_4BD6_A7C6_F2646A84D291__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef  _WIN32_WCE
#pragma comment(lib,"ws2_32")
#include <winsock2.h>
#else
#pragma comment(lib,"ws2")
#include <winsock.h>
#endif
#include <windows.h>

#include <stdlib.h>
#include <string.h>
#include <windows.h>

class CUDPClient 
{
private:
	struct sockaddr_in serverAddr;
	SOCKET	clientSocket;
	char*	serverName;
	int		serverPort;
	int		localPort;
public:
#ifdef _WIN32
	static BOOL  InitEnv();
#endif
	int Recv(BYTE *buffer, int len,int timeout = 1);
	//总是包含超时设置
	int Send(BYTE *buffer, int len);
	int Connect();
	CUDPClient();
	CUDPClient(const char *serverName,unsigned short port);
	virtual ~CUDPClient();

};

#endif // !defined(AFX_UDPCLIENT1_H__591B0F63_A6A9_4BD6_A7C6_F2646A84D291__INCLUDED_)

