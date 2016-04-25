// MSWordProcessor.cpp: implementation of the MSWordProcessor class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MSWordProcessor.h"


#include <stdio.h>
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

MSWordProcessor::MSWordProcessor()
{
	
}

MSWordProcessor::~MSWordProcessor()
{

}


int MSWordProcessor::processDocument(const char *fullDocumentPath)
{	

	OfficeDocumentProcessor::processDocument(fullDocumentPath);
	_DocumentPtr document;
	ParagraphPtr paragraph;

	variant_t docname(fullDocumentPath);


	if(this->handler==NULL) return 1;
	this->handler->startDocument(fullDocumentPath);


	app.CreateInstance(L"Word.Application");
	try{
		document = app->Documents->Open (&docname);

	}catch (_com_error  comerr)  {
		char *msg=(char*)comerr.Description();
		//printf(msg);
		if(msg){
			printf(msg);
		}else{
			printf("error but we don\'t know the message!\n");
		}
		return 1;

	} 
	for(long i=1;i<=document->Paragraphs->Count;i++){
		variant_t vi(i);
		
		//printf("=====================================\n");
		bstr_t ret;
		try{
			paragraph = document->Paragraphs->Item(vi);
			ret= paragraph->GetRange()->Text;
			WCHAR *text=(wchar_t*)ret;
			char *message=new char[wcslen(text)*2+2];
			int count = W2A(text,message);	
			message[count]=0;
			this->handler->onPage(i,message);
			delete message;			
		}catch (_com_error   comerr)  {
			
		} 
		
	}	
	document->Close();	
	this->handler->endDocument();
	app->Quit();
	app=NULL;
	return 0;
	
}
