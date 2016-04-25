
CC=g++
OBJS=Parameter.o Parameters.o \
	STBConfiguration.o TestContainer.o URLParameters.o WebDateTime.o\
	HttpUtil.o
CFLAGS= -Wall -O2  -I/usr/X11R6/include 

LINK_FLAGS= 

all: TestContainer

TestContainer: ${OBJS}
	${CC} ${LINK_FLAGS} -o  $@  $^
TestContainer.o: TestContainer.cpp
	${CC} ${CFLAGS} -c $<
Parameter.o: Parameter.cpp Parameter.h
	${CC} ${CFLAGS} -c $<
Parameters.o: Parameters.cpp Parameters.h
	${CC} ${CFLAGS} -c $<
STBConfiguration.o: STBConfiguration.cpp STBConfiguration.h
	${CC} ${CFLAGS} -c $<
URLParameters.o: URLParameters.cpp URLParameters.h
	${CC} ${CFLAGS} -c $<
WebDateTime.o: WebDateTime.cpp WebDateTime.h
	${CC} ${CFLAGS} -c $<
HttpUtil.o: HttpUtil.cpp HttpUtil.h
	${CC} ${CFLAGS} -c $<
down: clear
	wget -i urllist.lst
clean:
	rm -f ${OBJS}
clear:
	rm -f ${OBJS} *.cpp *.h

