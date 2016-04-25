// RequestQueue.cpp: implementation of the CRequestQueue class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "RequestQueue.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CRequestQueue::CRequestQueue()
{

}

CRequestQueue::~CRequestQueue()
{

}

void CRequestQueue::AddRequest(CServiceRequest *req)
{
	//this class would not instantiate any servicequest!
	requestQueue.push(req);
}

CServiceRequest *CRequestQueue::Dequeue()
{
	CServiceRequest *outreq = NULL;
	if(!requestQueue.empty()){
		outreq = requestQueue.front();
		requestQueue.pop();
	}
	return outreq;
}

DWORD CRequestQueue::GetCount()
{
	return requestQueue.size();
}
