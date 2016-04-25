// UpdateTestCases.cpp: implementation of the UpdateTestCases class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "UpdateTestCases.h"
#include "WebDateTime.h"
#include "URL.h"
#include "TCPClient.h"
#include <windows.h>
#include "Exception.h"
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

UpdateTestCases::UpdateTestCases()
{

}

UpdateTestCases::~UpdateTestCases()
{

}


int UpdateTestCases::run(int argc, char ** argv)
{
	int ret = 0;
	SHOW_TEST_BANNER;
	ret = TestSuite::run(argc,argv);
	return ret;
}

int UpdateTestCases::tcp_client_connect(int argc, char* argv[])
{
	int ret = 0;
	TCPClient *client=new TCPClient();
	ret = client->connect("suddy.channel.com",80);
	client->close();
	delete client;
	return ret;

}


int UpdateTestCases::web_time(int argc, char* argv[])
{
	CWebDateTime time;
	char *p="Thu, 23 Nov 2006 02:41:17 GMT";
	time.parse(p,strlen(p));
	SYSTEMTIME systime;
	::GetSystemTime(&systime);
	CWebDateTime time2(
		systime.wYear,
		systime.wMonth,
		systime.wDay,
		systime.wDayOfWeek,
		systime.wHour,
		systime.wMinute,
		systime.wSecond,
		systime.wMilliseconds);

	bool c=time.before(&time2);
	
	return !c;

}
#include "HttpDownloader.h"
int UpdateTestCases::http_is_update(int argc, char* argv[])
{
	char *url="http://suddy.channel.com/readme.txt";
	char *fileName="d:\\settopbox\\readme.txt";	
	
	return HttpDownloader::isUpdated(url,fileName);

}
#include <time.h>

int UpdateTestCases::http_no_update(int argc, char* argv[])
{
	char *url="http://suddy.channel.com/readme.txt";
	char *fileName = "d:\\settopbox\\readme.txt";
	int size=0;
	int downloadsize=0;	
	int c=clock();
	int ret = 0;
	if((size=HttpDownloader::getResourceSize(url))>0){
		if(HttpDownloader::isUpdated(url,fileName)){
			//printf("download\n");
			downloadsize = HttpDownloader::downloadFile(url,fileName);			
		}
	}

	return downloadsize-4;

}

int UpdateTestCases::http_update(int argc, char* argv[])
{
	char *url="http://suddy.channel.com/readme.txt";
	char *realPath = "d:\\resin-2.1.16\\doc\\readme.txt";
	char *fileName = "d:\\settopbox\\readme.txt";
	int size=0;
	int downloadsize=0;	
	int c=clock();
	int ret = 0;
	FILE *file=fopen(realPath,"wb");
	fwrite(&c,sizeof(int),1,file);
	fclose(file);
	TestSuite::delay(500);
	if((size=HttpDownloader::getResourceSize(url))>0){
		if(HttpDownloader::isUpdated(url,fileName)){
			//printf("download\n");
			downloadsize = HttpDownloader::downloadFile(url,fileName);			
		}
	}
	file=fopen(fileName,"rb");
	fread(&ret,sizeof(int),1,file);
	fclose(file);

	return abs(ret-c)+abs(downloadsize-size);

}

int UpdateTestCases::url_basic(int argc, char* argv[])
{
	int ret = 0;
	URL url;
	url.parse("http://rtx.tencent.com/download/rtx3.61/rtx_361_doc.zip");
	return ret;
}

#define POST_REQ_FORMAT 	\
"POST /%s HTTP/1.0\r\n\
User-Agent: TestWeBrowser\r\n\
Encoding: GBK\r\n\
Content-Length: %u\r\n\r\n"

#define POST_CONTENT \
"sendto=suddychang@gmail.com\r\n\
title=testmail\r\n\
location=f:\\document\\001.ppt\r\n\
from=zhangxl@channelsoft.com\r\n\r\n\
text from <doc src=f:\\document\\001.ppt>"

int UpdateTestCases::doc_client(int argc, char* argv[])
{
	int ret = 1;
	char buffer[1024];
	int  spliterPostion = 0;
	int contentLength = 0;
	contentLength=strlen(POST_CONTENT);

	URL url("http://suddy.channel.com/workflow/SmartMail.jsp");
	TCPClient *client=new TCPClient();
	ret = client->connect(url.getHostName(),url.getPort());
	sprintf(buffer,POST_REQ_FORMAT,url.getLocation(),contentLength);
	ret = client->send(buffer,strlen(buffer))==21?0:1;
	ret = client->send(POST_CONTENT,contentLength)==21?0:1;
	printf("%s\n",POST_CONTENT);
	while(ret=client->recv(buffer,1))
	{
		char r=*buffer;
		if(r=='\r'||r=='\n'){
			spliterPostion++;
		}else{
			spliterPostion=0;
		}
		if(spliterPostion>=4){
			break;
		}
	}
	int count = 0;
	while(1)
	{
		try{
			ret=client->recv(buffer,1024);
	
			if(ret==0) {
				break;
			}else if(ret>0){
				buffer[ret] = 0;
				//printf("%s\n",buffer);
			}
			count+=ret;
		}catch(Exception &e){
			e.report();
		}
	}
	//printf("\n%d writen\n",count);

	client->close();
	delete client;	
	return count-18;
}



#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
int UpdateTestCases::doc_file_size(int argc, char* argv[])
{
	int ret = 156;
	char *testFile="f:\\good\\text.txt";
	struct stat file_stats;
	if(stat(testFile, &file_stats)){
		return -1;
	}
	return 189-file_stats.st_size;

}
#define TEST_STRING "1234567"
inline char *stringcopy(char *dest, const char *src,long length)
{
	char *p = dest;
	char *end = (char*)src+length;
	while (src <= end){
		*(dest++) = *(src++);
	}
	return p;
}

#include <math.h>

int UpdateTestCases::test_basic(int argc,char *argv[])
{
	char buffer[0x20];
	double c = 0.0;
	int length = strlen(TEST_STRING)+1;
	for(int i=0;i<1024*1024*10;i++){
		strncpy(buffer,TEST_STRING,length);
		//c = cos(i);
	}
	return 0;
}
int UpdateTestCases::doc_send_file(int argc, char* argv[])
{
	int ret = 1;
	char buffer[1024];
	int  spliterPostion = 0;
	int contentLength = 0;
	struct stat file_stats;
	FILE *file = NULL;
	char *testFile="f:\\good\\cache.txt";
	if(stat(testFile, &file_stats)){
		return -1;
	}
	file = fopen(testFile,"rb");

	contentLength=file_stats.st_size;

	URL url("http://suddy.channel.com/workflow/SmartMail.jsp");

	TCPClient *client=new TCPClient();
	ret = client->connect(url.getHostName(),url.getPort());
	sprintf(buffer,POST_REQ_FORMAT,url.getLocation(),contentLength);
	ret = client->send(buffer,strlen(buffer))==21?0:1;

	int read = 0;
	while(read = fread(buffer,1,1,file)>0){
		client->send(buffer,read);		
	}
	fclose(file);
	while(ret=client->recv(buffer,1))
	{
		char r=*buffer;
		if(r=='\r'||r=='\n'){
			spliterPostion++;
		}else{
			spliterPostion=0;
		}
		if(spliterPostion>=4){
			break;
		}
	}
	int count = 0;
	while(1)
	{
		try{
			ret=client->recv(buffer,1024);
	
			if(ret==0) {
				break;
			}else if(ret>0){
				buffer[ret] = 0;				
			}
			count+=ret;
		}catch(Exception &e){
			e.report();
		}
	}
	//printf("\n%d writen\n",count);

	client->close();
	delete client;	
	return count-20;

}

int UpdateTestCases::url_eval(int argc, char* argv[])
{
	int ret = 0;
	URL url;
	char *href = "http://localhost/cast/1000.jsp";
	char *path = "./1234.jsp";
	url.parse(href);
	//printf("%s\n",url.eval(path));
	ret += strcmp("http://localhost/cast/1234.jsp",url.eval(path));

	href = "http://localhost:8080/cast/1000.jsp";
	path = "./1234.jsp";
	url.parse(href);
	//printf("%s\n",url.eval(path));
	ret += strcmp("http://localhost:8080/cast/1234.jsp",url.eval(path));

	href = "http://localhost:8080/cast/1000.jsp";
	path = ".12032/1234.jsp";
	url.parse(href);
	//printf("%s\n",url.eval(path));
	ret += strcmp("http://localhost:8080/cast/.12032/1234.jsp",url.eval(path));
	return ret;

}

int UpdateTestCases::http_resource_size(int argc, char* argv[])
{
	int size = HttpDownloader::getResourceSize("http://suddy.channel.com/");
	return !(size>0);
}
#define TEST_REQ_STRING 	"GET / HTTP/1.0\r\nUser-Agent: TestWeBrowser\r\n\r\n"
int UpdateTestCases::tcp_client_send(int argc, char* argv[])
{
	int ret = 0;
	TCPClient *client=new TCPClient();

	ret = client->connect("suddy.channel.com",80);
	ret = client->send(TEST_REQ_STRING,
		strlen(TEST_REQ_STRING))==strlen(TEST_REQ_STRING)?0:1;
	client->close();

	delete client;	
	return ret;

}


int UpdateTestCases::tcp_client_recv(int argc, char* argv[])
{
	int ret = 1;
	char buffer[20];
	TCPClient *client=new TCPClient();
	try{
		ret = client->connect("suddy.channel.com",80);
		ret = client->send(TEST_REQ_STRING,strlen(TEST_REQ_STRING))==21?0:1;
		ret = client->recv(buffer,20)==20?0:1;
		client->close();
	}catch(Exception &e){
		e.report();
		ret = 0;
	}
	delete client;
	return ret;

}
int UpdateTestCases::tcp_client_read(int argc, char* argv[])
{
	int ret = 1;
	char buffer[200];
	TCPClient *client=new TCPClient();
	ret = client->connect("suddy.channel.com",80);
	ret = client->send(TEST_REQ_STRING,strlen(TEST_REQ_STRING))==21?0:1;
	
	while(ret=client->recv(buffer,190))
	{
		buffer[ret]=0;
		//printf("%s \n",buffer);
	}

	client->close();
	delete client;
	
	return ret;

}
#define TEST_REQ_FORMAT 	"GET /%s HTTP/1.0\r\nUser-Agent: TestWeBrowser\r\n\r\n"
//http://rtx.tencent.com/download/rtx3.61/rtx_361_doc.zip
static bool isStateOK(char *buffer)
{
	//
	//HTTP/1.1 200 OK
	char *p=strchr(buffer,' ');
	char ch = *(p+1);
	if(ch=='2'){
		return true;
	}else{
		return false;
	}
}
static int getContentLength(char *buffer)
{
	//
	//HTTP/1.1 200 OK
	char *p=strchr(buffer,':');
	char *lengthString = (p+2);
	return atol(lengthString);

}

int UpdateTestCases::http_header(int argc, char* argv[])
{
	int ret = 1;
	char buffer[1024];
	int  spliterCounter = 0;
	int  counter = 0;

	URL url("http://suddy.channel.com/settopbox/stbplayer.exe");
	TCPClient *client=new TCPClient();
	ret = client->connect(url.getHostName(),url.getPort());
	sprintf(buffer,TEST_REQ_FORMAT,url.getLocation());
	ret = client->send(buffer,strlen(buffer))==21?0:1;

	char ch = '0';

	while(ret=client->recv(&ch,1))
	{
	
		if(ch=='\r'||ch=='\n'){
			spliterCounter++;
		}else{
			buffer[counter] = ch;
			counter++;
			spliterCounter=0;
		}
		if(spliterCounter == 2){
			buffer[counter] = 0;
			counter = 0;
		}
		if(spliterCounter>=4){
			break;
		}
	}
	int count = 0;

	client->close();
	delete client;
	
	return (ret - 1);

}


int UpdateTestCases::tcp_url_download(int argc, char* argv[])
{
	int ret = 1;
	char buffer[1024];
	FILE *file;
	int  spliterPostion = 0;
	
	file=fopen("d:\\settopbox\\index.html","wb");
	if(file==NULL){
		return 8;
	}

	URL url("http://rtx.tencent.com/download/rtx3.61/rtx_361_doc.zip");
	TCPClient *client=new TCPClient();
	ret = client->connect(url.getHostName(),url.getPort());
	sprintf(buffer,TEST_REQ_FORMAT,url.getLocation());
	ret = client->send(buffer,strlen(buffer))==21?0:1;

	while(ret=client->recv(buffer,1))
	{
		char r=*buffer;
		if(r=='\r'||r=='\n'){
			spliterPostion++;
		}else{
			spliterPostion=0;
		}
		if(spliterPostion>=4){
			break;
		}
	}
	int count = 0;
	while(1)
	{
		try{
			ret=client->recv(buffer,1024);
			if(ret==0) break;
			fwrite(buffer,1,ret,file);
			count+=ret;
		}catch(Exception &e){
			e.report();
		}
	}
	printf("\n%d writen\n",count);

	fclose(file);
	client->close();
	delete client;
	
	return ret;

}
int UpdateTestCases::tcp_client_recv_timeout(int argc, char* argv[])
{
	int ret = 1;
	char buffer[20];
	TCPClient *client=new TCPClient();
	ret = client->connect("suddy.channel.com",80);
	//ret = client->send(TEST_REQ_STRING,strlen(TEST_REQ_STRING))==21?0:1;
	try{
		ret = client->recv(buffer,20)==20?0:1;
	}catch(Exception &e){
		e.report();
		ret = 0;
	}
	client->close();
	delete client;
	return ret;

}


int UpdateTestCases::tcp_client_unkown_host(int argc, char* argv[])
{
	int ret = 1;
	TCPClient *client=new TCPClient();
	try{
		ret = client->connect("suddy.channel.com1",81);
		ret = client->send(TEST_REQ_STRING,strlen(TEST_REQ_STRING))==21?0:1;
	}catch(Exception &e){
		e.report();
		ret = 0;
	}
	client->close();
	delete client;
	return ret;

}


const char *requstFormat="http://suddy.channel.com/ajax/testcase.jsp?class=%s&methods=%s";
 
int UpdateTestCases::split_file(int argc, char *argv[])
{
	//
	char *url = "http://suddy.channel.com/ajax/testcase.jsp?class=LoveTestCases&methods=testLove+testHate+testHave";
	HttpDownloader::splitNetfile(url);
	
	return 0;
}


int UpdateTestCases::test_gen_cases(int argc, char *argv[])
{
	//char *url = "http://suddy.channel.com/ajax/testcase.jsp?class=LoveTestCases&methods=testLove+testHate+testHave";
	char requestURL[1024*4];
	char message[1024]={0};
	char *className;
	if(argc<3){
		printf("usage: testcase <TestCaseClass> <method1> <method2>\n");
		return 1;
	}
	className = argv[1];

	for(int i=2;i<argc-1;i++){
		strcat(message,argv[i]);
		strcat(message,"+");
	}
	strcat(message,argv[i]);
	sprintf(requestURL,requstFormat,className,message);
	HttpDownloader::splitNetfile(requestURL);
	return 0;
}

int UpdateTestCases::refresh_desktop(int argc, char *argv[])
{
	int ret = 0;
#if 0
	HWND hDesktop = FindWindowEx(FindWindowEx(
		FindWindow("Progman", "Program Manager"),
		0, "SHELLDLL_DefView", ""), 0,
		"SysListView32", "FolderView") ;
	::PostMessage(hDesktop,WM_KEYDOWN,VK_F5,0);
	::PostMessage(hDesktop,WM_KEYUP,VK_F5,0);
#endif	

	return ret;
}

void UpdateTestCases::registerTestCases()
{
	//T(UpdateTestCases::http_is_update);
	//T(UpdateTestCases::doc_client);
#if 1
	T(UpdateTestCases::test_update_manager);
	T(UpdateTestCases::test_set_home);
	T(UpdateTestCases::test_upgrade);
	T(UpdateTestCases::test_update_item);

#endif	
	//T(UpdateTestCases::split_file);	
	//T(UpdateTestCases::test_gen_cases);

	
#if 0
	T(UpdateTestCases::refresh_desktop);	
	T(UpdateTestCases::test_basic);
	//T(UpdateTestCases::doc_send_file);
	T(UpdateTestCases::doc_file_size);	
	T(UpdateTestCases::http_update);	
	T(UpdateTestCases::http_no_update);

	T(UpdateTestCases::tcp_client_connect);
	T(UpdateTestCases::tcp_client_send);
	T(UpdateTestCases::tcp_client_recv);
	//T(UpdateTestCases::tcp_client_recv_timeout);
	T(UpdateTestCases::tcp_client_unkown_host);
	T(UpdateTestCases::tcp_client_read);
	T(UpdateTestCases::url_basic);
	//T(UpdateTestCases::tcp_url_download);
	T(UpdateTestCases::http_header);
	T(UpdateTestCases::http_resource_size);
	T(UpdateTestCases::web_time);
	T(UpdateTestCases::url_eval);
#endif
	
}
#include "UpgradeManager.h"
int UpdateTestCases::test_update_manager(int argc, char *argv[])
{
	int ret = 1;
	UpgradeManager manager;
	manager.config(
		"http://suddy.channel.com/download/",
		"c:\\settopbox");
	bool result = manager.runUpgrade();
	return result - true;
}

int UpdateTestCases::test_set_home(int argc, char *argv[])
{
	int ret = 1;
	return ret;
}

int UpdateTestCases::test_upgrade(int argc, char *argv[])
{
	int ret = 1;
	return ret;
}

int UpdateTestCases::test_update_item(int argc, char *argv[])
{
	int ret = 1;
	return ret;
}