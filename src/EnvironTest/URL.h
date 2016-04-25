// URL.h: interface for the URL class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_URL_H__D8C861B9_8F48_4F9F_8AED_ED4E15775E9A__INCLUDED_)
#define AFX_URL_H__D8C861B9_8F48_4F9F_8AED_ED4E15775E9A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class URL  
{
private:
	unsigned short getDefaultPort();
	unsigned short port;
	char *protocol;
	char *host;
	char *location;
	char *paramString;
	char buffer[2048];
	int  usedLength;
public:
	bool isDefaultPort();
	char * eval(const char*relativePath);
	char * getLocation() const;
	char * getParameterString() const;
	char * getHostName() const;
	unsigned short getPort() const;
	int parse(char *urlstring);
	URL();
	URL(char *message);
	virtual ~URL();

};

#endif // !defined(AFX_URL_H__D8C861B9_8F48_4F9F_8AED_ED4E15775E9A__INCLUDED_)
