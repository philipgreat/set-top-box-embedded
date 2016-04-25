// ClassTestingContainer.cpp : Defines the entry point for the application.
//




#define MAX_LOADSTRING 100

// Global Variables:


#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "PortHeader.h"

#include "WebDateTime.h"
#include "NetworkUtil.h"
#include "URLParameters.h"
#include "STBConfiguration.h"
#include "HttpUtil.h"
//const char *teststring="code=0;message=succeed pass;471=233627464;";
#include <string.h>
#include <memory.h>
#define WRAP_FUNCTION(x)  {#x,(x)}


typedef struct
{
	char *name;
	int (*test_function) (int argc, char* argv[]);

}test_case_t;

int test_set_env(int argc, char* argv[])
{

	putenv("TEST_ENV=listing");
	return strcmp(getenv("TEST_ENV"),"listing")==0?0:1;

}
int test_url_parse(int argc, char* argv[])
{
	int ret = 0;
	char *p = NULL;
	CURLParameters *params = new CURLParameters();	
	params -> Parse("a=101&b=10a");	
	
	//params->Report();
	params -> Parse("a=101&b=10a");	
	//params->Report();
	p = params->GetValue("b");

	ret=strcmp(p,"10a");
	delete params;
	return ret;

}

int test_web_time(int argc, char* argv[])
{
	int ret = 0;
	CWebDateTime *webTime = new CWebDateTime();
	CWebDateTime *webTime2 = new CWebDateTime(2005,9,5,3,1,56);
	webTime->Parse("Mon, 05 Sep 2005 03:01:56 GMT",29);
	//webTime->ShowInConsole();
	ret = webTime->equals(webTime2)?0:1;
	delete webTime;
	delete webTime2;
	return ret;
}
int test_single_file(int argc, char* argv[]){
	//FILE *f=fopen("D:\\settopbox\\stbapplication.ini","r");
	FILE *f=fopen("C:\\config.ini","r");
	if(f==NULL) return 0;
	DWORD len=1024;
	DWORD readlen=1024;
	char *buffer=new char [len];
	int acturalread = fread(buffer,1,1024,f);
	*(buffer+acturalread)='\0';
	printf(buffer);
	fclose(f);

	if(!acturalread) return 1;
	return 0;

}
int test_stb_config(int argc, char* argv[])
{
	int ret = 0;
	char *p = NULL;
	CSTBConfiguration *config = new CSTBConfiguration();
	time_t timer;

	timer=time(NULL);

	config->SetValue("time",asctime(localtime(&timer)));

	config->SetValue("love","you");
	config->SetValue("name","value");
	config->Report();

	config->Save();
	
	config->Load();
	config->Report();

	p = config->GetValue("love");
	config->Save();
	ret=strcmp(p,"you");
	delete config;
	return ret;

}

int test_http_util(int argc, char* argv[])
{
	int ret = 0;
	BYTE p[100];
	int len=100;
	for(int i=0;i<1000;i++)
	{
		CHttpUtil *util = new CHttpUtil();
		ret = util->ProcessGet(
			"http://suddy.channel.com/dl/lic.jsp?username=ligang&password=ligang&controlwordid=1&contenttype=2&contentid=1200&authorizetype=1",p,&len);
		delete util;
	
	}
	return ret;
}

test_case_t test_cases[]={
	WRAP_FUNCTION(test_set_env),
	WRAP_FUNCTION(test_url_parse),	
	WRAP_FUNCTION(test_web_time),
	WRAP_FUNCTION(test_single_file),
	WRAP_FUNCTION(test_stb_config),
	//WRAP_FUNCTION(test_http_util),	
	{NULL,NULL},
};

int main(int argc, char* argv[])
{

	CHttpUtil::InitNetwork();
	int (*pcall) (int argc, char* argv[]);
	char failed[1024*4]={0};
	int ret = 0;
	clock_t startTime;
	clock_t endTime;
	
	test_case_t *p_testcase=test_cases;
	printf("Testcases build @%s %s\n",__TIME__,__DATE__);
	printf("----------------------------------------------------------\n");
	while(p_testcase->name!=NULL)
	{	
		
		pcall=p_testcase->test_function;
		printf("%-30s",p_testcase->name);
		startTime = clock();
		ret = pcall(argc,argv);
		endTime = clock();

		if(ret==0){
			printf("%.6d(%08X)[OK  ] ",ret,ret);
		}else{
			if(strlen(failed)<500){
				printf("%.6d(%08X)[FAIL]",ret,ret);
				strcat(failed," ");
				strcat(failed,p_testcase->name);			
			}else{
				strcat(failed," .... tooooooooooooo much");
				break;		
			}
		}
		
		printf("%-6.4f\n",1000*(endTime-startTime)/((CLOCKS_PER_SEC)*1.0));
		p_testcase++;

	}
	printf("----------------------------------------------------------\n");
	printf("failed case:%s\n",failed);

	
	return 0;
}
