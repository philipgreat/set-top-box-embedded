// DocumentProcessingApp.h: interface for the DocumentProcessingApp class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DOCUMENTPROCESSINGAPP_H__33C53081_A1EE_48E2_9F41_945A285E55E1__INCLUDED_)
#define AFX_DOCUMENTPROCESSINGAPP_H__33C53081_A1EE_48E2_9F41_945A285E55E1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "..\\common\\URLParameters.h"
#include "SmartDocumentDispatcher.h"

class DocumentProcessingApp  
{
private:
	int  externalCommandSequenceNumber;
	char command[256];
	char returnValue[256];
	CURLParameters parameters;
	SmartDocumentDispatcher *dispatcher;
public:

	int processDocument(const char *fileName);
	int Execute();
	char * GetReturnValue();
	bool ParseMessage(char *message,int messageLength);
	DocumentProcessingApp();
	virtual ~DocumentProcessingApp();

};

#endif // !defined(AFX_DOCUMENTPROCESSINGAPP_H__33C53081_A1EE_48E2_9F41_945A285E55E1__INCLUDED_)
