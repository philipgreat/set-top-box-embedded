// DocumentProcessingApp.cpp: implementation of the DocumentProcessingApp class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "DocumentProcessingApp.h"
#include <stdio.h>
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
#define ISFUNCTION(x)	strncmp((x),this->command,strlen((x))+1)
static  int counter = 0;

DocumentProcessingApp::DocumentProcessingApp()
{
	externalCommandSequenceNumber = 0;
	dispatcher=NULL;
	
}

DocumentProcessingApp::~DocumentProcessingApp()
{
	if(dispatcher!=NULL){delete dispatcher;}
}


bool DocumentProcessingApp::ParseMessage(char *message, int messageLength)
{
	
	int len=strlen(message)+1;
	char *p = NULL;	

	char *head = new char[len];
	int  commandLength = 0;
	int  seqnumberLength = 0;

	this->externalCommandSequenceNumber = 0;
	memset(this->command,0,sizeof(this->command));

	p = head ;
	strncpy(head, message, len);
	while(*p!='@'&&p-head<len)
	{
		seqnumberLength++;
		p++;	
	}
	
	if(p-head + 1>len){
		strncpy(this->command,head,len);
		strncpy(this->returnValue,head,len);

		goto end;
	}

	*p=0;

	this->externalCommandSequenceNumber = atol(head);
	commandLength = 0;
	while(*p!=' '&&p-head<len)
	{
		commandLength++;
		p++;
	}
	if(p-head<len){
		*p=0;
	}
	if(commandLength>0){
		
		strncpy(this->command,head+seqnumberLength+1,commandLength);
	}
	if(p-head<len){

		*p=0;
		//printf("%s\n",p+1);
		this->parameters.Parse(p+1);
		//this->parameters.Report();
	}
end:
	delete head;
	return true;
}


char * DocumentProcessingApp::GetReturnValue()
{
	return this->returnValue;
}

int DocumentProcessingApp::Execute()
{
	int  ret = 1;
	int  state = 0;
	bool isIntegerReturned = true;
	printf("command = %30s\t",this->command);
	if(!ISFUNCTION("processDocument")){		
		char *fileName=parameters.GetValue("fileName");	
		printf("filename= %s\n",fileName);
		ret = this->processDocument(fileName);
		goto end;
	}
	//if it is int value returned;
	//todo
end:
	if(isIntegerReturned){
		sprintf(this->returnValue,"%d@%s=%d",
			this->externalCommandSequenceNumber,
			this->command,
			state);
		
	}else{
		sprintf(this->returnValue,"%d@%s=%s",
			this->externalCommandSequenceNumber,
			this->command,
			ret?"true":"false");
	}
	counter++;
	return ret;
}

int DocumentProcessingApp::processDocument(const char *fileName)
{
	int ret = 0;
	if(dispatcher==NULL){
		dispatcher = new SmartDocumentDispatcher;
	}
	try{	
		ret = dispatcher->proc(fileName,"no");
	}catch(Exception e){
		e.report();
	}

	return ret;
}
