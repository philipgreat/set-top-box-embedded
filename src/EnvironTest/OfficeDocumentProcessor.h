// OfficeDocumentProcessor.h: interface for the OfficeDocumentProcessor class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_OFFICEDOCUMENTPROCESSOR_H__0092B3CC_AFF0_4FEA_B398_3CEFCFBA0480__INCLUDED_)
#define AFX_OFFICEDOCUMENTPROCESSOR_H__0092B3CC_AFF0_4FEA_B398_3CEFCFBA0480__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "DocumentHandle.h"
#include "Exception.h"
class OfficeDocumentProcessor  
{
protected:
	DocumentHandle *handler;
	char *documentName;
public:
	virtual int processDocument(const char *fullDocumentPath);
	virtual int setHandler(DocumentHandle *handler);
	OfficeDocumentProcessor();
	virtual ~OfficeDocumentProcessor();

};

#endif // !defined(AFX_OFFICEDOCUMENTPROCESSOR_H__0092B3CC_AFF0_4FEA_B398_3CEFCFBA0480__INCLUDED_)
