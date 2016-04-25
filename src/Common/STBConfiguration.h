// STBConfiguration.h: interface for the CSTBConfiguration class.
//
//////////////////////////////////////////////////////////////////////
/*===========================================================*\
  �ļ�: SerializableCertificate.h	
  ��Ȩ: ��ţ(����)�������޹�˾
  ����: 2005-09-05
  ����: ����Ĺ�����Ϊ�����ṩ��ݵĲ�����ʽ�������˻�����������Ϣ��ϸ��
  �ο�: CCertificateManager
  ����: zhangxl@channel.com
  �޶���¼:	

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
