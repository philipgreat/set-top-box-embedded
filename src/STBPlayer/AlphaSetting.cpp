// AlphaSetting.cpp: implementation of the CAlphaSetting class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "AlphaSetting.h"
/*

BOOL SetAlphaRangeRegister(BOOL bEnable, int iAlphaValue);
BOOL SetAlphaStreamRegister(PEXTSUPP_ALPHA_STREAM_BUFFER  pob);
BOOL GetAlphaStreamRegister(PEXTSUPP_ALPHA_STREAM_BUFFER  pob);
BOOL GetConstAlphaFactorRegister(PEXTSUPP_CONST_ALPHA_BUFFER  pob);

*/

#define  ESC_ALPHA_WINDOW                0x9901

#define  S3_Sub_GetConstantAlphaState    0x1
#define  S3_Sub_SetConstantAlphaState    0x2
#define  S3_Sub_GetAlphaStreamState      0x3
#define  S3_Sub_SetAlphaStreamState      0x4
#include "GraphicSurface.h"
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
extern HWND         hwnd = (HWND)NULL;                                // main window handle



static BOOL GetConstAlphaFactorRegister(PEXTSUPP_CONST_ALPHA_BUFFER  pob)
{
    DWORD                             ib;
    EXTSUPP_CONST_ALPHA_BUFFER        ob;
    HDC                               hdcio;
    DWORD                             dwRet = FALSE;

    hdcio = GetDC (hwnd);

    ib = S3_Sub_GetConstantAlphaState;

    dwRet = ExtEscape(hdcio, ESC_ALPHA_WINDOW, sizeof(ib), (char *) &ib, sizeof(ob), (char*) &ob);

    ReleaseDC(hwnd, hdcio);

    *pob = ob;

    /* It is greater than zero if the function is successful,
       except for the QUERYESCSUPPORT printer escape,
       which checks for implementation only.
       The return value is zero if the escape is not implemented.
       A return value less than zero indicates an error. */
    if (dwRet <= 0)
        return FALSE;

    return TRUE;
}


static BOOL SetAlphaRangeRegister(BOOL bEnable, int iAlphaValue)
{
    DWORD             ib;
    DWORD             ob[3];
    HDC               hdcio;
    DWORD             dwRet = FALSE;

    hdcio = GetDC (hwnd);

    ob[0]  = S3_Sub_SetConstantAlphaState;
    ob[1]  = (DWORD) bEnable;
    ob[2]  = (DWORD) iAlphaValue;

    dwRet = ExtEscape(hdcio, ESC_ALPHA_WINDOW, sizeof(ob), (char *) &ob, sizeof(ib), (char*) &ib);

    ReleaseDC(hwnd, hdcio);

    /* It is greater than zero if the function is successful,
       except for the QUERYESCSUPPORT printer escape,
       which checks for implementation only.
       The return value is zero if the escape is not implemented.
       A return value less than zero indicates an error. */
    if (dwRet <= 0)
        return FALSE;

    return TRUE;
}


static BOOL GetAlphaStreamRegister(PEXTSUPP_ALPHA_STREAM_BUFFER  pob)
{
    DWORD                              ib;
    EXTSUPP_ALPHA_STREAM_BUFFER        ob;
    HDC                                hdcio;
    DWORD                              dwRet = FALSE;

    hdcio = GetDC (hwnd);

    ib = S3_Sub_GetAlphaStreamState;

    dwRet = ExtEscape(hdcio, ESC_ALPHA_WINDOW, sizeof(ib), (char *) &ib, sizeof(ob), (char*) &ob);

    ReleaseDC(hwnd, hdcio);

    *pob = ob;

    /* It is greater than zero if the function is successful,
       except for the QUERYESCSUPPORT printer escape,
       which checks for implementation only.
       The return value is zero if the escape is not implemented.
       A return value less than zero indicates an error. */
    if (dwRet <= 0)
        return FALSE;

    return TRUE;
}


static BOOL SetAlphaStreamRegister(PEXTSUPP_ALPHA_STREAM_BUFFER  pob)
{
    DWORD              ib;
    DWORD              ob[3];
    HDC                hdcio;
    DWORD              dwRet = FALSE;

    hdcio = GetDC (hwnd);

    ob[0]  = S3_Sub_SetAlphaStreamState;
    ob[1]  = pob->dwAlphaEnable;
    ob[2]  = pob->dwAlphaBufferStartingAddress;

    dwRet = ExtEscape(hdcio, ESC_ALPHA_WINDOW, sizeof(ob), (char *) &ob, sizeof(ib), (char*) &ib);

    ReleaseDC(hwnd, hdcio);

    /* It is greater than zero if the function is successful,
       except for the QUERYESCSUPPORT printer escape,
       which checks for implementation only.
       The return value is zero if the escape is not implemented.
       A return value less than zero indicates an error. */
    if (dwRet <= 0)
        return FALSE;

    return TRUE;
}

static     EXTSUPP_ALPHA_STREAM_BUFFER   CAlphaDemoDlg_Alpha_Stream;
static     CGraphicSurface*               pm_GraphicSurface=NULL;

CAlphaSetting::CAlphaSetting()
{

}

CAlphaSetting::~CAlphaSetting()
{

}

BOOL CAlphaSetting::SetAlphaValue(int value)
{
#if 1 
	SetAlphaRangeRegister(TRUE,value);
	if (GetAlphaStreamRegister(&CAlphaDemoDlg_Alpha_Stream))
    {
        CAlphaDemoDlg_Alpha_Stream.dwAlphaEnable = TRUE;

		 if (pm_GraphicSurface == NULL)
			pm_GraphicSurface = new CGraphicSurface(&CAlphaDemoDlg_Alpha_Stream);
	}
#endif
	return TRUE;
	//::SetAlphaStreamRegister(
}
