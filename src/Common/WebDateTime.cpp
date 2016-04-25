// WebDateTime.cpp: implementation of the CWebDateTime class.
//
//////////////////////////////////////////////////////////////////////

#include "WebDateTime.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <memory.h>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

#include "PortHeader.h"
static const char *g_months[]={
	"Jan",
	"Feb",
	"Mar",
	"Apr",
	"May",
	"Jun",
	"Jul",
	"Aug",
	"Sep",
	"Oct",
	"Nov",
	"Dec",
	NULL};
static const char *g_dayofweeks[]={
	"Sun",
	"Mon",
	"Tue",
	"Wed",
	"Thu",
	"Fri",
	"Sat",
	NULL
};

//zero based index
static int GetIndex(const char *in,const char **data)
{
	char **p=(char **)data;
	int ret=0;
	BOOL isFound=FALSE;
	while(*p)
	{
		if(memcmp(in,*p,strlen(in)+1)==0){
			
			isFound=TRUE;
			break;
		}
		ret++;
		//printf(*p);
		p++;
	
	}
	if(!isFound){
		ret=-1;
	}
	return ret;


}
CWebDateTime::CWebDateTime():
	 year(0),
	 month(1),
	 day(1),
	 dayOfWeek(0),
	 hour(0),
	 minute(0),
	 second(0),
	 msecond(0)
{

}

CWebDateTime::CWebDateTime(	short year,	short month,short day)
:year(year),month(month),day(day),dayOfWeek(0),	hour(0), minute(0), second(0), msecond(0)
{
	
}

CWebDateTime::CWebDateTime(	short year,	short month, short day,short hour, short minute, short second)
:year(year),month(month),day(day),hour(hour), minute(minute), second(second), msecond(0)
{


}
CWebDateTime::CWebDateTime(
		short year,
		short month,
		short day,
		short dayOfWeek,
		short hour,
		short minute,
		short second,
		short msecond)
:year(year),month(month),day(day),hour(hour), minute(minute), second(minute), msecond(msecond)
{


	
}
CWebDateTime::~CWebDateTime()
{
	
}
//Mon, 05 Sep 2005 03:01:56 GMT

BOOL CWebDateTime::Parse(const char *data, int length)
{
	//return GetIndex("Mon",months);
	if(length<20)  return FALSE;
	char *p=NULL;
	char *head=NULL;
	int len=strlen(data)+1;
	p=head=new char[len];
	memcpy(p,data,len);

	while(p-head<len){
		if(*p==' '||*p==':'||*p==','){
			*p=0;
		}
		p++;
	}

	p=head;
	//Mon, 05 Sep 2005 03:01:56 GMT
	//012345678901234567890123456789
	char *pDayOfWeek	= p + 0;
	char *pDay			= p + 5;
	char *pMonth		= p + 8;
	char *pYear			= p + 12;
	char *pHour			= p + 17;
	char *pMinute		= p + 20;
	char *pSecond		= p + 23;

	this->year	=	atoi(pYear);
	this->month = GetIndex(pMonth,g_months)+1;
	this->day	= atoi(pDay);
	this->hour	= atoi(pHour);
	this->minute = atoi(pMinute);
	this->second = atoi(pSecond);
	this->dayOfWeek = GetIndex(pDayOfWeek,g_dayofweeks)+1;
	delete head;

	if(month==0) return FALSE;
	return TRUE;
}
static BOOL IsLeapYear(short year)
{
	return(year%4==0 && year%100!=0) || (year%400==0);
}

static BOOL IsTheLastDayOfMonth(short year, short month, short day){
	
	//
	int days=30;
	if(month<8&&month%2==1){
		days=31;
	}
	if(month>=8&&month%2==0){
		days=31;
	}
	if(month==2&&IsLeapYear(year)){
		days=29;
	}
	if(month==2&&!IsLeapYear(year)){
		days=28;
	}
	return day==days;


}
//多于24小时会出问题
void CWebDateTime::AddHour(int hr)
{

	this->hour+=hr;
	if(this->hour>=24){
		this->hour=this->hour%24;
		this->day++;
	}
	
	if(IsTheLastDayOfMonth(this->year,this->month,this->day )){
	
		this->day=1;
		this->month++;
	}
	if(this->month>12){
		this->month=this->month%13+1;
		this->year++;
	}

}

void CWebDateTime::ShowInConsole()
{
#if	 1
	printf("\n%.4d-%.2d-%.2d %.2d:%.2d:%.2d\n",
		this->year,
		this->month,
		this->day,
		this->hour,
		this->minute,
		this->second);
#endif
}

void CWebDateTime::AddSeconds(int sec)
{

}

BOOL CWebDateTime::equals(CWebDateTime *other)
{
	return   this->year	== other->year
		&&this->month	== other->month
		&&this->day		== other->day
		&&this->hour	== other->hour
		&&this->minute  == other->minute
		&&this->second  == other->second
		&&this->msecond == other->msecond;
}
