// Overlay.cpp: implementation of the COverlay class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Overlay.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUm_NEW
#endif
#include "resource.h"
typedef struct 
{
    COverlay* pOverlay;
    int iResourceID;
}RESOURCE;

DDPIXELFORMAT g_ddpfOverlayFormats[] = 
{   {sizeof(DDPIXELFORMAT), DDPF_RGB, 0, 16,  0x7C00, 0x03e0, 0x001F, 0},   // 16-bit RGB 5:5:5
    {sizeof(DDPIXELFORMAT), DDPF_RGB, 0, 16,  0xF800, 0x07e0, 0x001F, 0},   // 16-bit RGB 5:6:5
    {sizeof(DDPIXELFORMAT), DDPF_FOURCC,MAKEFOURCC('U','Y','V','Y'),0,0,0,0,0}, // UYVY
    {sizeof(DDPIXELFORMAT), DDPF_FOURCC,MAKEFOURCC('Y','U','Y','2'),0,0,0,0,0}};  // YUY2

#define NUM_OVERLAY_FORMATS (sizeof(g_ddpfOverlayFormats) / sizeof(g_ddpfOverlayFormats[0]))




//****************************************************************************
//* Function: EnumAttachedCallback
//* 
//* Description:
//*     Callback function for EnumAttachedSurfaces().  Used to recursively
//*     load each frame of the flying insect animation onto the appropriate
//*     overlay surface buffer.
//****************************************************************************
HRESULT WINAPI EnumAttachedCallback(LPDIRECTDRAWSURFACE7 lpdds,
									LPDDSURFACEDESC2 lpddsd, LPVOID lpContext)
{
	RESOURCE* pResource    = (RESOURCE*)lpContext;
	int       nResourceID  = pResource->iResourceID;
	HRESULT   hr           = DDENUMRET_OK;
    
    // Check to see if we've gone full circle through all surfaces and are now looking at the first one again.
    if (lpdds == pResource->pOverlay->GetOverlay())
        goto Exit;
    
    if (!pResource->pOverlay->LoadImageOntoSurface(lpdds, MAKEINTRESOURCE(nResourceID)))
    {
        hr = DDENUMRET_CANCEL;
        goto Exit;
    }
    
    nResourceID++;

	RESOURCE  res      = *pResource;
	res.iResourceID    = nResourceID;

    lpdds->EnumAttachedSurfaces((LPVOID)&res, EnumAttachedCallback);    
    
Exit:
    lpdds->Release();
    return DDENUMRET_OK;
}



//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

COverlay::COverlay()
{
    m_lpdd            = NULL;
    m_lpddsPrimary    = NULL;
    m_lpddsOverlay    = NULL;

    if(!InitDirectDraw())
    {
        return;
    }

    if(!AreOverlaysSupported())
    {
        return;
    }
    
    if(!CreateOverlay())
    {
        return;
    }
    
    if(!DisplayOverlay())
    {
        return;
    }
    
}

COverlay::~COverlay()
{
    DestroyOverlay();
    FreeDirectDraw();
}

//****************************************************************************
//* Function: FreeDirectDraw
//*
//* Description:
//*             Releases core DirectDraw objects
//****************************************************************************
void COverlay::FreeDirectDraw()
{
    if (m_lpddsPrimary)
    {
        m_lpddsPrimary->Release();
        m_lpddsPrimary=NULL;
    }
    
    if (m_lpdd)
    {
        m_lpdd->Release();
        m_lpdd=NULL;
    }    
}

//****************************************************************************
//* Function: CreatePrimarySurface()
//*
//* Description:
//*     Creates a Primary Surface.  Implemented as a separate function from
//* InitDirectDraw() because we occasionally need to just recreate the primary
//* surface such as when a mode change occurs.
//****************************************************************************
HRESULT COverlay::CreatePrimarySurface()
{
    DDSURFACEDESC2   ddsd;
    HRESULT         ddrval;
    
    if (!m_lpdd) return E_FAIL;
    
    INIT_DIRECTDRAW_STRUCT(ddsd);
    ddsd.dwFlags = DDSD_CAPS;
    ddsd.ddsCaps.dwCaps = DDSCAPS_PRIMARYSURFACE;
    ddrval = m_lpdd->CreateSurface(&ddsd, &m_lpddsPrimary, NULL );
    
    return ddrval;    
}

//****************************************************************************
//* Function: InitDirectDraw
//*
//* Description:
//*     Performs DirectDraw initialization.  Creates a primary surface which
//*     is needed to display our overlay on.  The actual overlay surface is
//*     created later in our CreateOverlay() call.
//****************************************************************************
BOOL COverlay::InitDirectDraw()
{
    HRESULT         ddrval;
    
    ddrval = DirectDrawCreateEx(NULL, (VOID**)&m_lpdd, IID_IDirectDraw7, NULL);
    if( FAILED(ddrval))
        goto ErrorOut;
    
    // For NORMAL cooperative level we no longer need to provide an HWND.
    ddrval = m_lpdd->SetCooperativeLevel(NULL, DDSCL_NORMAL);
    if( FAILED(ddrval))
        goto ErrorOut;
    
    ddrval= CreatePrimarySurface();
    if( FAILED(ddrval))
        goto ErrorOut;
    
    return TRUE;
    
ErrorOut:
    
    FreeDirectDraw();
    
    return FALSE;    
}

//****************************************************************************
//* Function: DestroyOverlay()
//* Description:
//*     Hides the overlay then releases it's surface.
//****************************************************************************
void COverlay::DestroyOverlay()
{
    if (m_lpddsOverlay)
    {
        // Use UpdateOverlay() with the DDOVER_HIDE flag to remove an overlay 
        // from the display.
        m_lpddsOverlay->UpdateOverlay(NULL, m_lpddsPrimary, NULL, DDOVER_HIDE, NULL);
        m_lpddsOverlay->Release();
        m_lpddsOverlay    = NULL;
    }    
}

//****************************************************************************
//* Function: CopyBitmapToYUVSurface
//* Description: 
//*     Copies an RGB GDI bitmap to a YUV surface. Both bitmap and surface
//*     must be a multiple of 2 pixels in width for the supported YUV formats.  
//*     The following formats are supported:
//*             YUY2
//*             UYVY
//*     
//*     The "YUY2" YUV pixel format looks like this:
//*         As a series of BYTES:    [Y0][U][Y1][V] (reverse it for a DWORD)
//*
//*     The "UYVY" YUV pixel format looks like this:
//*         As a series of BYTES:    [U][Y0][V][Y1] (reverse it for a DWORD)
//*
//*     As you can see, both formats pack two pixels into a single DWORD. The 
//*     pixels share U and V components and have separate Y components.
//*     
//* Returns: TRUE if successful, otherwise FALSE.
//****************************************************************************
BOOL COverlay::CopyBitmapToYUVSurface(LPDIRECTDRAWSURFACE7 lpDDSurf, HBITMAP hbm)
{
    HDC                 hdcImage;
    HRESULT             ddrval;
    DDSURFACEDESC2      ddsd;
    DWORD               x, y, dwWidth, dwHeight;
    LONG                lPitch;
    LPBYTE              pSurf;
    DWORD               dwBytesInRow;
    COLORREF            color;
    BYTE                R,G,B, Y0,Y1,U,V;
    BOOL                bRet = FALSE;
    
    if (hbm == NULL || lpDDSurf == NULL)
        return FALSE;
    
    //
    //  select bitmap into a memoryDC so we can use it.
    //
    hdcImage = CreateCompatibleDC(NULL);
    SelectObject(hdcImage, hbm);
    
    INIT_DIRECTDRAW_STRUCT(ddsd);
    // Lock down the surface so we can modify it's contents.
    ddrval=lpDDSurf->Lock( NULL, &ddsd, DDLOCK_SURFACEMEMORYPTR|DDLOCK_WAIT, NULL);
    if (FAILED(ddrval))
        goto CleanUp;
    
    dwWidth=ddsd.dwWidth;
    dwHeight=ddsd.dwHeight;
    lPitch=ddsd.lPitch;
    pSurf=(LPBYTE)ddsd.lpSurface;
    dwBytesInRow=ddsd.dwWidth*2;
    
    // Go through the image 2 pixels at a time and convert to YUV
    for(y=0; y<dwHeight; y++)
    {
        for(x=0; x<dwWidth; x+=2)
        {
            // The equations for color conversion used here, probably aren't 
            // exact, but they seem to do an OK job.
            color=GetPixel(hdcImage, x,y);
            R=GetRValue(color);
            G=GetGValue(color);
            B=GetBValue(color);
            Y0= (BYTE)(0.29*R + 0.59*G + 0.14*B);
            U= (BYTE)(128.0 - 0.14*R - 0.29*G + 0.43*B);
            
            color=GetPixel(hdcImage, x+1,y);
            R=GetRValue(color);
            G=GetGValue(color);
            B=GetBValue(color);
            Y1= (BYTE)(0.29*R + 0.57*G + 0.14*B);
            V= (BYTE)(128.0 + 0.36*R - 0.29*G - 0.07*B);
            
            switch (ddsd.ddpfPixelFormat.dwFourCC)
            {
            case MAKEFOURCC('Y','U','Y','2'): 
                *(pSurf++) = Y0;
                *(pSurf++) = U;
                *(pSurf++) = Y1;
                *(pSurf++) = V;
                break;
            case MAKEFOURCC('U','Y','V','Y'): 
                *(pSurf++) = U;
                *(pSurf++) = Y0;
                *(pSurf++) = V;
                *(pSurf++) = Y1;
                break;
            }                       
        }
        pSurf+=(lPitch-dwBytesInRow);
    }
    
    lpDDSurf->Unlock(NULL);     
    
CleanUp:
    if(hdcImage)
        DeleteDC(hdcImage);
    
    return TRUE;    
}

//****************************************************************************
//* Function: LoadImageOnToSurface
//* Description:
//*     Loads a resource based bitmap image onto a DirectDraw surface.  Can
//*     covert the bitmap to all RGB formats, plus a couple YUV formats.
//****************************************************************************
BOOL COverlay::LoadImageOntoSurface(LPDIRECTDRAWSURFACE7 lpdds, LPSTR lpstrResID)
{
    HBITMAP         hbm;
    HDC             hdcImage= NULL;
    HDC             hdcSurf = NULL;
    BOOL            bRetVal = FALSE;
    HRESULT         ddrval;
    DDSURFACEDESC2  ddsd;
    
    if (!lpdds)
        return FALSE;
    
    //
    // get surface size and format.
    //
    INIT_DIRECTDRAW_STRUCT(ddsd);
    ddsd.dwFlags = DDSD_HEIGHT | DDSD_WIDTH;
    ddrval = lpdds->GetSurfaceDesc(&ddsd);
    if (FAILED(ddrval))
        goto Exit;
    
    // Load the bitmap resource.  We'll use LoadImage() since it'll scale the 
    // image to fit our surface, and maintain the color information in the
    // bitmap.
    hbm = (HBITMAP)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(lpstrResID), IMAGE_BITMAP, ddsd.dwWidth, ddsd.dwHeight, LR_CREATEDIBSECTION);
    if (hbm == NULL)
        goto Exit;
    
    
    // If our surface is a FOURCC YUV format, we need to do a little work to convert
    // our RGB resource bitmap into the appropriate YUV format.
    if (ddsd.ddpfPixelFormat.dwFlags == DDPF_FOURCC)
    {
        if (!CopyBitmapToYUVSurface(lpdds, hbm))
            goto Exit;        
    }
    else  //Looks like we're just using a standard RGB surface format, let GDI do the work.
    {
        // Create a DC and associate the bitmap with it.
        hdcImage = CreateCompatibleDC(NULL);
        SelectObject(hdcImage, hbm);
        
        ddrval = lpdds->GetDC(&hdcSurf);
        if (FAILED(ddrval))
            goto Exit;
        
        if (BitBlt(hdcSurf, 0, 0, ddsd.dwWidth, ddsd.dwHeight, hdcImage, 0, 0, SRCCOPY) == FALSE)
            goto Exit;
    }
    
    bRetVal = TRUE;
    
Exit:
    if (hdcSurf)
        lpdds->ReleaseDC(hdcSurf);
    if (hdcImage)
        DeleteDC(hdcImage);
    if(hbm)
        DeleteObject(hbm);
    
    return bRetVal;    
}


//****************************************************************************
//* Function: DisplayOverlay
//*
//* Description:
//*     Displays the overlay on the primary surface
//****************************************************************************
BOOL COverlay::DisplayOverlay()
{
    HRESULT         ddrval;
    RECT            rs, rd;
    DDOVERLAYFX     ovfx;
    DDCAPS          capsDrv;
    unsigned int    uStretchFactor1000;
    unsigned int    uDestSizeAlign, uSrcSizeAlign;
    DWORD           dwUpdateFlags;
    
    if(!m_lpdd || !m_lpddsPrimary || !m_lpddsOverlay)
        return FALSE;
    
    // Get driver capabilities
    INIT_DIRECTDRAW_STRUCT(capsDrv);
    ddrval = m_lpdd->GetCaps(&capsDrv, NULL);
    if (FAILED(ddrval))
        return FALSE;
    
    // We need to check the minimum stretch.  Many display adpators require that
    // the overlay be stretched by a minimum amount.  The stretch factor will 
    // usually vary with the display mode (including changes in refresh rate).
    // The stretch factor is returned x1000.
    uStretchFactor1000 = capsDrv.dwMinOverlayStretch>1000 ? capsDrv.dwMinOverlayStretch : 1000;
    
    // Grab any alignment restrictions.  The DDCAPS struct contains a series of
    // alignment fields that are not clearly defined. They are intended for
    // overlay use.  It's important to observe alignment restrictions.
    // Many adapters with overlay capabilities require the overlay image be
    // located on 4 or even 8 byte boundaries, and have similar restrictions
    // on the overlay width (for both source and destination areas).
    uDestSizeAlign = capsDrv.dwAlignSizeDest;
    uSrcSizeAlign =  capsDrv.dwAlignSizeSrc;
    
    // Set the flags we'll send to UpdateOverlay
    dwUpdateFlags = DDOVER_SHOW | DDOVER_DDFX;
    
    // Does the overlay hardware support source color keying?
    // If so, we can hide the black background around the image.
    // This probably won't work with YUV formats
    if (capsDrv.dwCKeyCaps & DDCKEYCAPS_SRCOVERLAY)
        dwUpdateFlags |= DDOVER_KEYSRCOVERRIDE;
    
    // Create an overlay FX structure so we can specify a source color key.
    // This information is ignored if the DDOVER_SRCKEYOVERRIDE flag isn't set.
    INIT_DIRECTDRAW_STRUCT(ovfx);
    ovfx.dckSrcColorkey.dwColorSpaceLowValue=0; // Specify black as the color key
    ovfx.dckSrcColorkey.dwColorSpaceHighValue=0;
    
    // Set up our Source Rect. This is the area of the overlay surface we
    // want to display.  If you want to display your entire surface and
    // happen to know for certain that your surface width meets any alignment
    // restrictions you can go ahead and pass NULL for the source rect in your
    // calls to UpdateOverlay().  Our surface width of 320 probably will meet
    // every alignment restriction, but just in case we'll create a source rect
    // and check for it.
    rs.left=0; 
	rs.top=0; 
	// position 0,0 is already position (boundary aligned)
    rs.right = 320;
    rs.bottom = 240;
    //Apply any size alignment restrictions if necessary.
    if (capsDrv.dwCaps & DDCAPS_ALIGNSIZESRC && uSrcSizeAlign)
        rs.right -= rs.right % uSrcSizeAlign;
    
    // Set up our destination rect, indicating where we want the overlay to 
    // appear on the primary surface.  This is where we have to take into 
    // account any stretch factor which may be needed to ensure the overlay is
    // displayed.  Really only the destination width must be stretched for the
    // overlay hardware to work, but we stretch the height as well just to
    // maintain a proper aspect ratio.
    
    
    // Note: We use the source rect dimensions, not the surface dimensions in
    // case they differ.
    // UpdateOverlay will fail unless the minimum stretch value is observed.
    
    rd.left=0; rd.top=0; 
    rd.right  = (rs.right*uStretchFactor1000+999)/1000; // adding 999 takes care of integer truncation problems.
    rd.bottom = rs.bottom*uStretchFactor1000/1000;
    
    // It's also important to observe any alignment restrictions on size and
    // position with respect to the destination rect. Tweak the destination 
    // width a bit more to get the size alignment correct (Be sure to round up
    // to keep any minimum stretch restrictions met). we'll assume the 
    // position 0,0 is already "position aligned".
    if (capsDrv.dwCaps & DDCAPS_ALIGNSIZEDEST && uDestSizeAlign)
        rd.right = (int)((rd.right+uDestSizeAlign-1)/uDestSizeAlign)*uDestSizeAlign;
    
    // Make the call to UpdateOverlay() which actually displays the overlay on
    // the screen.
    ddrval = m_lpddsOverlay->UpdateOverlay(&rs, m_lpddsPrimary, &rd, dwUpdateFlags, &ovfx);
    if(FAILED(ddrval))
    {
        // Ok, the call to UpdateOVerlay() failed.  A likely cause is the
        // driver lied about the minimum stretch needed. 
        // Ideally we should try upping the destination size a bit, or
        // perhaps shrinking the source size so the destination stretch
        // is effectively higher.   For this sample, however, we'll just
        // bail!
        return FALSE;
    }
    
    // Set the initial position and velocity for our overlay.  We'll actually
    // move the image around using a timer proc (see MoveOverlayTimerCallback
    // below).
    m_nOverlayXPos = 0;
    m_nOverlayYPos = 0;
    m_nOverlayXVel = RANDOM_VELOCITY();
    m_nOverlayYVel = RANDOM_VELOCITY();
    m_nOverlayWidth = rd.right - rd.left;
    m_nOverlayHeight = rd.bottom - rd.top;
    m_nOverlayFlipCounter=0;
    
    // Set the "destination position alignment" global so we won't have to
    // keep calling GetCaps() everytime we move the overlay surface.
    if (capsDrv.dwCaps & DDCAPS_ALIGNBOUNDARYDEST)
        m_dwOverlayXPositionAlignment = capsDrv.dwAlignBoundaryDest;
    else 
        m_dwOverlayXPositionAlignment = 0;
    
    return TRUE;
}

//****************************************************************************
//* Function: AreOverlaysSupported
//*
//* Description:
//*     Determines whether or not the display hardware supports overlays.  If
//*     so, the function returns TRUE, otherwise FALSE.
//****************************************************************************
BOOL COverlay::AreOverlaysSupported()
{
    DDCAPS  capsDrv;
    HRESULT ddrval;
    
    // Get driver capabilities to determine Overlay support.
    INIT_DIRECTDRAW_STRUCT(capsDrv);
    ddrval = m_lpdd->GetCaps(&capsDrv, NULL);
    if (FAILED(ddrval))
        return FALSE;
    
    // Does the driver support overlays in the current mode? 
    // (Currently the DirectDraw emulation layer does not support overlays.
    // Overlay related APIs will fail without hardware support).  
    if (!(capsDrv.dwCaps & DDCAPS_OVERLAY))
        return FALSE;
    
    return TRUE;    
}

//****************************************************************************
//* Function: CreateOverlay
//*
//* Description:
//*     This is where we create the overlay surface, and put the flying insect 
//*     artwork on it.
//****************************************************************************
BOOL COverlay::CreateOverlay()
{
    DDSURFACEDESC2   ddsdOverlay;
    HRESULT          ddrval;
    int              i;
    
    if (!m_lpdd || !m_lpddsPrimary)
        return FALSE;
    
    // It's currently not possible to query for pixel formats supported by the
    // overlay hardware (though GetFourCCCodes() usually provides a partial 
    // list).  Instead you need to call CreateSurface() to try a variety of  
    // formats till one works.  
    INIT_DIRECTDRAW_STRUCT(ddsdOverlay);
    ddsdOverlay.ddsCaps.dwCaps=DDSCAPS_OVERLAY | DDSCAPS_FLIP | DDSCAPS_COMPLEX | DDSCAPS_VIDEOMEMORY;
    ddsdOverlay.dwFlags= DDSD_CAPS|DDSD_HEIGHT|DDSD_WIDTH|DDSD_BACKBUFFERCOUNT| DDSD_PIXELFORMAT;
    ddsdOverlay.dwWidth=320;
    ddsdOverlay.dwHeight=240;
    ddsdOverlay.dwBackBufferCount=2;
    
    // Try to create an overlay surface using one of the pixel formats in our
    // global list.
    i=0;
    do 
    {
        ddsdOverlay.ddpfPixelFormat    = g_ddpfOverlayFormats[i];
        // Try to create the overlay surface
        ddrval = m_lpdd->CreateSurface(&ddsdOverlay, &m_lpddsOverlay, NULL);
    } while( FAILED(ddrval) && (++i < NUM_OVERLAY_FORMATS) );
    
    // If we failed to create an overlay surface, let's try again with a single
    // (non-flippable) buffer.
    if (FAILED(ddrval))
    {
        // Just in case we're short on video memory or the hardware doesn't like flippable
        // overlay surfaces, let's make another pass using a single buffer.
        ddsdOverlay.dwBackBufferCount=0;
        ddsdOverlay.ddsCaps.dwCaps=DDSCAPS_OVERLAY | DDSCAPS_VIDEOMEMORY;
        ddsdOverlay.dwFlags= DDSD_CAPS|DDSD_HEIGHT|DDSD_WIDTH|DDSD_PIXELFORMAT;
        // Try to create the overlay surface
        ddrval = m_lpdd->CreateSurface(&ddsdOverlay, &m_lpddsOverlay, NULL);
        i=0;
        do 
        {
            ddsdOverlay.ddpfPixelFormat    = g_ddpfOverlayFormats[i];
            ddrval = m_lpdd->CreateSurface(&ddsdOverlay, &m_lpddsOverlay, NULL);
        } while( FAILED(ddrval) && (++i < NUM_OVERLAY_FORMATS) );
        
        // We just couldn't create an overlay surface.  Let's exit.
        if (FAILED(ddrval))
            return FALSE;
    }
    
    // Put the first bug image onto the first buffer of our complex surface.
    if (!LoadImageOntoSurface(m_lpddsOverlay, MAKEINTRESOURCE(IDB_BUGIMAGE1)))
        return FALSE;
    
    // This will recursively get all back buffers and load them with the appropriate image.
    RESOURCE res;
    res.pOverlay    = this;
    res.iResourceID    = IDB_BUGIMAGE2;
    ddrval = m_lpddsOverlay->EnumAttachedSurfaces((LPVOID)&res, EnumAttachedCallback);
    if (FAILED(ddrval))
        return FALSE;
    
    return TRUE;    
}

//****************************************************************************
//* Function: RestoreAllSurfaces
//****************************************************************************
BOOL COverlay::RestoreAllSurfaces()
{
    HRESULT ddrval;
    
    // It's possible that our surfaces were destroyed in a prior call to 
    // RestoreAllSurfaces().  If this happened we need to check for it, 
    // and perhaps try to recreate the surfaces.
    if (!m_lpddsPrimary)
    {
        ddrval = CreatePrimarySurface();
        if (FAILED(ddrval))
        {
            // We probably couldn't recreate the primary because someone has
            // exclusive mode.
            m_lpddsPrimary = NULL;
            return FALSE;
        }
    }
    
    if(!m_lpddsOverlay)
        if (!CreateOverlay())
            return FALSE;
        
        // Try Restoring the primary surface.
    ddrval = m_lpddsPrimary->Restore();
    if(FAILED(ddrval))
    {
        // If we weren't able to restore the primary surface, It's probably 
        // because some one else has exclusive mode, or the display mode
        // has been changed such that our primary surface needs to be recreated
        
        // Check to see if the mode changed on us.  Is so, we'll need to recreate
        // all surfaces.  (Note: we could have watched for the WM_DISPLAYCHANGE 
        // message as well)
        if (ddrval == DDERR_WRONGMODE)
        {
            m_lpddsPrimary->Release();
            DestroyOverlay();
            m_lpddsPrimary = NULL;
            m_lpddsOverlay = NULL;
            
            return FALSE;
        }
        
        else 
            return FALSE;
    }
    
    // Try Restoring the overlay surface.
    ddrval = m_lpddsOverlay->Restore();
    if (FAILED(ddrval))
        return FALSE;
    
    // Reload artwork onto overlay
    // Put the first bug image onto the first buffer of our complex surface.
    if ( !LoadImageOntoSurface(m_lpddsOverlay, MAKEINTRESOURCE(IDB_BUGIMAGE1)) )
        return FALSE;
    
    // This will recursively get all back buffers and load them with the appropriate image.
//    ddrval = m_lpddsOverlay->EnumAttachedSurfaces((LPVOID)IDB_BUGIMAGE2, EnumAttachedCallback);
 //   if(FAILED(ddrval))
 //       return FALSE;
    
    // Redisplay overlay
    if(!DisplayOverlay())
        return FALSE;
    
    return TRUE;        
}

//****************************************************************************
//* Function: DisplayError
//* Description:
//*    Displays an error message box.
//****************************************************************************
int COverlay::DisplayError(HINSTANCE hInst, LPSTR lpstrErr)
{
    MSGBOXPARAMS mbp;
    
    mbp.cbSize = sizeof(mbp);
    mbp.hwndOwner=NULL;
    mbp.hInstance=hInst;
    mbp.lpszText = lpstrErr;
    mbp.lpszCaption = "Mosquito Error!";
    mbp.dwStyle = MB_OK | MB_USERICON;
    mbp.lpszIcon = MAKEINTRESOURCE(IDI_BUGICON);
    mbp.dwContextHelpId = NULL;
    mbp.lpfnMsgBoxCallback = NULL;
    mbp.dwLanguageId = NULL;
    
    return MessageBoxIndirect(&mbp);    
}

//****************************************************************************
//* Function: MoveOverlayTimerCallback
//*
//* Description:
//*     TimeProc callback for moving the overlay surface around
//****************************************************************************
void COverlay::MoveOverlayTimer()
{
    HRESULT ddrval;
    DWORD   dwXAligned;
    
    // Make sure the overlay really exists before we mess with it.
    if (!m_lpddsOverlay)
        if (!RestoreAllSurfaces())
            return;
        
        //Add the current velocity vectors to the position.
        m_nOverlayXPos += m_nOverlayXVel;
        m_nOverlayYPos += m_nOverlayYVel;
        
        // Check to see if this new position puts the overlay off the edge of the screen.
        // SetOverlayPosition() won't like that.
        
        // Have we gone off the left edge?
        if (m_nOverlayXPos < 0)
        {
            m_nOverlayXPos = 0;
            m_nOverlayXVel = RANDOM_VELOCITY();
        }
        
        // Have we gone off the right edge?
        if ( (m_nOverlayXPos+m_nOverlayWidth) >  GetSystemMetrics(SM_CXSCREEN))
        {
            m_nOverlayXPos = GetSystemMetrics(SM_CXSCREEN)-m_nOverlayWidth;
            m_nOverlayXVel = -RANDOM_VELOCITY();
        }
        
        // Have we gone off the top edge?
        if (m_nOverlayYPos < 0)
        {
            m_nOverlayYPos = 0;
            m_nOverlayYVel = RANDOM_VELOCITY();
        }
        
        // Have we gone off the bottom edge?
        if ( (m_nOverlayYPos+m_nOverlayHeight) >  GetSystemMetrics(SM_CYSCREEN))
        {
            m_nOverlayYPos = GetSystemMetrics(SM_CYSCREEN)-m_nOverlayHeight;
            m_nOverlayYVel = -RANDOM_VELOCITY();
        }
        
        // We need to check for any alignment restrictions on the X position
        if (m_dwOverlayXPositionAlignment)
            dwXAligned = m_nOverlayXPos - m_nOverlayXPos % m_dwOverlayXPositionAlignment;
        else
            dwXAligned = m_nOverlayXPos;
        
        // Set the overlay to it's new position.
        ddrval = m_lpddsOverlay->SetOverlayPosition(dwXAligned, m_nOverlayYPos);
        if (ddrval == DDERR_SURFACELOST)
        {
            if (!RestoreAllSurfaces()) 
                return;
        }
        
        // Every fourth time this timer proc is called, lets flip the overlay surface.
        if (m_nOverlayFlipCounter++ > 3) 
        {
            m_nOverlayFlipCounter = 0; // reset counter
            // Flip to the next image in the sequence.  This is gonna fail if we
            // our overlay surface only contains one buffer (see CreateOverlay. 
            // This is a possibility), but the failure should be benign.
            m_lpddsOverlay->Flip(NULL, DDFLIP_WAIT);
        }        
}

LPDIRECTDRAWSURFACE7 COverlay::GetOverlay()
{
    return m_lpddsOverlay;
}
