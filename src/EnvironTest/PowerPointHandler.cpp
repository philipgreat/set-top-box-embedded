// PowerPointHandler.cpp: implementation of the PowerPointHandler class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "PowerPointHandler.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

PowerPointHandler::PowerPointHandler()
{

}

PowerPointHandler::~PowerPointHandler()
{

}


#define LINE_START \
"<TABLE BORDER=0 WIDTH='100%%' CELLSPACING=0 CELLPADDING=0><TR>\
<TD BGCOLOR=#000000><TABLE BORDER=0 WIDTH='100%%' CELLSPACING=1 CELLPADDING=2><TR>\
<TD  width=100%% BGCOLOR=#eeeeee  align=left ><pre>ตฺ %u าณ\r\n"
#define LINE_END "</pre></TD></TR></TD></TABLE></TABLE><p>"

int PowerPointHandler::onPage(int index, const char *text)
{
	char buffer[1024];
	if(strlen(text)>2){
	sprintf(buffer,LINE_START,index);
	bytebuffer.put(buffer,strlen(buffer));
	bytebuffer.put(text,strlen(text));
	sprintf(buffer,LINE_END);
	bytebuffer.put(LINE_END,strlen(LINE_END));
	bytebuffer.put("\r\n",2);
	
	}
	return 0;
}