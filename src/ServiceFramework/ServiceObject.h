// ServiceObject.h: interface for the CServiceObject class.
//
//////////////////////////////////////////////////////////////////////
/*===========================================================*\
  �ļ�: SerializableCertificate.h	
  ��Ȩ: ��ţ(����)�������޹�˾
  ����: 2005-09-05
  ����: ����������Ļ����࣬�̳и������ܹ�ͨ����������Զ�̷���
  �ο�: CCertificateManager
  ����: zhangxl@channel.com
  �޶���¼:	

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
