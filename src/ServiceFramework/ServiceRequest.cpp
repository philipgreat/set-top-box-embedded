// ServiceRequest.cpp: implementation of the CServiceRequest class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ServiceRequest.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
#include <windows.h>
#define  REQ_FLAG   ("servreq")
CServiceRequest::CServiceRequest()
{
	memset(data,0x00,1024);
}

CServiceRequest::~CServiceRequest()
{

	
}



char * CServiceRequest::GetData() const
{
	return (char *)this->data;
}
void * CServiceRequest::SetValue(void *data, int length) 
{
	return memcpy(this->data,data,length<1024?length:1024);

}


