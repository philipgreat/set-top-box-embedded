// MSWordProcessor.h: interface for the MSWordProcessor class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MSWORDPROCESSOR_H__459BE30C_1CCE_4435_AB4B_F7DB0DF2C099__INCLUDED_)
#define AFX_MSWORDPROCESSOR_H__459BE30C_1CCE_4435_AB4B_F7DB0DF2C099__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "OfficeDocumentProcessor.h"

#import "MSWORD.OLB" rename("ExitWindows","ExitWindowsEx"), rename_namespace("MSWord")
using namespace MSWord;

class MSWordProcessor : public OfficeDocumentProcessor
 
{
private:
	MSWord::_ApplicationPtr app;
	DocumentsPtr  documents;
public:
	int processDocument(const char*fullDocumentPath);
	MSWordProcessor();
	virtual ~MSWordProcessor();

};

#endif // !defined(AFX_MSWORDPROCESSOR_H__459BE30C_1CCE_4435_AB4B_F7DB0DF2C099__INCLUDED_)
