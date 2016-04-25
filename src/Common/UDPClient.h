// UDPClient1.h: interface for the CUDPClient class.
//
//////////////////////////////////////////////////////////////////////
/*===========================================================*\
  �ļ�: UDPClient.h	
  ��Ȩ: ��ţ(����)�������޹�˾
  ����: 2005-09-05
  ����: UDP�ͻ��˵İ�װ��
  �ο�: CCertificateManager
  ����: zhangxl@channel.com
  �޶���¼:	

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
	//���ǰ�����ʱ����
	int Send(BYTE *buffer, int len);
	int Connect();
	CUDPClient();
	CUDPClient(const char *serverName,unsigned short port);
	virtual ~CUDPClient();

};

#endif // !defined(AFX_UDPCLIENT1_H__591B0F63_A6A9_4BD6_A7C6_F2646A84D291__INCLUDED_)

