// GraphicSurface.h: interface for the CGraphicSurface class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GRAPHICSURFACE_H__1AFFF022_B5FC_456E_96DA_FFB0874425B2__INCLUDED_)
#define AFX_GRAPHICSURFACE_H__1AFFF022_B5FC_456E_96DA_FFB0874425B2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <memory.h>
// Windows Header Files:
#include <windows.h>
//#include <mmsystem.h> //added to compile under NT
#define INITGUID
#include <objbase.h>
#include <initguid.h>
#include <ddraw.h>  


typedef struct _EXTSUPP_CONST_ALPHA_BUFFER {
    DWORD    dwAlphaEnable;
    DWORD    dwAlphaLevel;
} EXTSUPP_CONST_ALPHA_BUFFER, *PEXTSUPP_CONST_ALPHA_BUFFER;

// Alpha Window Buffer Stucture (Alpha Stream)
typedef struct _EXTSUPP_ALPHA_STREAM_BUFFER {
    DWORD   dwAlphaEnable;
    DWORD   dwAlphaBufferStartingAddress;
    DWORD   dwAlphaBufferWidth;
    DWORD   dwAlphaBufferHeight;
    DWORD   dwAlphaBufferStride;
} EXTSUPP_ALPHA_STREAM_BUFFER, *PEXTSUPP_ALPHA_STREAM_BUFFER;







class CGraphicSurface
{
public:
    CGraphicSurface(PEXTSUPP_ALPHA_STREAM_BUFFER pm_bufer);
    ~CGraphicSurface();

    BOOL  CreateGraphicSurface();

    BOOL  RestoreAllSurfaces();
    void  DestroyGraphicSurface();

    BOOL  InitDirectDraw();
    void  FreeDirectDraw(void);

    BOOL  PrepareImageforSurface(LPDIRECTDRAWSURFACE7 lpdds);

    DWORD GetGraphicSurfaceStartingAddress();

    void  foo(BYTE bAlphaValueDyn);

protected:
    LPDIRECTDRAW7                 p_lpdd;
    LPDIRECTDRAWSURFACE7          p_lpddsGraphicSurface;
    EXTSUPP_ALPHA_STREAM_BUFFER   m_GraphicSurface_Alpha_Stream;

    int m_nOverlayXPos, m_nOverlayYPos;
    int m_nOverlayXVel, m_nOverlayYVel;
    int m_nOverlayWidth, m_nOverlayHeight;
    int m_nOverlayFlipCounter; 
    DWORD m_dwOverlayXPositionAlignment;  // used to keep track of any alignment
};


#endif // !defined(AFX_GRAPHICSURFACE_H__1AFFF022_B5FC_456E_96DA_FFB0874425B2__INCLUDED_)
