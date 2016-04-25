// DocumentServerObject.cpp: implementation of the DocumentServerObject class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "DocumentServerObject.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
#include <stdio.h>

DocumentServerObject::DocumentServerObject()
{
	app = new DocumentProcessingApp();
}

DocumentServerObject::~DocumentServerObject()
{
	if(app!=NULL)delete app;
	
}

int DocumentServerObject::InvokeText(char *text, int len, char *out, int *outlen)
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
int DocumentServerObject::OnStart()
{
	return 0;
}

int DocumentServerObject::OnEnd()
{
	delete app;
	app=NULL;
	return 0;
}


int DocumentServerObject::Invoke(CServiceRequest *request, CServiceRequest *response)
{
	response->SetValue(request->GetData(),100);
	return 0;
}