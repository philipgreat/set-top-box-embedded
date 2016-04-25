// AlphaSetting.h: interface for the CAlphaSetting class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ALPHASETTING_H__F29C9AE2_6FEE_49DD_A0AF_B95C33FADB89__INCLUDED_)
#define AFX_ALPHASETTING_H__F29C9AE2_6FEE_49DD_A0AF_B95C33FADB89__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CAlphaSetting  
{
public:
	static BOOL  SetAlphaValue(int value);
	CAlphaSetting();
	virtual ~CAlphaSetting();

};

#endif // !defined(AFX_ALPHASETTING_H__F29C9AE2_6FEE_49DD_A0AF_B95C33FADB89__INCLUDED_)
