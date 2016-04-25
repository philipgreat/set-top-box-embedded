// HttpUtil.h: interface for the CHttpUtil class.
//
//////////////////////////////////////////////////////////////////////
/*===========================================================*\
  文件: HttpUtil.h	
  版权: 青牛(北京)技术有限公司
  日期: 2005-09-05
  描述: 是用HTTP下载文件或者数据的类， 可以执行POST和GET请求
  参考: CDirectoryHelper , CJavaScriptGenerator
  作者: zhangxl@channel.com
  修订记录:	

\*===========================================================*/

#if !defined(AFX_HTTPUTIL_H__0C7CDE16_8D2C_4E4E_8F29_AC848033DF3D__INCLUDED_)
#define AFX_HTTPUTIL_H__0C7CDE16_8D2C_4E4E_8F29_AC848033DF3D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#include <windows.h>
#endif // _MSC_VER > 1000
#include "PortHeader.h"

#ifdef _WINDOWS_
	#ifdef  _WIN32_WCE
		#pragma comment(lib,"ws2")
		#include <winsock.h>
	#else
		#pragma comment(lib,"ws2_32")
		#include <winsock.h>
	#endif
#else
	/*berkerly and unix/unix-like systems*/
	#include<errno.h>
	#include<netdb.h>
	#include<netinet/in.h>
	#include<unistd.h>
	#include<arpa/inet.h>
	#include<sys/socket.h> 
	#include<sys/wait.h> 
	#include<sys/types.h>
	#include <fcntl.h>
#endif

struct POSTDATA_INFO
{
		char *username;
		char *password;
		DWORD controlWordId;
		DWORD contentType;
		DWORD contentId;
		DWORD certificateTypeID;
		char *cpID;
};

class CHttpUtil  
{

private:
	char *buffer;
	int timeoutSeconds;
public:
	void SetTimeout(int seconds);

	static void  UninitNetwork();
	static void  InitNetwork();
	

	enum HTTP_UTIL_STATE{HTTP_ERROR_CONNECT=1,HTTP_ERROR_DNSFAIL,HTTP_ERROR_REQFAIL};

	int ParseURL(const char*url,
		char **proto,
		char **host,unsigned short *port,char **path);
	int ProcessPost(const char *url,POSTDATA_INFO &postData,BYTE *retData,int *maxLen);
	int ProcessGet(
		const char *url, //URL TO PRC
		BYTE *retData,//in out, a sequence of data
		int *maxLen//in,out
		);
	CHttpUtil();
	virtual ~CHttpUtil();

};

#endif // !defined(AFX_HTTPUTIL_H__0C7CDE16_8D2C_4E4E_8F29_AC848033DF3D__INCLUDED_)
