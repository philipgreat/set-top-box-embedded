// STBConfiguration.h: interface for the CSTBConfiguration class.
//
//////////////////////////////////////////////////////////////////////
/*===========================================================*\
  文件: SerializableCertificate.h	
  版权: 青牛(北京)技术有限公司
  日期: 2005-09-05
  描述: 该类的功能是为配置提供便捷的操作方式，隐藏了机顶盒配置信息的细节
  参考: CCertificateManager
  作者: zhangxl@channel.com
  修订记录:	

\*===========================================================*/
#if !defined(AFX_STBCONFIGURATION_H__F1C16FFF_13D7_42CB_804C_A1B678F80D0A__INCLUDED_)
#define AFX_STBCONFIGURATION_H__F1C16FFF_13D7_42CB_804C_A1B678F80D0A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "URLParameters.h"


class CSTBConfiguration  
{
private:
	int templistCount;
	CURLParameters params;
public:
	char* GetCWServiceProviderURL() ;
	char* GetHomePage() ;
	char* GetLastViewURL();
	void SaveLastViewed(const char* url);
	char* GetPassword();
	char* GetUsername();
	int SetValue(const char* key, const char* value);
	int Parse(const char* data);
	void Report();
	char* GetCWProviderURL();
	char* GetValue(const char* key);
	int Save();
	int Load();
	CSTBConfiguration();
	virtual ~CSTBConfiguration();

};

#endif // !defined(AFX_STBCONFIGURATION_H__F1C16FFF_13D7_42CB_804C_A1B678F80D0A__INCLUDED_)
