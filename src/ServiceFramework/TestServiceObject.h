// TestServiceObject.h: interface for the CTestServiceObject class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TESTSERVICEOBJECT_H__8C58F049_46EC_40A1_A919_EF3E9580B9E6__INCLUDED_)
#define AFX_TESTSERVICEOBJECT_H__8C58F049_46EC_40A1_A919_EF3E9580B9E6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ServiceObject.h"
//该类仅仅用于测试
class CTestServiceObject : public CServiceObject  
{
public:
	int InvokeText(char *text, int len, char *out, int *outlen);
	int Invoke(CServiceRequest *request,CServiceRequest *response);
	//调用自身的方法来处理请求
	//把结果封装在response中
	int OnEnd();
	int OnStart();
	CTestServiceObject();
	virtual ~CTestServiceObject();
	
};

#endif // !defined(AFX_TESTSERVICEOBJECT_H__8C58F049_46EC_40A1_A919_EF3E9580B9E6__INCLUDED_)
