// Parameters.cpp: implementation of the CParameters class.
//
//////////////////////////////////////////////////////////////////////

#include "Parameters.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CParameters::CParameters()
{
	
}

CParameters::~CParameters()
{
	//释放所有的参数
	//TODO
	this->Clear();
	//printf("delete paran\n");

}


BOOL CParameters::AddParameter(const char *name, const char *value)
{

	map<const char*, CParameter*, ltstr>::iterator loc;
	
	if(name!=NULL&&value!=NULL)
	{
		loc=parameters.find(name);

		char *key=new char[strlen(name)+1];
		//key will be free when the object destructed!		
		memcpy(key,name,strlen(name)+1);

		//this key will be free when the 
		//object destruct
		if(loc==parameters.end()){
			//not found
			parameters[key]=new CParameter(name,value);
			//printf("'%s'\n",name);

		}else{
			//found
			//char *keyOld=(char*)loc->first;
			//delete keyOld;

			CParameter *p=loc->second;
			delete p;
			//加入新的参数
			//parameters.erase(name);
			parameters[key]=new CParameter(name,value);
		}
		return TRUE;
	}else{
		return FALSE;
	}

	return FALSE;

}

enum PARSE_STATE{INIT=0,IN_NAME,BEFORE_VALUE,IN_VALUE,END_VALUE,END};
//该函数需要参考状态图

int  CParameters::ParseExpression(const char *str2parse,
								  char nameValueSeperator,
								  char itemSeperator)
{

	int state=INIT;
	char *header=NULL;
	int  parseStrLen=strlen(str2parse)+1;
	char *p=header=new char[parseStrLen];
	char *name=NULL;
	char *value=NULL;

	memcpy(p,str2parse,parseStrLen);
	this->parameters.clear();
	while(p-header<parseStrLen){
		switch(state){
		
		case INIT:
			if(isalnum(*p)){
				name=p;
				state=IN_NAME;
			}
			break;
		case IN_NAME:
			if(*p==nameValueSeperator){
				state=BEFORE_VALUE;
				*p='\0';
			}else if (!(isalnum(*p)||*p=='_'||*p=='.'||*p=='-')){

				*p='\0';
			}
			break;
		case BEFORE_VALUE:
			if(*p=='\r'||*p=='\n'||*p==itemSeperator){
				value="";
				state=END_VALUE;
				p--;
			}else if(*p==' '||*p=='\t' ){
				//忽略前面的空格等无效字符
			}else {
				value=p;
				state=IN_VALUE;
			}	
			break;
		case IN_VALUE:
			if(*p=='\r'||*p=='\n'||*p==itemSeperator||*p=='\0'){
				*p='\0';
				p--;
				state=END_VALUE;
			}
			break;
		case END_VALUE:
			this->AddParameter(name,value);
			state=INIT;	
			break;
		default:
			break;

		}
		p++;
	
	}
	//printf("%d\r\n",p-header);

	delete[] header;

	return 0;
}

int CParameters::Parse(const char *data)
{
	//
	this->ParseExpression(data);
	return 1;
	
}

char * CParameters::GetValue(const char *name)
{
	CParameter *param=NULL;

	map<const char*, CParameter*, ltstr>::iterator loc;
	loc = this->parameters.find(name);
	if(this->parameters.end() != loc){
		param=loc->second;
		return param->GetValue();
	}else{
		return NULL;
	}

}

void CParameters::Report()
{
	map<const char*, CParameter*, ltstr>::iterator loc;
	int len=parameters.size();
	printf("Size of the map: %u\n",len);
	
	for(loc=parameters.begin();loc!=parameters.end();loc++)
	{
		CParameter *p=loc->second;
		char *name=p->GetName();
		char *value=p->GetValue();

		printf("\t%20s = %s\n",p->GetName(),p->GetValue());
	}
	//::WritePrivateProfileString(
}
/*
int CParameters::Save(const char *fileName)
{
	
	HANDLE saveFile;
	saveFile = CreateFile(fileName, 
		GENERIC_WRITE, FILE_SHARE_READ, NULL, 
		OPEN_ALWAYS, 
		FILE_ATTRIBUTE_NORMAL, NULL);

	map<const char*, CParameter*, ltstr>::iterator loc;
	int len=parameters.size();
	::SetEndOfFile(saveFile);

	//printf("Size of the map: %u\n",len);
	char line[1024];
	//SetFilePointer(saveFile,0,0,0);
	for(loc=parameters.begin();loc!=parameters.end();loc++)
	{
		CParameter *p=loc->second;
		//saveFile
		unsigned long readLen=0;
		sprintf(line,"%s = %s\r\n",p->GetName(),p->GetValue());
		DWORD len=strlen(line);
		WriteFile(saveFile,line,len,&readLen,NULL);
		
	}
	CloseHandle(saveFile);

	return 0;

}

*/
int CParameters::Save(const char *fileName)
{
	FILE *f=fopen(fileName,"w+b");

	if(f==NULL) return 1;
	map<const char*, CParameter*, ltstr>::iterator loc;
	char line[1024];
	for(loc=parameters.begin();loc!=parameters.end();loc++)
	{
		CParameter *p=loc->second;
		sprintf(line,"%s = %s\r\n",p->GetName(),p->GetValue());
		fwrite(line,strlen(line),1,f);		
	}
	sprintf(line,"\r\n");
	fwrite(line,strlen(line),1,f);
	fclose(f);

	return 0;

}

void CParameters::Load(char *fileName)
{

	FILE *f=fopen(fileName,"r+b");
	if(f==NULL) return;
	fseek(f,0,0);
	DWORD len=1024*10;
	DWORD readlen=1024*10;
	char *buffer=new char [len];
	int acturalread = fread(buffer,1,readlen,f);
	*(buffer+acturalread)='\0';
	fclose(f);
	this->Parse(buffer);
	delete buffer;
}

void CParameters::Clear()
{
	map<const char*, CParameter*, ltstr>::iterator loc;
	for(loc=parameters.begin();loc!=parameters.end();loc++)
	{
		CParameter *p=loc->second;	
		char *key=(char*)loc->first;
		delete key;
		delete p;
		p=NULL;
	}
	parameters.clear();
}
