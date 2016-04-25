// DocumentHandle.h: interface for the DocumentHandle class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DOCUMENTHANDLE_H__EF500FC5_1B0E_4FDF_8ED2_D1DE82C19DFD__INCLUDED_)
#define AFX_DOCUMENTHANDLE_H__EF500FC5_1B0E_4FDF_8ED2_D1DE82C19DFD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include <stdlib.h>
#include <stdio.h>
#include "ByteBuffer.h"
class DocumentHandle  
{

protected:
	char *documentName;
	char *title;
	ByteBuffer bytebuffer;
public:
	virtual int onProperty(char *name,char *value);
	virtual int onPage(int index, const char *text) ;
	virtual int startDocument(const char *filePath)  ;
	virtual int endDocument() ;
	DocumentHandle();
	virtual ~DocumentHandle();

};
#define A2W(W,A)     MultiByteToWideChar(936,0,(A),strlen((A))+1,(W),strlen((A))+1)
#define W2A(W,A)     WideCharToMultiByte(936,0,(W),wcslen((W)),(A),wcslen((W))*2,NULL,NULL);
#endif // !defined(AFX_DOCUMENTHANDLE_H__EF500FC5_1B0E_4FDF_8ED2_D1DE82C19DFD__INCLUDED_)
