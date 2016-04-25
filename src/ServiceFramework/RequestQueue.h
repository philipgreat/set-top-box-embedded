// RequestQueue.h: interface for the CRequestQueue class.
//
//////////////////////////////////////////////////////////////////////
/*===========================================================*\
  �ļ�: Parameters.h:	
  ��Ȩ: ��ţ(����)�������޹�˾
  ����: 2005-09-05
  ����: ������еİ�װ���࣬ͬ���������
  �ο�: 
  ����: zhangxl@channel.com
  �޶���¼:	

\*===========================================================*/
#if !defined(AFX_REQUESTQUEUE_H__876E559F_6D11_487D_B777_807CDF448B61__INCLUDED_)
#define AFX_REQUESTQUEUE_H__876E559F_6D11_487D_B777_807CDF448B61__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include <vector>
#include <algorithm>
#include <queue>
#include <string>

using namespace std;
#include <windows.h>
//������ʵ��������ͬ��������½��з���
//TODO: add critical section machanism here to control the access of 
//parallal threads
#include "ServiceRequest.h"
class CRequestQueue
{
private:
	//CServiceRequest *requst;
	queue<CServiceRequest *> requestQueue;
public:
	DWORD GetCount();
	CServiceRequest* Dequeue();
	void AddRequest(CServiceRequest *req);
	CRequestQueue();
	virtual ~CRequestQueue();
};

#endif // !defined(AFX_REQUESTQUEUE_H__876E559F_6D11_487D_B777_807CDF448B61__INCLUDED_)
