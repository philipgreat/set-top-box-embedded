// UpgradeManager.cpp: implementation of the UpgradeManager class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "UpgradeManager.h"
#include <string.h>
#include "HttpDownloader.h"
#include "TCPClient.h"
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
#include <stdio.h>
UpgradeManager::UpgradeManager()
{
	
}

UpgradeManager::~UpgradeManager()
{
	
}

void UpgradeManager::config(const char *url,const char*localHome)
{
	strncpy(this->upgradeURL,url,1024-1);
	strncpy(this->localHome,localHome,1024-1);
}

char *getValue(char *expr)
{
	char *p = expr;
	while(*p){
		if(*p=='='){
			*p=0;
			break;
		}		
		p++;
	}
	return p+1;
	
}

bool UpgradeManager::runUpgrade()
{
	bool	ret = true;
	FILE	*file;
	char	buffer[1024];
	int		spliterCounter = 0;
	char	ch;
	int		counter = 0;
	char	*name;
	char	*value;
	try{
		if(this->forceDownloadFile("updatelist.ini")<=0){
			throw Exception("failed to get file updatelist.ini");
		}
		sprintf(buffer,"%s\\%s",this->localHome,"updatelist.ini");
		file = fopen(buffer,"rb");
		if(file==NULL){
			throw Exception("failed to open file 'updatelist.ini'");
		}
		while(fread(&ch,1,1,file)>0){
			if(ch=='\r'||ch=='\n'){
				spliterCounter++;
			}else if(ch!=' '&&ch!='\t'){	
				buffer[counter] = ch;
				counter++;
				spliterCounter=0;
			}
			if(spliterCounter == 2){
				
				buffer[counter] = 0;
				//printf("%s\n",buffer);
				name = buffer;
				value = getValue(buffer);
				//printf("name=%s, value=%s\n", name, value);
				this->downloadFile(name,value);
				counter = 0;
			}
		}
		if(counter>0){
			//the file does not end with '\r\n'
			name = buffer;
			value = getValue(buffer);
			this->downloadFile(name,value);
			//printf("%s\n",buffer);
		}
		
	}catch(Exception &e){
		e.report();
		ret = false;
	}
	return ret;
	
}

int UpgradeManager::downloadNewestFile(const char *fileName)
{
	int size=0;
	int downloadsize=0;		
	char url[1024];
	char localFileName[1024];
	sprintf(url,"%s/%s",this->upgradeURL,fileName);
	sprintf(localFileName,"%s\\%s",this->localHome,fileName);

	if((size=HttpDownloader::getResourceSize(url))>0){
		if(HttpDownloader::isUpdated(url,localFileName)){
			downloadsize = HttpDownloader::downloadFile(url,localFileName);			
		}
	}else{
		throw Exception("the file seems disappeared from server side!");
	}
	return 1;
	
}

int UpgradeManager::forceDownloadFile(const char *fileName)
{
	int downloadsize=0;		
	char url[1024];
	char localFileName[1024];
	sprintf(url,"%s/%s",this->upgradeURL,fileName);
	sprintf(localFileName,"%s\\%s",this->localHome,fileName);

	return downloadsize = HttpDownloader::downloadFile(url,localFileName);
}

void UpgradeManager::downloadFile(char *fileName, char *rule)
{
	if(EQUALS("force",rule)){
		if(this->forceDownloadFile(fileName)<=0){
			throw Exception("down load file failed!");
		}
	}else{
		if(this->downloadNewestFile(fileName)<=0){
			throw Exception("down load file failed!");
		}					
	}	

}
