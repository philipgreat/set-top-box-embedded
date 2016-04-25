// HighPrecisionTimer.h: interface for the CHighPrecisionTimer class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_HIGHPRECISIONTIMER_H__8EDAF97D_F64D_4D53_9AC3_E7FEACD34E21__INCLUDED_)
#define AFX_HIGHPRECISIONTIMER_H__8EDAF97D_F64D_4D53_9AC3_E7FEACD34E21__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include <windows.h>
class HighPrecisionTimer  
{
private:
	LARGE_INTEGER tim1, tim2, freq;
public:
	double getSpanTime();
	double end();
	double start();
	HighPrecisionTimer();
	virtual ~HighPrecisionTimer();

};

#endif // !defined(AFX_HIGHPRECISIONTIMER_H__8EDAF97D_F64D_4D53_9AC3_E7FEACD34E21__INCLUDED_)
