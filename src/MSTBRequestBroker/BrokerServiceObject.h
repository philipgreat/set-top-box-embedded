// BrokerServiceObject.h: interface for the CBrokerServiceObject class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BROKERSERVICEOBJECT_H__20C847D9_42EA_4B54_96DF_4B467D840173__INCLUDED_)
#define AFX_BROKERSERVICEOBJECT_H__20C847D9_42EA_4B54_96DF_4B467D840173__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "..\\ServiceFramework\\ServiceObject.h"
#include "MSTBRequestBrokerApp.h"
class CBrokerServiceObject : public CServiceObject  
{
private:
	CMSTBRequestBrokerApp *app;
public:
	int Invoke(CServiceRequest *request, CServiceRequest *response);
	int InvokeText(char *text, int len, char *out, int *outlen);
	//调用自身的方法来处理请求
	//把结果封装在response中
	int OnEnd();
	int OnStart();
	CBrokerServiceObject();
	virtual ~CBrokerServiceObject();

};

#endif // !defined(AFX_BROKERSERVICEOBJECT_H__20C847D9_42EA_4B54_96DF_4B467D840173__INCLUDED_)
