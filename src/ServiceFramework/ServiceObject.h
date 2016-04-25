// ServiceObject.h: interface for the CServiceObject class.
//
//////////////////////////////////////////////////////////////////////
/*===========================================================*\
  文件: SerializableCertificate.h	
  版权: 青牛(北京)技术有限公司
  日期: 2005-09-05
  描述: 定义服务对象的基础类，继承该类则能够通过容器进行远程服务
  参考: CCertificateManager
  作者: zhangxl@channel.com
  修订记录:	

\*===========================================================*/
#if !defined(AFX_SERVICEOBJECT_H__E454754A_C99E_445D_A329_8FC114A705B2__INCLUDED_)
#define AFX_SERVICEOBJECT_H__E454754A_C99E_445D_A329_8FC114A705B2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "ServiceRequest.h"

class CServiceObject 
{
public:
	virtual int Invoke(CServiceRequest *request,CServiceRequest *response) = 0;
	virtual int InvokeText(char *text, int len, char *out, int *outlen) = 0;
	virtual int OnStart() = 0;
	virtual int OnEnd() = 0;
	CServiceObject();
	virtual ~CServiceObject();
};

#endif // !defined(AFX_SERVICEOBJECT_H__E454754A_C99E_445D_A329_8FC114A705B2__INCLUDED_)
