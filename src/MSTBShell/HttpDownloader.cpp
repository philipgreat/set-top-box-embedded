// HttpDownloader.cpp: implementation of the HttpDownloader class.
//
//////////////////////////////////////////////////////////////////////


#include "HttpDownloader.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <memory.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/utime.h>
#include <time.h>

#include "TCPClient.h"
#include "URL.h"
#include "WebDateTime.h"
#define TEST_REQ_FORMAT 	"GET /%s HTTP/1.0\r\nUser-Agent: TestWeBrowser\r\n\r\n"
#define HEAD_REQ_FORMAT 	"HEAD /%s HTTP/1.0\r\nUser-Agent: TestWeBrowser\r\n\r\n"
#define TEST_REQ_PARAM  	"GET /%s?%s HTTP/1.0\r\nUser-Agent: TestWeBrowser\r\n\r\n"



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

static char * getLastModified(char *buffer)
{
	//
	//HTTP/1.1 200 OK
	char *p=strchr(buffer,':');
	char *dateTimeString = (p+2);
	return dateTimeString;
	
}


static int setFileModifyTime(const char *filename, time_t time)
{
	int ret = 0;
	struct _utimbuf ubuf;
	ubuf.modtime =  time;	
	ret = ::_utime(filename,&ubuf);
	return ret;
}

static time_t getFileModifyTime(const char *filename)
{
	struct stat filestat;
	if(0==stat(filename,&filestat)>0){
		return  filestat.st_mtime;
	}else{
		return 0;
	}
}





HttpDownloader::HttpDownloader()
{

}

HttpDownloader::~HttpDownloader()
{

}

int HttpDownloader::downloadFile(const char *urlstring, const char *fileName)
{
	int		ret = 1;
	char	buffer[1024];
	FILE	*file;
	int		spliterCounter = 0;
	URL		url(urlstring);
	int		counter = 0;
	int		size = 0;
	char	*tempTimeString = NULL;
	CWebDateTime remoteResourceTime;
	time_t	remoteFileTime;
	char ch = '0';


	file=fopen(fileName,"wb");
	if(file == NULL)
	{		
		return 0;
	}

	TCPClient *client=new TCPClient();
	ret = client->connect(url.getHostName(),url.getPort());
	sprintf(buffer,TEST_REQ_FORMAT,url.getLocation());
	ret = client->send(buffer,strlen(buffer));

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
			if(strncmp("HTTP/",buffer,5)==0){
				if(isStateOK(buffer)){
					size = 1;
				}
			}
			if(strncmp("Last-Modified: ",buffer,strlen("Last-Modified: "))==0){
				tempTimeString = getLastModified(buffer);
				remoteResourceTime.parse(tempTimeString,strlen(tempTimeString));
			}

			counter = 0;
		}
		if(spliterCounter>=4){
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
			count += ret;
		}catch(Exception &e){
			e.report();
		}
	}

	fclose(file);
	client->close();
	delete client;

	if(size==0) return 0;

	remoteResourceTime.toStandardTime(&remoteFileTime);
	setFileModifyTime(fileName,remoteFileTime);
	
	return count;
}


int HttpDownloader::getResourceSize(const char *urlString)
{
	int		ret = 0;
	int		size = 0;
	char	buffer[1024];
	int		spliterCounter = 0;
	URL		url(urlString);
	int		counter = 0;
	TCPClient *client=new TCPClient();
	char ch = '0';

	ret = client->connect(url.getHostName(),url.getPort());
	sprintf(buffer,HEAD_REQ_FORMAT,url.getLocation());
	ret = client->send(buffer,strlen(buffer))==21?0:1;


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
			if(strncmp("HTTP/",buffer,5)==0){
				if(isStateOK(buffer)){
					size = 1;
				}
			}
			if(strncmp("Content-Length: ",buffer,strlen("Content-Length: "))==0){
				if(size>0) size = getContentLength(buffer);
			}

			counter = 0;
		}
		if(spliterCounter>=4){
			break;
		}
	}
	client->close();
	delete client;
	return size;
}

bool HttpDownloader::isUpdated(const char *urlString, const char *fileName)
{

	int		ret = 0;
	int		size = 0;
	char	buffer[1024];
	int		spliterCounter = 0;
	URL		url(urlString);
	int		counter = 0;
	char	*tempTimeString = NULL;
	time_t	remoteFileTime;
	time_t	localFileTime;
	CWebDateTime remoteResourceTime;


	TCPClient *client=new TCPClient();
	ret = client->connect(url.getHostName(),url.getPort());
	sprintf(buffer,HEAD_REQ_FORMAT,url.getLocation());
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
			if(strncmp("HTTP/",buffer,5)==0){
				if(isStateOK(buffer)){
					size = 1;
				}
			}

			if(strncmp("Last-Modified: ",buffer,strlen("Last-Modified: "))==0){
				tempTimeString = getLastModified(buffer);
				remoteResourceTime.parse(tempTimeString,strlen(tempTimeString));
			}
			counter = 0;
		}
		if(spliterCounter>=4){
			break;
		}
	}
	client->close();
	delete client;
	if(size=0) return false;
	localFileTime = getFileModifyTime(fileName);
	remoteResourceTime.toStandardTime(&remoteFileTime);
	return remoteFileTime > localFileTime;
}

bool HttpDownloader::setFileTime(const char *urlString, const char *fileName)
{

	int		ret = 0;
	int		size = 0;
	char	buffer[1024];
	int		spliterCounter = 0;
	URL		url(urlString);
	int		counter = 0;
	char	*tempTimeString = NULL;
	CWebDateTime remoteResourceTime;
	time_t	remoteFileTime;


	TCPClient *client=new TCPClient();
	ret = client->connect(url.getHostName(),url.getPort());
	sprintf(buffer,HEAD_REQ_FORMAT,url.getLocation());
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
			if(strncmp("HTTP/",buffer,5)==0){
				if(isStateOK(buffer)){
					size = 1;
				}
			}

			if(strncmp("Last-Modified: ",buffer,strlen("Last-Modified: "))==0){
				tempTimeString = getLastModified(buffer);
				remoteResourceTime.parse(tempTimeString,strlen(tempTimeString));
			}
			counter = 0;
		}
		if(spliterCounter>=4){
			break;
		}
	}
	client->close();
	delete client;
	if(size==0) return false;
	remoteResourceTime.toStandardTime(&remoteFileTime);
	setFileModifyTime(fileName,remoteFileTime);
	return (ret>0);
}

#define FILE_SAVE_FLAG	"@savefile: "
#define FILE_APPD_FLAG	"@appendfile: "
int HttpDownloader::splitNetfile(const char *urlString)
{
	int		ret = 1;
	char	buffer[1024];
	FILE	*file=NULL;
	int		spliterCounter = 0;
	URL		url(urlString);
	int		counter = 0;
	int		size = 0;
	char	ch = '0';

	TCPClient *client=new TCPClient();
	ret = client->connect(url.getHostName(),url.getPort());
	char *p = url.getParameterString();
	if(p!=NULL){
		sprintf(buffer,TEST_REQ_PARAM,url.getLocation(),p);
	}else{
		sprintf(buffer,TEST_REQ_FORMAT,url.getLocation());
	}
	ret = client->send(buffer,strlen(buffer));

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
			if(strncmp("HTTP/",buffer,5)==0){
				if(isStateOK(buffer)){
					size = 1;
				}
			}
			counter = 0;
		}
		if(spliterCounter>=4){
			break;
		}
	}

	int count = 0;
	while(ret=client->recv(&ch,1))
	{
	
		//printf("%c",ch);

		if(ch=='\r'||ch=='\n'){
			spliterCounter++;
		}else{
			buffer[counter] = ch;
			counter++;
			spliterCounter=0;
		}
		if(spliterCounter == 2){
			
			buffer[counter] = 0;			
			if(0==strncmp(FILE_SAVE_FLAG,buffer,strlen(FILE_SAVE_FLAG))){				
				if(file!=NULL){
					fclose(file);
				}
				char *p=strchr(buffer,':');
				file = fopen(p+2,"wb");
			}else{
				if(file){
					fwrite(buffer,1,strlen(buffer),file);
					fwrite("\r\n",1,2,file);
				
				}//simpley write 
			}
			counter = 0;
		}

	}

	//fclose(file);
	client->close();
	delete client;

	if(size==0) return 0;
	
	return count;
}
