// HttpHeader.cpp: implementation of the CHttpHeader class.
//
//////////////////////////////////////////////////////////////////////

#include "HttpHeader.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CHttpHeader::CHttpHeader()
{

}

CHttpHeader::~CHttpHeader()
{

}
/*

HTTP/1.1 200 OK
Server: Resin/2.1.16
ETag: "AAAAQYkO5bh"
Last-Modified: Mon, 05 Sep 2005 03:01:56 GMT
Expires: Mon, 12 Sep 2005 06:43:59 GMT
Content-Type: application/octet-stream
Content-Length: 26624
Date: Mon, 12 Sep 2005 06:43:54 GMT

*/
static const char *sampleHeader="HTTP/1.1 200 OK\r\n\
Server: Resin/2.1.16\r\n\
ETag: \"AAAAQYkO5bh\"\r\n\
Last-Modified: Mon, 05 Sep 2005 03:01:56 GMT\r\n\
Expires: Mon, 12 Sep 2005 06:43:59 GMT\r\n\
Content-Type: application/octet-stream\r\n\
Content-Length: 26624\r\n\
Date: Mon, 12 Sep 2005 06:43:54 GMT\r\n\r\n";

int CHttpHeader::Parse(const char *data)
{
	//
	char  *p=(char*)data;
	int startPos=0;
	int codeStartPos=0;
	//找到第一个空格，得到HTTP的返回码
	while(*p!=' '){
		startPos++;
		p++;
	}
	codeStartPos=startPos+1;

	while(*p!='\r'&&*p!='\r'){
		startPos++;
		p++;
	}
	//因该自动找到两个\r\n\r\n的地方，确定边界
	this->ParseExpression(data+startPos,':',';');
	return 0;
}

int CHttpHeader::Test()
{
	this->Parse(sampleHeader);
	this->Report();
	return 0;
}

int CHttpHeader::GetInt(const char* name)
{
	char* value=this->GetValue(name);
	//int i=0;
	BOOL isDigit=TRUE;
	char *p=value;
	while(*p){
		if(!isdigit(*p)){
			isDigit=FALSE;
			break;
		}
		p++;
	}
	if(isDigit){
		return atoi(value);
	}else{
		return 0;
	}
}