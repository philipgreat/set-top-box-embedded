// BrokerServiceObject.cpp: implementation of the CBrokerServiceObject class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "BrokerServiceObject.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CBrokerServiceObject::CBrokerServiceObject()
{
	app = new CMSTBRequestBrokerApp();
}

CBrokerServiceObject::~CBrokerServiceObject()
{
	delete app;
	
}

int CBrokerServiceObject::InvokeText(char *text, int len, char *out, int *outlen)
{
	printf("ProcessRequest %s\n",text);

	app->ParseMessage(text,1024);
	app->Execute();
	app->GetReturnValue();
	int returnLength = strlen(app->GetReturnValue())+1;
	memcpy(out,app->GetReturnValue(),returnLength);
	*outlen = returnLength;


	//parse execute and return result 
	return 0;
}
int CBrokerServiceObject::OnStart()
{
	return 0;
}

int CBrokerServiceObject::OnEnd()
{
	return 0;
}


int CBrokerServiceObject::Invoke(CServiceRequest *request, CServiceRequest *response)
{
	response->SetValue(request->GetData(),100);
	return 0;
}