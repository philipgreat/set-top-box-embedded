// HighPrecisionTimer.cpp: implementation of the HighPrecisionTimer class.
//
//////////////////////////////////////////////////////////////////////



//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

// HighPrecisionTimer.cpp: implementation of the HighPrecisionTimer class.
//
//////////////////////////////////////////////////////////////////////

#include "HighPrecisionTimer.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

HighPrecisionTimer::HighPrecisionTimer()
{
	QueryPerformanceFrequency(&freq);
}

HighPrecisionTimer::~HighPrecisionTimer()
{

}

double HighPrecisionTimer::start()
{
	QueryPerformanceCounter(&tim1);
	return (double)tim1.QuadPart;
}

double HighPrecisionTimer::end()
{
	QueryPerformanceCounter(&tim2);
	return (double)tim2.QuadPart;
}

double HighPrecisionTimer::getSpanTime()
{
	return (double)(tim2.QuadPart-tim1.QuadPart)/(double)freq.QuadPart;
}


