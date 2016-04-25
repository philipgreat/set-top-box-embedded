// Parameter.cpp: implementation of the CParameter class.
//
//////////////////////////////////////////////////////////////////////

#include "Parameter.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CParameter::CParameter()
{

}
CParameter::CParameter(const char *pname, const char *pvalue)
{
	int nameLength=strlen(pname)+1;
	int valueLength=strlen(pvalue)+1;

	this->name=new char[nameLength];
	memset(this->name,0,nameLength);

	this->value=new char[valueLength];
	memset(this->value,0,valueLength);

	memcpy(this->name,pname,nameLength);
	memcpy(this->value,pvalue,valueLength);


}


CParameter::~CParameter()
{
	if(this->name) delete this->name;
	if(this->value) delete this->value;
	this->name=NULL;
	this->value=NULL;

}

char * CParameter::GetName()
{
	return this->name;
}

void CParameter::Report()
{
	printf("report\n");
	printf("\t%s = %s \n",name,value);
}
