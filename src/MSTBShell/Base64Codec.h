// Base64Codec.h: interface for the Base64Codec class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BASE64CODEC_H__431F8EE6_8645_4209_9BEF_86D92EE89E60__INCLUDED_)
#define AFX_BASE64CODEC_H__431F8EE6_8645_4209_9BEF_86D92EE89E60__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class Base64Codec  
{
private:
	char *buffer;
public:
	char* encodeString(char *buffer,int length);
	char* encode(const unsigned char *buf, int length);
	Base64Codec();
	virtual ~Base64Codec();

};

#endif // !defined(AFX_BASE64CODEC_H__431F8EE6_8645_4209_9BEF_86D92EE89E60__INCLUDED_)
