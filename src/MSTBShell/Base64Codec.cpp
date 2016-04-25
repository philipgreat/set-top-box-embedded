// Base64Codec.cpp: implementation of the Base64Codec class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Base64Codec.h"
const int size=1024;
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
static char base64_alphabet[]=
{'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P',
'Q','R','S','T','U','V','W','X','Y','Z','a','b','c','d','e','f',
'g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v',
'w','x','y','z','0','1','2','3','4','5','6','7','8','9','+','/','='}; 
static inline void encodeblock( unsigned char *in, char *out, int len )
{
	int a= in[0] >> 2;
    out[0] = base64_alphabet[ in[0] >> 2 ];
    out[1] = base64_alphabet[ ((in[0] & 0x03) << 4) | ((in[1] & 0xf0) >> 4) ];
    out[2] = (unsigned char) (len > 1 ? base64_alphabet[ ((in[1] & 0x0f) << 2) | ((in[2] & 0xc0) >> 6) ] : '=');
    out[3] = (unsigned char) (len > 2 ? base64_alphabet[ in[2] & 0x3f ] : '=');
}

Base64Codec::Base64Codec()
{
	buffer=new char[size];
}

Base64Codec::~Base64Codec()
{
	delete buffer;
}
#include <string.h>
char* Base64Codec::encode(const unsigned char *buf, int length)
{

	unsigned char *p=(unsigned char *)buf;
	int i=0;
	memset(buffer,0x00,size);
	while(p-buf<=length-3){	
		encodeblock(p,(buffer+(i<<2)),3);
		p+=3;
		i++;
	}
	encodeblock(p,(buffer+(i<<2)),length-(p-buf));
	//buffer[(i<<2)+length-(p-buf)]=0;
	return this->buffer;
}

char* Base64Codec::encodeString(char *buffer, int length)
{
	return this->encode((unsigned char *)buffer,length);
}
