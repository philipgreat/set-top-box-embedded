// PowerPointProcessor.cpp: implementation of the PowerPointProcessor class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "PowerPointProcessor.h"
#include <stdlib.h>
#include <ole2.h>
#include <stdio.h>
#include <odbcinst.h> // glaub dieses Include brauchste gar nicht 
#include <objbase.h>
#include <windows.h>
#pragma warning (disable:4146 4192 4786 4081)
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
#include "ByteBuffer.h"
PowerPointProcessor::PowerPointProcessor()
{

	app.CreateInstance(L"PowerPoint.Application");

}

PowerPointProcessor::~PowerPointProcessor()
{
	app->Quit();
	app  = NULL;
	delete this->documentName;
}

int PowerPointProcessor::processDocument(const char *fullDocumentPath)
{	
	OfficeDocumentProcessor::processDocument(fullDocumentPath);
	_PresentationPtr  pres;
	_SlidePtr		slide;
	ByteBuffer buffer;
	bstr_t ret;
	char *message=NULL;
	WCHAR *text=NULL;
	int count =0;

	

	if(this->handler==NULL) return 1;

	pres = app->GetPresentations()->Open(bstr_t(fullDocumentPath),msoFalse,msoTrue,msoFalse);
	if(pres!=NULL){	
		this->handler->startDocument(fullDocumentPath);	
	}else{
		return 2;
	}
	
	for(long i=1;i<=pres->GetSlides()->Count;i++){
		variant_t vi(i);
		slide = pres->GetSlides()->Item(vi);
		buffer.reset();
		for(long j=1;j<=slide->GetShapes()->Count;j++)
		{
			variant_t vj(j);
			try{
				ret= slide->Shapes->Item(vj)->TextFrame->TextRange->Text;
			
				text=(wchar_t*)ret;
				message=new char[wcslen(text)*2+2+10];
				count = W2A(text,message);	
				message[count]='\r';
				message[count+1]='\n';
				message[count+2]='0';
				buffer.put(message,strlen(message));
				
				delete message;			
			}catch (_com_error comerr) {
				
				//printf("%s\n",(char*)comerr.Description());
			} 
			
			
		}
		this->handler->onPage(i,buffer.getString());
	
	}
	this->handler->endDocument();
	
	slide = NULL;
	pres->Close();
	pres = NULL;	
	
	
	return 0;	
}


#if 0
		hr = lpdispProps->Invoke(0x4, IID_NULL, LOCALE_USER_DEFAULT,
            DISPATCH_PROPERTYGET, &dpNoArgs, &vResult, NULL, NULL);

		hr=dp->GetIDsOfNames(IID_NULL,  &ucPtr, 1, LOCALE_USER_DEFAULT, &dispID);

		PIDSI_TITLE;
		printf("here fails");
		HRESULT hr = dp->GetIDsOfNames((
			PIDSI_TITLE,
			IID_NULL,
			LOCALE_USER_DEFAULT,
            DISPATCH_PROPERTYGET, 
			NULL, 
			&vResult, 
			NULL,
			NULL);
		printf("here fails");
#endif
