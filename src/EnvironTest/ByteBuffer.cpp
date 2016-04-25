// ByteBuffer.cpp: implementation of the ByteBuffer class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ByteBuffer.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
const int initialSize = 1024*1024;
ByteBuffer::ByteBuffer()
{
	writePostion = 0;
	currentSize = initialSize;
	buffer = new char[currentSize];
}

ByteBuffer::~ByteBuffer()
{
	delete buffer;
}
#include <string.h>
#include <stdio.h>
bool ByteBuffer::put(const char *msg, int length)
{
	if(writePostion+length<this->currentSize){
		memcpy(this->buffer+this->writePostion,msg,length);
		this->writePostion+=length;
	}else{
		this->currentSize =writePostion+length+initialSize;
		char *temp=buffer;
		printf("new buffer\n");
		buffer  = new char[currentSize];
		memcpy(this->buffer,temp,this->writePostion);
		delete temp;
		memcpy(this->buffer+this->writePostion,msg,length);
		writePostion += length;	

	}
	return true;
}

char * ByteBuffer::getString() const
{
	this->buffer[writePostion]='\0';
	return this->buffer;
}

void ByteBuffer::reset()
{
	memset(this->buffer,0x00,this->currentSize);
	writePostion = 0;
}
