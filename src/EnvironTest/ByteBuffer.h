// ByteBuffer.h: interface for the ByteBuffer class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BYTEBUFFER_H__3C6D9E3A_E294_4C35_9776_F53D5A8071C4__INCLUDED_)
#define AFX_BYTEBUFFER_H__3C6D9E3A_E294_4C35_9776_F53D5A8071C4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class ByteBuffer  
{
private:
	int writePostion;
	char *buffer;
	int currentSize;
public:
	void reset();
	char * getString()const;
	bool put(const char*msg,int length);
	ByteBuffer();
	virtual ~ByteBuffer();

};

#endif // !defined(AFX_BYTEBUFFER_H__3C6D9E3A_E294_4C35_9776_F53D5A8071C4__INCLUDED_)
