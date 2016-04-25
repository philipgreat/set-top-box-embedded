// OfficeDocumentProcessor.cpp: implementation of the OfficeDocumentProcessor class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "OfficeDocumentProcessor.h"
#include <string.h>
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

OfficeDocumentProcessor::OfficeDocumentProcessor()
{
	this->handler = NULL;
	this->documentName=new char[MAX_PATH];
}

OfficeDocumentProcessor::~OfficeDocumentProcessor()
{

}
OfficeDocumentProcessor::setHandler(DocumentHandle *handler)
{
	this->handler= handler;
	return 0;	
}

int OfficeDocumentProcessor::processDocument(const char *fullDocumentPath)
{
	strncpy(this->documentName,fullDocumentPath,MAX_PATH);	
	return 0;
}
