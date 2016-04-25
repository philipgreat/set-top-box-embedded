// HttpUtil.cpp: implementation of the CHttpUtil class.
//
//////////////////////////////////////////////////////////////////////
#include "HttpUtil.h"
#include "PortHeader.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <memory.h>
#include <stdarg.h>
#include <ctype.h>



//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
#define SAFE_DELETE(x)    if(NULL!=x) {delete x;x=NULL;}
enum URL_PARSE_STATE{URL_START=0,
URL_PROT_START,
URL_PROT_IN,
URL_PROT_END,
URL_HOST_START,
URL_HOST_IN,
URL_HOST_END,
URL_PORT_START,
URL_PORT_IN,
URL_PORT_END,
URL_PATH_START,
URL_PATH_IN,
URL_PATH_END,
URL_END};

CHttpUtil::CHttpUtil()
{
	buffer=new char[1024*8];
	timeoutSeconds = 5;
}

CHttpUtil::~CHttpUtil()
{
	delete[] buffer;
}

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
#ifdef _WINDOWS_
static int SockConnect(char *domain,short port) 
{
	
	int white_sock; 
	int ret = 0;
	struct hostent * site; 
	struct sockaddr_in me; 
	
	memset(&me,0,sizeof(struct sockaddr_in)); 
	me.sin_addr.s_addr=inet_addr(domain);
	
	if (me.sin_addr.s_addr==(DWORD)-1){
		site = gethostbyname(domain);
		//printf("try to regard as hostname\n");
		memcpy(&me.sin_addr,site->h_addr_list[0],site->h_length);
	}
	
	white_sock = socket(AF_INET,SOCK_STREAM,0); 
	if (white_sock<0) return -1; 	
	//printf("white socket domain %s %d %d\n",domain,port,white_sock);
	
	//NOTE: found memory error here in pc edition 
	//this is a known bug in windows socket 
	
	unsigned long ul = 1;
	ret = ioctlsocket(white_sock, FIONBIO, (unsigned long*)&ul);
	if(ret>0) return ret;
	
	me.sin_family = AF_INET; 
	me.sin_port = htons(port); 
	ret = connect(white_sock,(struct sockaddr *)&me,sizeof(struct sockaddr));
	if(ret<0){
		struct timeval timeout ;
		fd_set set;
		
		FD_ZERO(&set);
		FD_SET(white_sock+1, &set);
		timeout.tv_sec = 5; //连接超时15秒
		timeout.tv_usec =0;
		ret = select(0, 0, &set, 0, &timeout);
		if ( ret <= 0 )
		{
			closesocket(white_sock);
			return -2;
			
		}
	}	
	
	return white_sock; 
}   
#else
//unix version of connect
static int SockConnect(char *domain,short port) 
{
	
	int white_sock; 
	int valopt; 
	int ret = 0;
	long arg; 
	struct hostent * site; 
	struct sockaddr_in me; 
	fd_set myset; 
	struct timeval tv; 
	socklen_t len = 0;
	
	
	memset(&me,0,sizeof(struct sockaddr_in)); 
	me.sin_addr.s_addr=inet_addr(domain);
	
	if (me.sin_addr.s_addr==(DWORD)-1){
		site = gethostbyname(domain);
		memcpy(&me.sin_addr,site->h_addr_list[0],site->h_length);
	}
	
	white_sock = socket(AF_INET,SOCK_STREAM,0); 
	if (white_sock<0) return -1; 	

	arg = fcntl(white_sock, F_GETFL, NULL); 
	arg |= O_NONBLOCK; 
	fcntl(white_sock, F_SETFL, arg); 

	me.sin_family = AF_INET; 
	me.sin_port = htons(port); 
	ret = connect(white_sock,(struct sockaddr *)&me,sizeof(struct sockaddr));
	if (ret < 0) { 
		if (errno == EINPROGRESS) { 
			tv.tv_sec = 5; 
			tv.tv_usec = 0; 
			FD_ZERO(&myset); 
			FD_SET(white_sock, &myset); 
			if (select(white_sock+1, NULL, &myset, NULL, &tv) > 0) { 
				len = sizeof(int); 
				getsockopt(white_sock, SOL_SOCKET, SO_ERROR, (void*)(&valopt), &len); 
				if (valopt) { 
					close(white_sock);
					return -3; 
				} 
			} else {			
				close(white_sock);
				return -2; 
			} 
		} else { 
			close(white_sock);
			return -3; 
		} 
	} 
	
	arg = fcntl(white_sock, F_GETFL, NULL); 
	arg &= (~O_NONBLOCK); 
	fcntl(white_sock, F_SETFL, arg);
	
	return white_sock; 
}   

#endif

static int SockSend(int sock,char *fmt,...) 
{ 
	char BUF[1024]; 
	va_list argptr; 
	va_start(argptr,fmt); 
	vsprintf(BUF,fmt,argptr); 
	va_end(argptr); 
	return send(sock,BUF,strlen(BUF),0); 
}
static int SeekDoubleReturn(const char *buffer,int len)
{
	char *p=(char*)buffer;
	int i=0;
	//printf("i = %s\n",buffer);
	while(memcmp(p,"\r\n\r\n",4) != 0 
		&&memcmp(p,"\n\r\n\r",4) !=0
		&&p-buffer<len){
		p++;
		i++;
	}
	return i;
}

int CHttpUtil::ProcessGet(const char *url,BYTE *retData,int *maxLen)
{
	int clientSocket; 
	int len=0;
	
	//if (argc<2) return 1; 
	DWORD dataSize=1024;
	unsigned short port=0;	
	
	char *phost;
	char *ppath;
	char *proto;
	
	this->ParseURL(url,&proto,&phost,&port,&ppath);
	clientSocket = SockConnect(phost,port); 

	if (clientSocket<0) {
		return clientSocket; 
	}

	SockSend(clientSocket,"GET /%s HTTP/1.1\r\nHost: suddy\r\nConnection: Close\r\n\r\n",ppath); 
	char *recvBuffer=new char[1024];
	memset(recvBuffer,0,dataSize);
	

	if ((len=recv(clientSocket,recvBuffer,dataSize-1,0))>0) { 
		//printf("%d\n%s\n",len,recvBuffer);
		int i=SeekDoubleReturn(recvBuffer,len);	
		int copyLen=(len-i-4)+1< *maxLen?(len-i-4)+1:*maxLen;
		*maxLen=copyLen;
		memcpy(retData,recvBuffer+i+4,copyLen);
		//printf("error on recv %s\n",retData);
	} 
	delete[] recvBuffer;
	
#ifdef _WINDOWS_
	closesocket(clientSocket);
#else
	close(clientSocket);
#endif
	return 0;
}

#ifdef VCPROJECT_DEBUG
#include <fstream>
#include <iostream>
using namespace std;
#endif


int CHttpUtil::ProcessPost(const char *url,POSTDATA_INFO &postData,BYTE *retData,int *maxLen)
{
	int clientSocket; 
	int len=0;
	
	//if (argc<2) return 1; 
	DWORD dataSize=2048;
	unsigned short port=0;	
	
	char *phost;
	char *ppath;
	char *proto;
	
	this->ParseURL(url,&proto,&phost,&port,&ppath);
	//
	clientSocket = SockConnect(phost,port); 
	
	if (clientSocket<0) {
		printf("error on connect; maybe you need use WSAStartup to initiate your env\n");
		
		return HTTP_ERROR_CONNECT; 
	}
	
	char *requestData = new char[1024];
	char *requestBody = new char[800];
	
	sprintf(requestBody,
		"<?xml version=\"1.0\" encoding=\"utf-8\"?>\r\n"
		"<soap:Envelope xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\" xmlns:xsd=\"http://www.w3.org/2001/XMLSchema\" xmlns:soap=\"http://schemas.xmlsoap.org/soap/envelope/\">\r\n"
		"<soap:Body>\r\n"
		"<Authenticate xmlns=\"http://tempuri.org/\">\r\n"
		"<authenticInfo>\r\n"
		"<CPID>%s</CPID>\r\n"
		"<UserId>%s</UserId>\r\n"
		"<Password>%s</Password>\r\n"
		"<ContentId>%u</ContentId>\r\n"
		"<ContentTypeId>%u</ContentTypeId>\r\n"
		"<CWID>%u</CWID>\r\n"
		"<CertifcateTypeId>%u</CertifcateTypeId>\r\n"
		"</authenticInfo>\r\n"
		"</Authenticate>\r\n"
		"</soap:Body>\r\n"
		"</soap:Envelope>\r\n",
		
		postData.cpID,
		postData.username,
		postData.password,
		postData.contentId,
		postData.contentType,
		postData.controlWordId,
		postData.certificateTypeID
		);
	
	sprintf(requestData,
		"POST /%s HTTP/1.1\r\n"
		"Host: %s\r\n"
		"Connection: Close\r\n"
		"Content-Type: text/xml; charset=utf-8\r\n"
		"Content-Length: %u\r\n"
		"SOAPAction: \"http://tempuri.org/Authenticate\"\r\n\r\n"
		"%s",
		
		ppath,
		phost,
		strlen(requestBody),
		requestBody
		);
	SockSend(clientSocket,requestData,ppath); 
	char *recvBuffer=new char[2048];
	memset(recvBuffer,0,dataSize);	
	//if ((len=recv(clientSocket,recvBuffer,dataSize-1,0))>0)
	while(((len=recv(clientSocket,recvBuffer,dataSize-1,0))>0))
	{ 
		printf("ecv  Length:%d  Data:%s\n",len,recvBuffer);
		int i=SeekDoubleReturn(recvBuffer,len);	
		DWORD copyLen=(len-i-4)+1< *maxLen?(len-i-4)+1:*maxLen;
		*maxLen=copyLen;
		memcpy(retData,recvBuffer+i+4,copyLen);
	} 
	
	delete[] requestData;
	delete[] requestBody;
	delete[] recvBuffer;
#ifdef _WINDOWS_
	closesocket(clientSocket);
#else
	close(clientSocket);
#endif
	return 0;
}



int CHttpUtil::ParseURL(const char *url, 
						char **proto,
						char **host, 
						unsigned short *port, 
						char **path)
{
	//该函数看起来有一些奇怪, 输入的指针只是指向了输入的字符串
	int		len=strlen(url)+1;
	char	*header=NULL;
	int		state=URL_START;
	char	*pproto=NULL;
	char	*phost=NULL;
	char	*ppath=NULL;
	char	*pport=NULL;
	
	*port=80;
	
	char *p=header=this->buffer;
	
	memcpy(this->buffer,url,len);
	//不要轻易改变该段代码,在更改之前需要经过比较详细的状态机分析
	
	while(p-header<len)
	{
		
		switch(state){
		case URL_START:
			state=URL_PROT_START;
			//break;
		case URL_PROT_START:
			pproto=p;
			state=URL_PROT_IN;
			break;
		case URL_PROT_IN:
			if(*p==':'){
				*p='\0';
				state=URL_PROT_END;
			}
			break;
		case URL_PROT_END:
			if(*p=='/'&&*(p-1)=='/')
			{
				*p='\0';
				*(p-1)='\0';
				state=URL_HOST_START;			
			}
			
			break;
		case URL_HOST_START:
			if(isalnum(*p)){
				phost=p;
				state=URL_HOST_IN;				
			}
			break;
		case URL_HOST_IN:
			if(*p==':'){
				//phost=p;
				*p='\0';				
				state=URL_HOST_END;				
				state=URL_PORT_START;
			}
			if(*p=='/'){
				//phost=p;
				*p='\0';
				//p--;
				state=URL_HOST_END;
				state=URL_PATH_START;				
			}
			break;
		case URL_PORT_START:
			if(isalnum(*p)){
				pport=p;
				state=URL_PORT_IN;
			}
			break;
		case URL_PORT_IN:
			if(*p=='/'){
				state=URL_PORT_END;
				state=URL_PATH_START;
				//p--;
			}
			break;
		case URL_PATH_START:
			ppath=p;
			state=URL_PATH_IN;		
			break;		
		case URL_PATH_IN:
			//ppath=p;
			//state=URL_PATH_IN;		
			break;
		default:			
			break;
			
		}
		//printf("%d %s \n",state,p);
		p++;
		
	}
	
	*host=phost;
	*proto=pproto;
	*path=ppath;
	*port=(pport==NULL?80:atoi(pport));
	
	//SAFE_DELETE(header);
	
	
	return 0;
}

void CHttpUtil::InitNetwork()
{
#ifdef _WINDOWS_
	WORD wVersionRequested;
	WSADATA wsaData;
	int err;
	BOOL stateWrite=FALSE;
	wVersionRequested = MAKEWORD( 1, 1 );
	err = WSAStartup( wVersionRequested, &wsaData );
#endif
}

void CHttpUtil::UninitNetwork()
{
#ifdef _WINDOWS_
	::WSACleanup();
#endif
}


void CHttpUtil::SetTimeout(int seconds)
{
	
}
