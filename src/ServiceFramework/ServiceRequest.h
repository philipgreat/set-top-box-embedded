// ServiceRequest.h: interface for the CServiceRequest class.
//
//////////////////////////////////////////////////////////////////////
/*===========================================================*\
  文件: SerializableCertificate.h	
  版权: 青牛(北京)技术有限公司
  日期: 2005-09-05
  描述: 定义服务实体的类，该数据在网络节点之间传输
  参考: CCertificateManager
  作者: zhangxl@channel.com
  修订记录:	

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
