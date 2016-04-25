// HttpDownloader.h: interface for the HttpDownloader class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_HTTPDOWNLOADER_H__8D2BF71F_C4EA_46E4_A98E_E2A1E56F8705__INCLUDED_)
#define AFX_HTTPDOWNLOADER_H__8D2BF71F_C4EA_46E4_A98E_E2A1E56F8705__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class HttpDownloader  
{
public:
	static int splitNetfile(const char *urlString);
	static bool setFileTime(const char *urlString,const  char* fileName);
	static bool isUpdated(const char *urlString,const  char* fileName);
	static int	getResourceSize(const char *urlString);
	static int downloadFile(const char *url, const char *fileName);
	HttpDownloader();
	virtual ~HttpDownloader();

};

#endif // !defined(AFX_HTTPDOWNLOADER_H__8D2BF71F_C4EA_46E4_A98E_E2A1E56F8705__INCLUDED_)




