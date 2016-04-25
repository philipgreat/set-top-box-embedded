// ChannelPlayerOSD.cpp: implementation of the CChannelPlayerOSD class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ChannelPlayerOSD.h"
#include	"AlphaSetting.h"
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CChannelPlayerOSD::CChannelPlayerOSD()
{
	currentStreamPercent = 0;
	timerCount = 0;
	CAlphaSetting::SetAlphaValue(8);
}

CChannelPlayerOSD::~CChannelPlayerOSD()
{

}
#include <stdio.h>


BOOL CChannelPlayerOSD::DrawMenu(char *message,int percent)
{
	HBITMAP         hbm;
    HDC             hdcImage= NULL;
    HDC             hdcSurf = NULL;
    BOOL            bRetVal = FALSE;
    HRESULT         ddrval;
    DDSURFACEDESC2  ddsd;
	

	LPDIRECTDRAWSURFACE7 lpdds = m_lpddsOverlay;

    
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
    //hbm = (HBITMAP)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(lpstrResID), IMAGE_BITMAP, ddsd.dwWidth, ddsd.dwHeight, LR_CREATEDIBSECTION);
	/*
		hbm = (HBITMAP)LoadImage(NULL,
		this->imageFilePath, IMAGE_BITMAP, 
		ddsd.dwWidth, ddsd.dwHeight, LR_LOADFROMFILE|LR_CREATEDIBSECTION);
	memDC = CreateCompatibleDC ( NULL );
	hbm = CreateCompatibleBitmap(memDC,ddsd.dwWidth, ddsd.dwHeight);
	
	*/

	hbm = (HBITMAP)LoadImage(NULL,
		this->imageFilePath, IMAGE_BITMAP, 
		ddsd.dwWidth, ddsd.dwHeight, LR_LOADFROMFILE|LR_CREATEDIBSECTION);
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
		SetBkMode (hdcImage, TRANSPARENT) ;
		HANDLE pen=::CreatePen(0,0,RGB(255,255,255));

		ddrval = lpdds->GetDC(&hdcSurf);
		::SelectObject(hdcImage,pen);
        double perunit=560.0/100;
		//233,217
		POINT *p=new POINT[4];
		(p + 0)->x = 20 + (int)(perunit*percent);
		(p + 0)->y = 233;

		(p + 1)->x = 20 + (int)(perunit*percent)-20;
		(p + 1)->y = 217;

		(p + 2)->x = 20 + (int)(perunit*percent)+20;
		(p + 2)->y = 217;
		
		*(p	+ 3) = *p;
		char str[1024];
		RECT rect;
		rect.left=rect.top=0;
		rect.right=600;
		rect.bottom=40;
		sprintf(str,"%s %s",__TIME__,__DATE__);
		::DrawText(hdcImage,str,strlen(str),&rect,DT_CENTER|DT_VCENTER|DT_SINGLELINE);
		::Polygon(hdcImage,p,4);
		::DeleteObject(pen);
		delete [] p;

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
	//return TRUE;

}
#include <stdio.h>
BOOL CChannelPlayerOSD::ShowVolume(int position)
{
	timerCount = 0;
	CAlphaSetting::SetAlphaValue(8);
	this->DrawVolume(position);
	return this->DisplayOverlay();

}

BOOL CChannelPlayerOSD::DrawVolume(int position)
{
	HBITMAP         hbm;
    HDC             hdcImage= NULL;
    HDC             hdcSurf = NULL;
    BOOL            bRetVal = FALSE;
	HDC				memDC   = NULL;
    HRESULT         ddrval;
    DDSURFACEDESC2  ddsd;
	

	LPDIRECTDRAWSURFACE7 lpdds = m_lpddsOverlay;

    
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
    //hbm = (HBITMAP)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(lpstrResID), IMAGE_BITMAP, ddsd.dwWidth, ddsd.dwHeight, LR_CREATEDIBSECTION);
	/*
		hbm = (HBITMAP)LoadImage(NULL,
		this->imageFilePath, IMAGE_BITMAP, 
		ddsd.dwWidth, ddsd.dwHeight, LR_LOADFROMFILE|LR_CREATEDIBSECTION);
	memDC = CreateCompatibleDC ( NULL );
	hbm = CreateCompatibleBitmap(memDC,ddsd.dwWidth, ddsd.dwHeight);
	
	*/

	memDC = CreateCompatibleDC ( NULL );
	hbm = CreateCompatibleBitmap(memDC,ddsd.dwWidth, ddsd.dwHeight);
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
		SetBkMode (hdcImage, TRANSPARENT) ;
		HANDLE pen=::CreatePen(0,0,RGB(255,255,255));

		ddrval = lpdds->GetDC(&hdcSurf);
		::SelectObject(hdcImage,pen);
        double perunit=560.0/100;

		RECT rect;


		for(int i=0; i<20; i++){
			
			rect.left	= 80 + i * 20 ;
			rect.top	= 218 - i * 5 + 20;
			rect.right	= 80 + 10 + i  * 20;
			rect.bottom	= 218 + 30;
			
			if(i<=(int)((double)position/5.0)){
				FillRect(hdcImage, &rect, (HBRUSH) RGB(255,255,255));
				//FillRect(hdcImage, &rect, (HBRUSH) RGB(255,255,255));			
			}else{
				POINT *points=new POINT[5];
				(points + 0)->x = rect.left;
				(points + 0)->y = rect.top;

				(points + 1)->x = rect.right;
				(points + 1)->y = rect.top;

				(points + 2)->x = rect.right;
				(points + 2)->y = rect.bottom;

				(points + 3)->x = rect.left;
				(points + 3)->y = rect.bottom;

				*(points + 4) = *points;
				//(points + 4)->y = rect.top;
				
				::Polyline(hdcImage,points,5);

				//Rectangle(hdcImage,rect.left-1,rect.top-1,rect.right,rect.bottom);
				delete[] points;
			
			}
		}

		::DeleteObject(pen);
		
        if (FAILED(ddrval))
            goto Exit;
        
        if (BitBlt(hdcSurf, 0, 0, ddsd.dwWidth, ddsd.dwHeight, hdcImage, 0, 0, SRCCOPY) == FALSE)
            goto Exit;
    }
    
    bRetVal = TRUE;
    
Exit:
    if (hdcSurf)
        lpdds->ReleaseDC(hdcSurf);
	if (memDC)
        DeleteDC(memDC);
    if (hdcImage)
        DeleteDC(hdcImage);
    if(hbm)
        DeleteObject(hbm);
    
    return bRetVal; 
}

int CChannelPlayerOSD::OnTimer()
{
	timerCount++;
	if(timerCount>50){
		this->isShowMe = TRUE;
		this->Hide();
	}else if(timerCount<50&&timerCount>30){
		CAlphaSetting::SetAlphaValue((50-timerCount)/3);
		//if menu is showing, update the postion of the triangle
	}
	return 0;
}

BOOL CChannelPlayerOSD::ShowMenu(char *message, int percent)
{	
	char filePath[MAX_PATH];
	char currentDir[MAX_PATH];
	timerCount = 0;
	currentStreamPercent = percent;
	LPDIRECTDRAWSURFACE7 lpdds = m_lpddsOverlay;
	CAlphaSetting::SetAlphaValue(8);

	::GetCurrentDirectory(MAX_PATH,currentDir);

	sprintf(filePath,"%s\\%s",currentDir,"showimage.bmp");//,filePath;
	if (!this->SetBackgroudImage(filePath))
        return FALSE;
	
	if (!DrawMenu(message,percent))
	{
		return FALSE;
	}

    if(!DisplayOverlay())
    {
        return 2;
    }


	return TRUE;
}
bool CChannelPlayerOSD::ToggleShow()
{
	
	if(isShowMe){
		this->ShowMenu("", this->currentStreamPercent);
	}else{
		this->Hide();
	}
	isShowMe = !isShowMe;
	return isShowMe;
}

int CChannelPlayerOSD::UpdatePercent(int percent)
{
	return (this->currentStreamPercent=percent);
}

BOOL CChannelPlayerOSD::ShowMenu()
{
	isShowMe = TRUE;
	timerCount = 0;
	return this->ShowMenu(this->message,this->currentStreamPercent);
}
