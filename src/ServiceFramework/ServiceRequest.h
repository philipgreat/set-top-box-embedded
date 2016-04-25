// ServiceRequest.h: interface for the CServiceRequest class.
//
//////////////////////////////////////////////////////////////////////
/*===========================================================*\
  �ļ�: SerializableCertificate.h	
  ��Ȩ: ��ţ(����)�������޹�˾
  ����: 2005-09-05
  ����: �������ʵ����࣬������������ڵ�֮�䴫��
  �ο�: CCertificateManager
  ����: zhangxl@channel.com
  �޶���¼:	

\*===========================================================*/
#if !defined(AFX_SERVICEREQUEST_H__0AEB3446_F970_4698_94C1_2B9C087DD581__INCLUDED_)
#define AFX_SERVICEREQUEST_H__0AEB3446_F970_4698_94C1_2B9C087DD581__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#ifdef _WIN32
#include <windows.h>
#else
typedef  DWORD  unsigned long
#endif

class CServiceRequest  
{
private:
	char data[1024];
public:
	void * SetValue(void *data, int length);
	char * GetData()  const;
	CServiceRequest();
	virtual ~CServiceRequest();

};

#endif // !defined(AFX_SERVICEREQUEST_H__0AEB3446_F970_4698_94C1_2B9C087DD581__INCLUDED_)
