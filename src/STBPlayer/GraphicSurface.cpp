// CGraphicSurface.cpp: implementation of the CCGraphicSurface class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "GraphicSurface.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
#define INIT_DIRECTDRAW_STRUCT(x) (ZeroMemory(&x, sizeof(x)), x.dwSize=sizeof(x))
#define NUM_GRAPHICSURFACE_FORMATS (sizeof(g_ddpfGraphicSurfaceFormats) / sizeof(g_ddpfGraphicSurfaceFormats[0]))



DDPIXELFORMAT g_ddpfGraphicSurfaceFormats[] = 
{
    {sizeof(DDPIXELFORMAT), DDPF_RGB, 0, 16,  0x7C00, 0x03e0, 0x001F, 0},   // 16-bit RGB 5:5:5
    {sizeof(DDPIXELFORMAT), DDPF_RGB, 0, 16,  0xF800, 0x07e0, 0x001F, 0},   // 16-bit RGB 5:6:5
    {sizeof(DDPIXELFORMAT), DDPF_FOURCC,MAKEFOURCC('U','Y','V','Y'),0,0,0,0,0}, // UYVY
    {sizeof(DDPIXELFORMAT), DDPF_FOURCC,MAKEFOURCC('Y','U','Y','2'),0,0,0,0,0}  // YUY2
};








CGraphicSurface::CGraphicSurface(PEXTSUPP_ALPHA_STREAM_BUFFER pm_bufer)
{
    p_lpdd            = NULL;

    memset(&m_GraphicSurface_Alpha_Stream, 0, sizeof(EXTSUPP_ALPHA_STREAM_BUFFER));

    if (InitDirectDraw())
    {
        memcpy(&m_GraphicSurface_Alpha_Stream, pm_bufer, sizeof(EXTSUPP_ALPHA_STREAM_BUFFER));

        if (!CreateGraphicSurface())
        {
            memset(&m_GraphicSurface_Alpha_Stream, 0, sizeof(EXTSUPP_ALPHA_STREAM_BUFFER));
        }

        memcpy(pm_bufer, &m_GraphicSurface_Alpha_Stream, sizeof(EXTSUPP_ALPHA_STREAM_BUFFER));
    }
}


CGraphicSurface::~CGraphicSurface()
{
    DestroyGraphicSurface();
}


//****************************************************************************
//* Function: InitDirectDraw
//*
//* Description:
//*     Performs DirectDraw initialization.  Creates a primary surface which
//*     is needed to display our overlay on.  The actual overlay surface is
//*     created later in our CreateOverlay() call.
//****************************************************************************
BOOL CGraphicSurface::InitDirectDraw()
{
    HRESULT         ddrval;

    ddrval = DirectDrawCreateEx(NULL, (VOID**)&p_lpdd, IID_IDirectDraw7, NULL);
    if( FAILED(ddrval))
        goto ErrorOut;
    
    // For NORMAL cooperative level we no longer need to provide an HWND.
    ddrval = p_lpdd->SetCooperativeLevel(NULL, DDSCL_NORMAL);
    if( FAILED(ddrval))
        goto ErrorOut;
    
    return TRUE;
    
ErrorOut:
    
    FreeDirectDraw();

    return FALSE;    
}


//****************************************************************************
//* Function: FreeDirectDraw
//*
//* Description:
//*             Releases core DirectDraw objects
//****************************************************************************
void CGraphicSurface::FreeDirectDraw()
{
    if (p_lpdd)
    {
        p_lpdd->Release();
        p_lpdd = NULL;
    }    
}


//****************************************************************************
//* Function: CreateOverlay
//*
//* Description:
//*     This is where we create the overlay surface, and put the flying insect 
//*     artwork on it.
//****************************************************************************
BOOL CGraphicSurface::CreateGraphicSurface()
{
    DDSURFACEDESC2   ddsdGraphicSurface;
    HRESULT          ddrval;
    int              i;

    INIT_DIRECTDRAW_STRUCT(ddsdGraphicSurface);

    ddsdGraphicSurface.ddsCaps.dwCaps = DDSCAPS_VIDEOMEMORY    |
                                        DDSCAPS_LOCALVIDMEM    |
                                        DDSCAPS_OFFSCREENPLAIN |
                                        0 ;

    ddsdGraphicSurface.dwFlags = DDSD_CAPS        |
                                 DDSD_HEIGHT      |
                                 DDSD_WIDTH       |
                                 DDSD_PITCH       |
                                 DDSD_PIXELFORMAT |
                                 0;

    ddsdGraphicSurface.dwWidth  = m_GraphicSurface_Alpha_Stream.dwAlphaBufferWidth;
    ddsdGraphicSurface.dwHeight = m_GraphicSurface_Alpha_Stream.dwAlphaBufferHeight;
    ddsdGraphicSurface.lPitch   = m_GraphicSurface_Alpha_Stream.dwAlphaBufferStride;
    
    // Try to create an overlay surface using one of the pixel formats in our
    // global list.
    i=0;
    do 
    {
        ddsdGraphicSurface.ddpfPixelFormat    = g_ddpfGraphicSurfaceFormats[i];
        // Try to create the overlay surface
        ddrval = p_lpdd->CreateSurface(&ddsdGraphicSurface, &p_lpddsGraphicSurface, NULL);
    } while( FAILED(ddrval) && (++i < NUM_GRAPHICSURFACE_FORMATS) );


    // If we failed to create an overlay surface, let's try again with a single
    // (non-flippable) buffer.
    if (FAILED(ddrval))
    {
        return FALSE;
    }

    // Put the first bug image onto the first buffer of our complex surface.
    if ( !PrepareImageforSurface(p_lpddsGraphicSurface) )
        return FALSE;

    return TRUE;
}


//****************************************************************************
//* Function: DestroyOverlay()
//* Description:
//*     Hides the overlay then releases it's surface.
//****************************************************************************
void CGraphicSurface::DestroyGraphicSurface()
{
    if (p_lpddsGraphicSurface)
    {
        // Use UpdateOverlay() with the DDOVER_HIDE flag to remove an overlay 
        // from the display.
        p_lpddsGraphicSurface->Release();
        p_lpddsGraphicSurface    = NULL;
        memset(&m_GraphicSurface_Alpha_Stream, 0, sizeof(EXTSUPP_ALPHA_STREAM_BUFFER));
    }
}


//****************************************************************************
//* Function: RestoreAllSurfaces
//****************************************************************************
BOOL CGraphicSurface::RestoreAllSurfaces()
{
    HRESULT ddrval;

    if(!p_lpddsGraphicSurface)
    {
        if (!CreateGraphicSurface())
            return FALSE;
    }
        
    // Try Restoring the primary surface.
    ddrval = p_lpddsGraphicSurface->Restore();
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
            DestroyGraphicSurface();
            p_lpddsGraphicSurface = NULL;
            
            return FALSE;
        }
        
        else 
            return FALSE;
    }
    
    // Try Restoring the overlay surface.
    ddrval = p_lpddsGraphicSurface->Restore();
    if (FAILED(ddrval))
        return FALSE;
    
    // Reload artwork onto overlay
    // Put the first bug image onto the first buffer of our complex surface.
    if ( !PrepareImageforSurface(p_lpddsGraphicSurface) )
        return FALSE;

    return TRUE;        
}


DWORD CGraphicSurface::GetGraphicSurfaceStartingAddress()
{
    return m_GraphicSurface_Alpha_Stream.dwAlphaBufferStartingAddress;
}


//****************************************************************************
//* Function: PrepareImageforSurface
//* Description:
//*     Prepare the DirectDraw surface for some specified colors.
//****************************************************************************
BOOL CGraphicSurface::PrepareImageforSurface(LPDIRECTDRAWSURFACE7 lpdds)
{
    BOOL              bRetVal = FALSE;
    HRESULT           ddrval;
    DDSURFACEDESC2    ddsd;

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


    //
    // ********* get the surface's virtual address *********
    //
    ddrval = lpdds->Lock(NULL, &ddsd, DDLOCK_WAIT, NULL);
    if (FAILED(ddrval)) goto Exit;

    m_GraphicSurface_Alpha_Stream.dwAlphaBufferStartingAddress = (DWORD) ddsd.lpSurface;

	// color-fill the Graphic Surface
    foo(2);

    ddrval = lpdds->Unlock(NULL);
    if (FAILED(ddrval)) goto Exit;

    bRetVal = TRUE;

Exit:
    return bRetVal;    
}


// dummy function to color fill the Graphic Surface
void CGraphicSurface::foo(BYTE bAlphaDyn)
{
    BYTE  AlphaFactor;
    BYTE  AlphaFactor0, AlphaFactor1, AlphaFactor2, AlphaFactor3;
    BYTE  AlphaFactor4, AlphaFactor5, AlphaFactor6, AlphaFactor7;
    int   i, j;

    DWORD  dwAlphaBuffer_Width  = m_GraphicSurface_Alpha_Stream.dwAlphaBufferWidth;
    DWORD  dwAlphaBuffer_Height = m_GraphicSurface_Alpha_Stream.dwAlphaBufferHeight;
    DWORD  dwAlpha_Stride       = m_GraphicSurface_Alpha_Stream.dwAlphaBufferStride;
    LPBYTE p_TempAddr           = (LPBYTE) m_GraphicSurface_Alpha_Stream.dwAlphaBufferStartingAddress;


    if (bAlphaDyn == 1)
    {
        AlphaFactor0 = 0x77;
        AlphaFactor1 = 0x00;
        AlphaFactor2 = 0xFF;
        AlphaFactor3 = 0x22;

        for (j=0; j < (int)dwAlphaBuffer_Height; j++)
        {
            for (i = 0; i < (int)dwAlphaBuffer_Width; i++)
            {
                if (i < (int)(dwAlphaBuffer_Width/4))
                {
                   p_TempAddr[i] = AlphaFactor0;
                }
                else if ( (i >= (int) (dwAlphaBuffer_Width/4)) &&
                          (i <  (int) (2*(dwAlphaBuffer_Width/4))) )
                {
                    p_TempAddr[i] = AlphaFactor1;
                }
                else if ( (i >= (int) (2*(dwAlphaBuffer_Width/4))) &&
                          (i <  (int) (3*(dwAlphaBuffer_Width/4))) )
                {
                    p_TempAddr[i] = AlphaFactor2;
                }
                else
                {
                    p_TempAddr[i] = AlphaFactor3;
                }
            }
            p_TempAddr += dwAlpha_Stride;
        }
    }
    else if (bAlphaDyn == 2)
    {
        AlphaFactor0 = 0x77;
        AlphaFactor1 = 0x00;
        AlphaFactor2 = 0xFF;
        AlphaFactor3 = 0x22;
    
        AlphaFactor4 = 0x00;
        AlphaFactor5 = 0xFF;
        AlphaFactor6 = 0x77;
        AlphaFactor7 = 0x22;
    
        for (j=0; (j < (int)dwAlphaBuffer_Height); j++)
        {
            if (j < (int)(dwAlphaBuffer_Height/2))
            {
                for (i = 0; i < (int)dwAlphaBuffer_Width; i++)
                {
                    if (i < (int)(dwAlphaBuffer_Width/4))
                    {
                        p_TempAddr[i] = AlphaFactor0;
                    }
                    else if ( (i >= (int)(dwAlphaBuffer_Width/4)) &&
                              (i <  (int)(2*(dwAlphaBuffer_Width/4))) )
                    {
                        p_TempAddr[i] = AlphaFactor1;
                    }
                    else if ( (i >= (int)(2*(dwAlphaBuffer_Width/4))) &&
                              (i <  (int)(3*(dwAlphaBuffer_Width/4))) )
                    {
                        p_TempAddr[i] = AlphaFactor2;
                    }
                    else
                    {
                        p_TempAddr[i] = AlphaFactor3;
                    }
                }
            }
            else
            {
                for (i = 0; (i < (int)dwAlphaBuffer_Width); i++)
                {
                    if (i < (int)(dwAlphaBuffer_Width/4))
                    {
                        p_TempAddr[i] = AlphaFactor4;
                    }
                    else if ( (i >= (int)(dwAlphaBuffer_Width/4)) &&
                              (i <  (int)(2*(dwAlphaBuffer_Width/4))) )
                    {
                        p_TempAddr[i] = AlphaFactor5;
                    }
                    else if ( (i >= (int)(2*(dwAlphaBuffer_Width/4))) &&
                              (i <  (int)(3*(dwAlphaBuffer_Width/4))) )
                    {
                        p_TempAddr[i] = AlphaFactor6;
                    }
                    else
                    {
                        p_TempAddr[i] = AlphaFactor7;
                    }
                }
            }
            p_TempAddr += dwAlpha_Stride;
    
        }
    }
    else
    {
        AlphaFactor = 0x44;
    
        for (i = 0; (i < (int)dwAlphaBuffer_Height); i++)
        {
            if (i == (int)(dwAlphaBuffer_Height/2))
                AlphaFactor = 0xCC;
    
            for (j = 0; (j < (int)dwAlphaBuffer_Width); j++)
            {
                *p_TempAddr = AlphaFactor;
                p_TempAddr++;
            }
        }   
    }
}

