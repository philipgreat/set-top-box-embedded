// URL.cpp: implementation of the URL class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "URL.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
#include "BadArgumentException.h"
URL::URL()
{
	port = 80;
	this->host = NULL;
	this->location = "/";
	this->protocol = NULL;
	this->paramString="";
	usedLength = 0;

	memset(this->buffer,0x00,2048);
}
URL::URL(char *message)
{
	port = 80;
	this->host = NULL;
	this->location = "/";
	this->protocol = NULL;
	this->paramString="";
	memset(this->buffer,0x00,2048);

	this->parse(message);
}
URL::~URL()
{

}

int URL::parse(char *urlstring)
{
	int length = strlen(urlstring)+1;
	char *p = buffer;
	char *portString = NULL;
	int  hostPostion = 0; 
	int  portPostion = 0; 
	int  paramPostion = 0;
	
	strncpy(buffer,urlstring,length<2048?length:2048);
	usedLength=length;
	
	this->protocol = buffer;

	while(*p){	
		if(*p==':') {
			*p=0;
			p++;
			break;
		}
		p++;
	}
	if(*p!='/'||*(p+1)!='/'){
		throw BadArgumentException("bad url format");
	}
	p+=2;
	this->host=p;
	
	while(*p){	
		if(*p=='/') {
			*p=0;
			p++;
			this->location=p;
			break;
		}else if(*p==':'){
			*p=0;
			portString = p+1;
		}
		p++;
	}
	
	if(portString) this->port=(unsigned short)atol(portString);

	while(*p){
		if(*p=='?'){
			*p = 0;
			p++;
			this->paramString = p;
			break;
		}
		p++;		
	}


#if 0
	printf("%s://%s:%d/%s?%s\n",
		this->protocol,
		this->host,
		this->port,
		this->location,
		this->paramString);
#endif
	return 0;
}
unsigned short URL::getPort()const
{
	return this->port;	
}
char * URL::getHostName()const
{
	return this->host;
}

char * URL::getParameterString()const
{
	return this->paramString;
}

char * URL::getLocation() const
{
	return this->location;
}

char * URL::eval(const char *relativePath)
{
	//
	//http://10.130.100.23/lostpath/   cast/shell.asp
	char *p=this->buffer+this->usedLength+1;
	char *r=(char*)relativePath;

	if(this->isDefaultPort()){
		sprintf(p,"%s://%s/",this->protocol,this->host);
	}else{
		sprintf(p,"%s://%s:%u/",this->protocol,this->host,this->port);
	}
	int rootLength = strlen(p);

	if(*r=='/'){
		strncpy(p+rootLength,r+1,strlen(r+1)+1);
	}else if(*r=='.'&&*(r+1)=='/'){
		strncpy(p+strlen(p),+this->location,strlen(this->location)+1);
		char *parentPath = strrchr(p,'/');
		strncpy(parentPath+1,r+2,strlen(r+2)+1);
	}else{
		strncpy(p+strlen(p),+this->location,strlen(this->location)+1);
		char *parentPath = strrchr(p,'/');
		strncpy(parentPath+1,r,strlen(r)+1);
	}
	return p;
}
#define EQUALS(A,B) (strncmp(A,B,strlen(A))==0)
bool URL::isDefaultPort()
{
	bool defaultPort=false;
	if(EQUALS(this->protocol,"http")&&this->port==80){
		defaultPort = true;
		goto end;
	}
	if(EQUALS(this->protocol,"https")&&this->port==443){
		defaultPort = true;
		goto end;
	}
	if(EQUALS(this->protocol,"rtsp")&&this->port==554){
		defaultPort = true;
		goto end;
	}
	if(EQUALS(this->protocol,"ldap")&&this->port==389){
		defaultPort = true;
		goto end;
	}

end:
	return defaultPort;
}


unsigned short URL::getDefaultPort()
{
	int port=80;
	if(EQUALS(this->protocol,"http")){
		port = 80;
		goto end;
	}
	if(EQUALS(this->protocol,"https")){
		port = 443;
		goto end;
	}
	if(EQUALS(this->protocol,"rtsp")){
		port = 554;
		goto end;
	}
	if(EQUALS(this->protocol,"ldap")){
		port = 389;
		goto end;
	}

end:
	return port;
}
