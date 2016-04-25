// DocumentHandle.cpp: implementation of the DocumentHandle class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "DocumentHandle.h"
#include <stdio.h>
#include <windows.h>
#include <ole2.h>
#include <locale.h>
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
#include "URL.h"
#include "TCPClient.h"

static void DumpPropVariant(PROPVARIANT *pPropVar,char *message, int length) {
	// Don't iterate arrays, just inform as an array.
	// Switch types.
	switch(pPropVar->vt) {
	case VT_EMPTY:
		sprintf(message,"N/A");
		break;
	case VT_NULL:
		sprintf(message,"NULL");
		break;
	case VT_BLOB:
		sprintf(message,"<BIN>\n");
		break;
	case VT_BOOL:
		sprintf(message,"%s",pPropVar->boolVal ? "TRUE" : "FALSE");
		break;
	case VT_I2: // 2-byte signed int.
		sprintf(message,"%d", (int)pPropVar->iVal);
		break;
	case VT_I4: // 4-byte signed int.
		sprintf(message,"%d", (int)pPropVar->lVal);
		break;
	case VT_R4: // 4-byte real.
		sprintf(message,"%.2lf", (double)pPropVar->fltVal);
		break;
	case VT_R8: // 8-byte real.
		sprintf(message,"%.2lf", (double)pPropVar->dblVal);
		break;
	case VT_BSTR: // OLE Automation string.
		{
            // Translate into ASCII.
            char dbcs[1024];
            char *pbstr = (char *)pPropVar->bstrVal;
            int i = wcstombs(dbcs, pPropVar->bstrVal, *((DWORD *)(pbstr-4)));
            dbcs[i] = 0;
            sprintf(message,"%s", dbcs);
		}
		break;
	case VT_LPSTR: // Null-terminated string.
		{
			sprintf(message,"%s", pPropVar->pszVal);
		}
		break;
	case VT_FILETIME:
		{
            char *dayPre[] =
			{"Sun","Mon","Tue","Wed","Thu","Fri","Sat"};
			
            FILETIME lft;
            FileTimeToLocalFileTime(&pPropVar->filetime, &lft);                
			SYSTEMTIME lst;
            FileTimeToSystemTime(&lft, &lst);			
            sprintf(message,"%02d:%02d.%02d %s, %s %02d/%02d/%d",
				1+(lst.wHour-1)%12, lst.wMinute, lst.wSecond,
				(lst.wHour>=12) ? "pm" : "am",
				dayPre[lst.wDayOfWeek%7],
				lst.wMonth, lst.wDay, lst.wYear);
		}
		break;
	case VT_CF: // Clipboard format.
		sprintf(message,"(Clipboard format)");		
		break;
	default: // Unhandled type, consult wtypes.h's VARENUM structure.
		sprintf(message,"(Unhandled type: 0x%08lx)\n", pPropVar->vt);
		break;
	}
}





static void DumpBuiltInProps(IPropertySetStorage *pPropSetStg, DocumentHandle *handle)
{

	char message[1024];
	IPropertyStorage *pPropStg = NULL;
	HRESULT hr;
	
	// Open summary information, getting an IpropertyStorage.
	hr = pPropSetStg->Open(FMTID_SummaryInformation,
		STGM_READ | STGM_SHARE_EXCLUSIVE, &pPropStg);
	//hr = pPropSetStg->Open(FMTID_UserDefinedProperties,
	//STGM_READ | STGM_SHARE_EXCLUSIVE, &pPropStg);
	if(FAILED(hr)) {
		printf("No Summary-Information.\n");
		return;
	}
	// Array of PIDSI's you are interested in.
	struct pidsiStruct {
		char *name;
		long pidsi;
	} pidsiArr[] = {
		{"title",            PIDSI_TITLE}, // VT_LPSTR
		{"subject",          PIDSI_SUBJECT}, // ...
		{"author",           PIDSI_AUTHOR},
		{"keywords",         PIDSI_KEYWORDS},
		{"comments",         PIDSI_COMMENTS},
		{"template",         PIDSI_TEMPLATE},
		{"lastAuthor",       PIDSI_LASTAUTHOR},
		{"revision Number",  PIDSI_REVNUMBER},
		{"edit Time",        PIDSI_EDITTIME}, // VT_FILENAME (UTC)
		{"last printed",     PIDSI_LASTPRINTED}, // ...
		{"created",          PIDSI_CREATE_DTM},
		{"last Saved",       PIDSI_LASTSAVE_DTM},
		{"page Count",       PIDSI_PAGECOUNT}, // VT_I4
		{"word Count",       PIDSI_WORDCOUNT}, // ...
		{"char Count",       PIDSI_CHARCOUNT},		
		{"thumpnail",        PIDSI_THUMBNAIL}, // VT_CF
		{"appName",          PIDSI_APPNAME}, // VT_LPSTR
		{"doc Security",     PIDSI_DOC_SECURITY}, // VT_I4
		{0, 0}
	};
	// Count elements in pidsiArr.
	int nPidsi = 0;
	for(nPidsi=0; pidsiArr[nPidsi].name; nPidsi++);
	
	// Initialize PROPSPEC for the properties you want.
	PROPSPEC *pPropSpec = new PROPSPEC [nPidsi];
	PROPVARIANT *pPropVar = new PROPVARIANT [nPidsi];
	
	for(int i=0; i<nPidsi; i++) {
		ZeroMemory(&pPropSpec[i], sizeof(PROPSPEC));
		pPropSpec[i].ulKind = PRSPEC_PROPID;
		pPropSpec[i].propid = pidsiArr[i].pidsi;
	}
	
	
	
	// Read properties.
	hr = pPropStg->ReadMultiple(nPidsi, pPropSpec, pPropVar);
	
	if(FAILED(hr)) {
		
	}
	else {
		// Dump properties.
		for(i=0; i<nPidsi; i++) {
            DumpPropVariant(pPropVar + i,message,1024);
			handle->onProperty(pidsiArr[i].name,message);
		}
	}
	
	// De-allocate memory.
	delete [] pPropVar;
	delete [] pPropSpec;
	
	// Release obtained interface.
	pPropStg->Release();
	
}

// Dump's custom properties of a property storage.

// Dump's custom and built-in properties of a compound document.
static void DumpProps(const char *filename,DocumentHandle *handle) 
{

	
	if(handle==NULL) return;
	// Translate filename to Unicode.
	WCHAR wcFilename[1024];
	setlocale( LC_ALL, "" );
	int i = mbstowcs(wcFilename, filename, strlen(filename));
	setlocale( LC_ALL, "C" );
	wcFilename[i] = 0;
	
	IStorage *pStorage = NULL;
	IPropertySetStorage *pPropSetStg = NULL;
	HRESULT hr;
	hr = ::StgOpenStorage(wcFilename, NULL,
		STGM_READ | STGM_SHARE_EXCLUSIVE, NULL, 0, &pStorage);
	
	if(FAILED(hr)) {
		return;
	}
	hr = pStorage->QueryInterface(
		IID_IPropertySetStorage, (void **)&pPropSetStg);
	if(FAILED(hr)) {		
		pStorage->Release();
		return;
	}
	DumpBuiltInProps(pPropSetStg,handle);
	pPropSetStg->Release();
	pStorage->Release();
}
DocumentHandle::DocumentHandle()
{
	this->documentName=new char[MAX_PATH];
	bytebuffer.reset();
}

DocumentHandle::~DocumentHandle()
{
	delete this->documentName;
}
/*
sendto=suddychang@gmail.com
title=中文标题
location=http://localhost
from=zhangxl@channelsoft.com
encoding=GBK

*/
int DocumentHandle::startDocument(const char *filePath)
{
	char buffer[1024];
	bytebuffer.reset();
	strncpy(this->documentName,filePath,MAX_PATH);
	sprintf(buffer,"sendto=%s\r\n","suddychang@gmail.com");
	bytebuffer.put(buffer,strlen(buffer));

	sprintf(buffer,"location=http://localhost/\r\n",filePath);
	bytebuffer.put(buffer,strlen(buffer));

	sprintf(buffer,"encoding=GBK\r\n");
	bytebuffer.put(buffer,strlen(buffer));

	sprintf(buffer,"from=%s\r\n","zhangxl@channelsoft.com");
	bytebuffer.put(buffer,strlen(buffer));

	DumpProps(filePath,this);
	bytebuffer.put("\r\n",2);	

	return 0;
}
#define POST_REQ_FORMAT 	\
"POST /%s HTTP/1.0\r\n\
User-Agent: TestWeBrowser\r\n\
Encoding: GBK\r\n\
Content-Length: %u\r\n\r\n"





int DocumentHandle::endDocument()
{

	int ret = 1;
	char buffer[1024];
	int  spliterPostion = 0;
	int contentLength = 0;
	char *sendContent = bytebuffer.getString();

	bytebuffer.put("</pre>",6);
	sprintf(buffer,"<doc src='%s'>",this->documentName);
	bytebuffer.put(buffer,strlen(buffer));

	URL url("http://suddy.channel.com/workflow/SmartMail.jsp");

	TCPClient *client=new TCPClient();
	ret = client->connect(url.getHostName(),url.getPort());
	contentLength = strlen(sendContent);
	sprintf(buffer,POST_REQ_FORMAT,url.getLocation(),contentLength);	
	ret = client->send(buffer,strlen(buffer));
	ret = client->send(sendContent,contentLength);
	
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
#define LINE_START "<TABLE BORDER=0 WIDTH='800' CELLSPACING=0 CELLPADDING=0><TR>\
<TD BGCOLOR=#000000><TABLE BORDER=0 WIDTH='100%%' CELLSPACING=1 CELLPADDING=2><TR>\
<TD  width=100%% BGCOLOR=#eeeeee  align=left >"
#define LINE_END "</TD></TR></TD></TABLE></TABLE><p>"

int DocumentHandle::onPage(int index, const char *text)
{
	char buffer[1024];
	if(strlen(text)>2){
	sprintf(buffer,LINE_START);
	bytebuffer.put(buffer,strlen(buffer));
	bytebuffer.put(text,strlen(text));
	sprintf(buffer,LINE_END);
	bytebuffer.put(LINE_END,strlen(LINE_END));
	bytebuffer.put("\r\n",2);
	
	}
	return 0;
}

int DocumentHandle::onProperty(char *name, char *value)
{
	char buffer[1024];

	if(strncmp("title",name,strlen("title")+1)==0){
		if(value==NULL||strlen(value)==0){
			sprintf(buffer,"%s=@%s\r\n",name,this->documentName);
			bytebuffer.put(buffer,strlen(buffer));			
			return 1;
		}else{
			sprintf(buffer,"%s=%s\r\n",name,value);
			bytebuffer.put(buffer,strlen(buffer));	
			return 0;		
		}
		
	}
	


	return 1;
}
