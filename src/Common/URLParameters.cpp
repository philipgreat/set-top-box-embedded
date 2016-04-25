// URLParameters.cpp: implementation of the CURLParameters class.
//
//////////////////////////////////////////////////////////////////////

#include "URLParameters.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
enum URL_ENCODE_STATE{COMMON,ENC_START,ENC_IN,ENC_END};

CURLParameters::CURLParameters()
{
}

CURLParameters::~CURLParameters()
{
}

int CURLParameters::Parse(const char *data)
{
	CParameters::ParseExpression(data,'=','&');
	return 0;
}

BOOL CURLParameters::AddParameter(const char *name, const char *value)
{
	//特殊字符需要重新处理后才可以使用
	//临时的变量可以保存在栈上
	BYTE val[1024];
	memset(val,0,1024);
	char *p=(char*)value;
	int index=0;
	int state=COMMON;
	while(*p){
		switch(state){
		
		case COMMON:
			if(*p=='+'){			
				val[index]=' ';
				index++;
			}else if(*p=='%'){
				state=ENC_START;
			}else{
				val[index]=*p;
				index++;		
			}
			break;
		case ENC_START:
			//first 
			if(isdigit(*p)){
				val[index]=(*p-'0');
			}else{
				val[index]=(*p-'A'+10);
			}
			state=ENC_IN;
			break;
		case ENC_IN:
			//first 
			//printf("%d",val[index]);
			BYTE high=0;
			if(isdigit(*p)){
				high=(*p-'0');
			}else{
				high=(*p-'A'+10);
			}
			BYTE low=val[index]<<4;
			val[index]=(BYTE)(high+low);
			//printf("%s %c %02X\n",name,val[index],val[index]);
			index++;
			state=COMMON;
			break;
		}

		p++;
	}
	val[index++]=0;

	return CParameters::AddParameter(name,(char *)val);
	//return CParameters::AddParameter(name,value);

}

