// SmartDocumentDispatcher.h: interface for the SmartDocumentDispatcher class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SMARTDOCUMENTDISPATCHER_H__DCB05D0F_5A6C_42CF_878B_4FA29AF14B55__INCLUDED_)
#define AFX_SMARTDOCUMENTDISPATCHER_H__DCB05D0F_5A6C_42CF_878B_4FA29AF14B55__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "DocumentHandle.h"
#include "OfficeDocumentProcessor.h"
class SmartDocumentDispatcher  
{
private:
	DocumentHandle **handles;
	OfficeDocumentProcessor **processors;

public:
	bool checkFile(const char* fileName);
	char * getFileExtName(const char* fileName);
	int proc(const char* fileName,const char* comment);
	DocumentHandle* allocHandler(const char *ext);
	DocumentHandle* getHandle(const char*ext);
	OfficeDocumentProcessor* allocProcessor(const char* ext);
	OfficeDocumentProcessor* getProcessor(const char*ext);
	int getIndex(const char *ext);
	SmartDocumentDispatcher();
	virtual ~SmartDocumentDispatcher();

};

#endif // !defined(AFX_SMARTDOCUMENTDISPATCHER_H__DCB05D0F_5A6C_42CF_878B_4FA29AF14B55__INCLUDED_)
