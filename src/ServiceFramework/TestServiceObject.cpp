// TestServiceObject.cpp: implementation of the CTestServiceObject class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TestServiceObject.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTestServiceObject::CTestServiceObject()
{

}

CTestServiceObject::~CTestServiceObject()
{
	
}

int CTestServiceObject::OnStart()
{
	return 0;
}

int CTestServiceObject::OnEnd()
{
	return 0;
}

int CTestServiceObject::Invoke(CServiceRequest *request, CServiceRequest *response)
{


	response->SetValue(request->GetData(),100);
	return 0;

}

int CTestServiceObject::InvokeText(char *text, int len, char *out, int *outlen)
{
	printf("ProcessRequest %s\n",text);
	memcpy(out,text,len);
	*outlen = len;

	return 0;
}
