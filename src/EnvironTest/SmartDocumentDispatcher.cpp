// SmartDocumentDispatcher.cpp: implementation of the SmartDocumentDispatcher class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "SmartDocumentDispatcher.h"
#include "PowerPointProcessor.h"
#include "MSWordProcessor.h"
#include "ByteBuffer.h"
#include "DocumentHandle.h"
#include "TCPClient.h"
#include "PowerPointHandler.h"

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/utime.h>
#include <time.h>
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
static char *exts[]={"doc","ppt","txt","cpp","h","mp3",NULL,};
const int typecount = 40;
SmartDocumentDispatcher::SmartDocumentDispatcher()
{
	handles=new DocumentHandle*[typecount];
	memset(handles,0x00,sizeof(DocumentHandle*)*typecount);
	processors=new OfficeDocumentProcessor*[typecount];
	memset(processors,0x00,sizeof(OfficeDocumentProcessor*)*typecount);

}

SmartDocumentDispatcher::~SmartDocumentDispatcher()
{
	for(int i=0;i<typecount;i++){
			
		if(handles[i]!=NULL){
			delete  handles[i];
		}
		if(processors[i]!=NULL){
			delete  processors[i];
		}

	
	}
	delete handles;
	delete processors;
}

int SmartDocumentDispatcher::getIndex(const char *ext)
{
	char **p=exts;
	int index = -1;
	while((*p)!=NULL)
	{
		if(_strnicmp(*p,ext,strlen(*p)+1)==0){
			index = p-exts;
			break;
		}	
		p++;
		
	}
	return index;
}

OfficeDocumentProcessor* SmartDocumentDispatcher::getProcessor(const char *ext)
{
	OfficeDocumentProcessor* p=NULL;
	int index = getIndex(ext);
	if(index >=0 ){
		if(processors[index]==NULL){
			p = processors[index] = this->allocProcessor(ext);
		}else{
			p = processors[index] ;
		
		}
	}else{
		return NULL;
	}
	return p;
}


#define EQUALS(A,B) _strnicmp(A,B,strlen(A)+1)==0
OfficeDocumentProcessor* SmartDocumentDispatcher::allocProcessor(const char *ext)
{
	OfficeDocumentProcessor* p=NULL;
	if(EQUALS("doc",ext)){
		p = new MSWordProcessor;
		goto end;
	}
	if(EQUALS("ppt",ext)){
		p = new PowerPointProcessor;
		goto end;
	}

end:
	return p;
}

DocumentHandle* SmartDocumentDispatcher::allocHandler(const char *ext)
{
	DocumentHandle* p=NULL;
	if(EQUALS("doc",ext)){
		p = new DocumentHandle;
		goto end;
	}
	if(EQUALS("ppt",ext)){
		p = new PowerPointHandler;
		goto end;
	}
end:
	return p;
}


DocumentHandle* SmartDocumentDispatcher::getHandle(const char *ext)
{
	DocumentHandle* p=NULL;
	int index = getIndex(ext);
	if(index >=0 ){
		if(this->handles[index]==NULL){
			 p = this->handles[index] = this->allocHandler(ext);
		}else{
			 p = this->handles[index];
		}
	}
	return p;
}

int SmartDocumentDispatcher::proc(const char *fileName,const char* comment)
{
	char *fileext = getFileExtName(fileName);
	if(fileext==NULL){
		throw Exception("can not find the file externsion,do not know how to process it!\n");
	}
	if(this->getIndex(fileext)<0){
		throw Exception("the file is not recongnized to be processed!\n");
	}
	if(!this->checkFile(fileName)){
		throw Exception("the file does not exit, or the file is too big to send as email!");
	}
	DocumentHandle* handle;
	OfficeDocumentProcessor* processor;
	handle = this->getHandle(fileext);
	processor = this->getProcessor(fileext);
	if(handle==NULL||processor==NULL){
		throw Exception("error handle of processor is null");
	}
	processor->setHandler(handle);
	return processor->processDocument(fileName);

}

char * SmartDocumentDispatcher::getFileExtName(const char *fileName)
{
	//012345.
	//0123456789
	char *p=strrchr(fileName,'.');
	if(p!=NULL){
		
		if((unsigned int)(p-fileName)==strlen(fileName)-1){
			//file name end with '.'
			return NULL;
		}
		return p+1;
		//check if p matches end of filename;
	}else{
		return p;
	}
}

bool SmartDocumentDispatcher::checkFile(const char *fileName)
{
	struct stat filestat;
	if(stat(fileName,&filestat)==0){
		if(filestat.st_size>16*1024*1024){
			return false;
		}else{
			return true;
		}
	}else{
		return false;
	}
}
