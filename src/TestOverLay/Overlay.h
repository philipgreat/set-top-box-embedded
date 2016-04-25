// Overlay.h: interface for the COverlay class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_OVERLAY_H__31DDDFD7_FA52_4DB2_9E0A_62B2EAD4A29A__INCLUDED_)
#define AFX_OVERLAY_H__31DDDFD7_FA52_4DB2_9E0A_62B2EAD4A29A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// C RunTime Header Files
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>

// Windows Header Files:
#include <windows.h>
#include <mmsystem.h> //added to compile under NT
#define INITGUID
#include <objbase.h>
#include <initguid.h>
#include <ddraw.h>                                                                

// Local Headers
#include "resource.h"
// Define some macros
#define INIT_DIRECTDRAW_STRUCT(x) (ZeroMemory(&x, sizeof(x)), x.dwSize=sizeof(x))
#define RAND_INT(x) (rand()*x/RAND_MAX)
#define RANDOM_VELOCITY() ((RAND_INT(5)+3)*2)

// Define some error messages.  If we had many more we'd stick 'em in our RC file.
#define NO_OVERLAY_HARDWARE     "Sorry, In order to run this sample application you must "\
"have a display adapter and driver which support overlays."

#define UNABLE_TO_CREATE_OVERLAY    "Sorry, your display adapter appears to "\
    "support overlays, but we were unable to "\
    "create an overlay in any of the formats "\
    "this app supports (16-bit RGB and YUV).  "\
    "You may want to try shutting down other "\
    "DirectX apps to free video memory, or try "\
    "rerunning this app in a different display "\
"mode."

#define UNABLE_TO_DISPLAY_OVERLAY   "Sorry, we created an overlay on your "\
    "system, but were unable to display it.  "\
    "Please try rerunning this app in "\
"a different display mode."

class COverlay  
{
public:
    LPDIRECTDRAWSURFACE7 GetOverlay();
    void MoveOverlayTimer();
    int DisplayError(HINSTANCE hInst, LPSTR lpstrErr);
    BOOL RestoreAllSurfaces();
    BOOL CreateOverlay();
    BOOL AreOverlaysSupported();
    BOOL DisplayOverlay();
    BOOL LoadImageOntoSurface(LPDIRECTDRAWSURFACE7 lpdds, LPSTR lpstrResID);
    BOOL CopyBitmapToYUVSurface(LPDIRECTDRAWSURFACE7 lpDDSurf, HBITMAP hbm);
    void DestroyOverlay();
    BOOL InitDirectDraw();
    HRESULT CreatePrimarySurface();
    void FreeDirectDraw(void);
    COverlay();
    virtual ~COverlay();

protected:
    LPDIRECTDRAW7        m_lpdd;
    LPDIRECTDRAWSURFACE7 m_lpddsPrimary;
    LPDIRECTDRAWSURFACE7 m_lpddsOverlay;
    
    int m_nOverlayXPos, m_nOverlayYPos;
    int m_nOverlayXVel, m_nOverlayYVel;
    int m_nOverlayWidth, m_nOverlayHeight;
    int m_nOverlayFlipCounter; 
    DWORD m_dwOverlayXPositionAlignment;  // used to keep track of any alignment
    // restrictions on the X postion of
    // our overlay surface.  Comes from the
    // the DDCAPS dwBoundaryAlignDest field.
    // Initialized in DisplayOverlay().
    
    // These are the pixel formats this app supports.  Most display adapters
    // with overlay support will recognize one or more of these formats.
    // The first on our list is the 16-bit RGB formats.  These have the widest
    // support.
    
    
};



#endif // !defined(AFX_OVERLAY_H__31DDDFD7_FA52_4DB2_9E0A_62B2EAD4A29A__INCLUDED_)

