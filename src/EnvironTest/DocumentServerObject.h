// DocumentServerObject.h: interface for the DocumentServerObject class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DOCUMENTSERVEROBJECT_H__B76048F9_9BCA_41C7_8296_2DE737F2B034__INCLUDED_)
#define AFX_DOCUMENTSERVEROBJECT_H__B76048F9_9BCA_41C7_8296_2DE737F2B034__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "..\\ServiceFramework\\ServiceObject.h"
#include "DocumentProcessingApp.h"

class DocumentServerObject : public CServiceObject  
{

private:
	DocumentProcessingApp *app;
public:
	int Invoke(CServiceRequest *request, CServiceRequest *response);
	int InvokeText(char *text, int len, char *out, int *outlen);
	//调用自身的方法来处理请求
	//把结果封装在response中
	int OnEnd();
	int OnStart();
public:
	DocumentServerObject();
	virtual ~DocumentServerObject();

};

#endif // !defined(AFX_DOCUMENTSERVEROBJECT_H__B76048F9_9BCA_41C7_8296_2DE737F2B034__INCLUDED_)
