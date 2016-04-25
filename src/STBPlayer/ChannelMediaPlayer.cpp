// ChannelMediaPlayer.cpp: implementation of the CChannelMediaPlayer class.
//
//////////////////////////////////////////////////////////////////////

#include "ChannelMediaPlayer.h"
#include <stdio.h>
#include <stdlib.h>
#ifndef _WCE
#pragma comment(lib, "Winmm.lib")
#endif
#define HELPER_RELEASE(x) { if (x) x->Release(); x = NULL; }


#define JIF(x) if (FAILED(hr=(x))) \
    {\
	TCHAR msg[1024]={0}; AMGetErrorText(hr,msg,1024);  printf(TEXT("\n0X%08X: %s In: "),hr,msg);\
	printf(#x); printf("\n"); return hr;}

#define LIF(x) if (FAILED(hr=(x))) \
    {RETAILMSG(1, (TEXT("FAILED(hr=0x%x) in ") TEXT(#x) TEXT("\n"), hr));}

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
#define APPLICATIONNAME TEXT("Movie Player")
#define CLASSNAME       TEXT("PlayWndMoviePlayer")
#define VOLUME_SILENCE  (-10000L)

static HRESULT RenderOutputPins(IGraphBuilder *pGB, IBaseFilter *pFilter)
{
    HRESULT         hr = S_OK;
    IEnumPins *     pEnumPin = NULL;
    IPin *          pConnectedPin = NULL, * pPin;
    PIN_DIRECTION   PinDirection;
    ULONG           ulFetched;

    // Enumerate all the pins on the filter.
    hr = pFilter->EnumPins( &pEnumPin );

    if(SUCCEEDED(hr))
    {
        // Step through every pin, looking for the output pins.
        while (S_OK == (hr = pEnumPin->Next( 1L, &pPin, &ulFetched)))
        {
            // Check whether this pin is already connected. If so, ignore it.
            hr = pPin->ConnectedTo(&pConnectedPin);
            if (pConnectedPin)
            {
                // Release the IPin interface on the connected pin.
                pConnectedPin->Release();
                pConnectedPin = NULL;
            }

            if (VFW_E_NOT_CONNECTED == hr)
            {
                // This pin is not connected to another filter yet. Check 
                // whether it is an output pin. If so, use the Filter Graph
                // Manager's Render() method to render the pin.

                hr = pPin->QueryDirection( &PinDirection );
                if ( ( S_OK == hr ) && ( PinDirection == PINDIR_OUTPUT ) )
                {
                    hr = pGB->Render(pPin);
                }
            }
            pPin->Release();

            // If there was an error, stop enumerating.
            if (FAILED(hr))                      
                break;
        }
    }

    // Release the pin enumerator object.
    pEnumPin->Release();
    return hr;
}

CChannelMediaPlayer::CChannelMediaPlayer():
mpGraphBuider(NULL),
mpMediaControl(NULL),
mpMediaEvent(NULL),
mpVideoWindow(NULL),
mpBasicAudio(NULL),
mpBasicVideo(NULL),
mpMediaSeeking(NULL),
mhMainWindow(NULL),
mState(0),playContentType(0)
{

	programURL = new WCHAR[1024*4];
	::ShowCursor(FALSE);
}

CChannelMediaPlayer::~CChannelMediaPlayer()
{
	delete programURL;
}


int CChannelMediaPlayer::CreateMainWindow(HINSTANCE   hInstance)
{
	pReader = NULL;
	pFS = NULL;
	currentVolume = 0;
	this->hInstance=hInstance;
	return 0;
}

HRESULT CChannelMediaPlayer::Init()
{
	currentVolume = 0;
	return 0;	
}
#include <initguid.h>
DEFINE_GUID(CLSID_DescrambleFilter,
	0x68726666, 0xdc93, 0x11ce, 0xa0, 0x99, 0x00, 0xaa, 0x00, 0x47, 0x9a, 0x58);
DEFINE_GUID(IID_IDescramble,
	0x68716666, 0x2fe8, 0x11cf, 0xbc, 0xb1, 0x44, 0x45, 0x53, 0x54, 0x00, 0x00);


static enum  PLAYER_CONTENT_TYPE{
	PROGRAM_TYPE_UNKOWN = 0,
	PROGRAM_TYPE_LIVE,
	PROGRAM_TYPE_TSTV,
	PROGRAM_TYPE_VOD,
	PROGRAM_TYPE_COMMON,
};

static char *protoList[] ={"unkown","live","tstv","vod","dtv","mms"};

static DWORD GetContentType(const char *proto)
{
	
	DWORD index = 0;
	for(int i=0;i<5;i++){
		if(0==strncmp(proto,*(protoList+i),strlen(*(protoList+i))))
		{
			index = i;
			break;
		}
	}
	
	return index;
}

#define A2W(W,A)     MultiByteToWideChar(936,0,(A),strlen((A))+1,(W),strlen((A))+1)

HRESULT CChannelMediaPlayer::RenderFile(const WCHAR *url,HWND owner)
{
	HRESULT hr;
	LONG lHeight, lWidth;

	if(this->mState==PLAYING){		
		this->Release();
	}
	
	JIF(CoCreateInstance(CLSID_FilterGraph, NULL, CLSCTX_INPROC_SERVER, IID_IGraphBuilder, 
		(void **)&this->mpGraphBuider));

	JIF(CoCreateInstance(CLSID_WMAsfReader, NULL, CLSCTX_INPROC,
		IID_IBaseFilter, (void **)&pReader));
	JIF(this->mpGraphBuider->AddFilter(pReader, L"ASF Reader"));
	JIF(pReader->QueryInterface(IID_IFileSourceFilter, (void **) &pFS));
	printf("before render file!\n");
	JIF(pFS->Load( url, NULL));
	
	JIF(RenderOutputPins(this->mpGraphBuider,pReader));
	JIF(this->mpGraphBuider->QueryInterface(IID_IMediaControl,
		(void **)&this->mpMediaControl));
	JIF(this->mpGraphBuider->QueryInterface(IID_IMediaEventEx, 
		(void **)&this->mpMediaEvent));
	JIF(this->mpGraphBuider->QueryInterface(IID_IMediaSeeking, 
		(void **)&this->mpMediaSeeking));
	JIF(this->mpGraphBuider->QueryInterface(IID_IVideoWindow, 
		(void **)&this->mpVideoWindow));
	JIF(this->mpGraphBuider->QueryInterface(IID_IBasicVideo, 
		(void **)&this->mpBasicVideo));
	JIF(this->mpGraphBuider->QueryInterface(IID_IBasicAudio, 
		(void **)&this->mpBasicAudio));

	//JIF(this->mpVideoWindow->SetWindowForeground(-1));
	//JIF(this->mpVideoWindow->put_Owner((OAHWND)owner));
	//printf("render file 9\n");
	JIF(mpMediaEvent->SetNotifyWindow((OAHWND)owner, WM_GRAPHNOTIFY, 0));
	ShowWindow(owner, SW_SHOWNORMAL);
    RECT grc;
    GetClientRect(owner, &grc);
	JIF(mpVideoWindow->put_Owner((OAHWND)owner));
	JIF(this->mpBasicVideo->GetVideoSize(&lWidth, &lHeight));

	float scale = (grc.right - grc.left) / (float)lWidth;
	long videoHeight = long(lHeight * scale);
	long vOffset = (grc.bottom - grc.top) - videoHeight;
	JIF(mpVideoWindow->SetWindowPosition(grc.left,vOffset / 2, grc.right - grc.left, grc.bottom - vOffset));
	//JIF(mpVideoWindow->put_FullScreenMode(TRUE))
	JIF(mpVideoWindow->SetWindowForeground(-1));
	JIF(mpVideoWindow->put_WindowStyle(WS_CHILD | WS_CLIPSIBLINGS | WS_CLIPCHILDREN));
	UpdateWindow(owner);
	SetForegroundWindow(owner);
    SetFocus(owner);
	JIF(this->mpMediaControl->Run());
	this->SetVolume(50);
	//printf("render file 11\n");
	this->mState=PLAYING;
//END:
	return 0;
}
/*

        JIF(pVW->put_FullScreenMode(lMode));

        // Undo change of message drain
        LIF(pVW->put_MessageDrain((OAHWND) hDrain));

        // Reset video window
        LIF(pVW->SetWindowForeground(-1));

        // Reclaim keyboard focus for player application
        UpdateWindow(ghApp);
        SetForegroundWindow(ghApp);
        SetFocus(ghApp);

*/
LRESULT CChannelMediaPlayer::UnInit()
{
	CloseHandle(this->mhMainWindow);
	this->mState=DESTROYED;
	return 0;
}

HRESULT CChannelMediaPlayer::Release()
{	

	if(this->mState==RELEASED){
		return 0;
	}

	if(NULL!=mpVideoWindow)
    {
        mpVideoWindow->put_Visible(OAFALSE);
        mpVideoWindow->put_Owner(NULL);
    }
	//mpVideoWindow->put_Owner(NULL);

	HELPER_RELEASE(mpBasicAudio);
	HELPER_RELEASE(mpGraphBuider);
	HELPER_RELEASE(mpMediaControl);
	HELPER_RELEASE(mpMediaEvent);
	HELPER_RELEASE(mpVideoWindow);
	HELPER_RELEASE(mpBasicAudio);
	HELPER_RELEASE(mpBasicVideo);
	HELPER_RELEASE(mpMediaSeeking);
	//CloseHandle(this->
	//HELPER_RELEASE(mhMainWindow);
	//fileters===================================================
	HELPER_RELEASE(mpFilterSrc);
	HELPER_RELEASE(mpFilterDest);
	HELPER_RELEASE(mpDescFilter);
	//pins========================================================
	HELPER_RELEASE(mpPinSrcOut);
	HELPER_RELEASE(mpPinDestIn);
	HELPER_RELEASE(mpPinDescOut);
	HELPER_RELEASE(mpPinDescIn);

	this->mState=RELEASED;
	return 0;
}

HRESULT CChannelMediaPlayer::Stop()
{
	HRESULT hr;
	if(this->mState==PLAYING){
		JIF(this->mpMediaControl->Stop());
	}
	this->mState=STOPED;
	return 0;
}

LRESULT CChannelMediaPlayer::PutOwner(HWND owner)
{
	HRESULT hr;
	JIF(
		this->mpVideoWindow->put_Owner((OAHWND)owner)
	);
	return 0;
}
HRESULT CChannelMediaPlayer::Pause()
{
	HRESULT hr;
	if(this->mState==PLAYING){
		JIF(this->mpMediaControl->Pause());
		this->mState=PAUSED;	
	}else{	
		JIF(this->mpMediaControl->Run());
		this->mState=PLAYING;
	}
	return 0;

}

HRESULT CChannelMediaPlayer::PreProcGraphEvent(long *eventCode)
{
    LONG evCode, evParam1, evParam2;
    HRESULT hr=S_OK;

	
    while(SUCCEEDED(mpMediaEvent->GetEvent(&evCode, &evParam1, &evParam2, 0)))
    {
		//_LOG_VAL(evCode);
		//_LOG_VAL(evParam1);
		//_LOG_VAL(evParam2);
		*eventCode=evCode;
		int i=EC_STARVATION;
        // Spin through the events
        hr = mpMediaEvent->FreeEventParams(evCode, evParam1, evParam2);
		
        if(EC_COMPLETE == evCode)
        {
            LONGLONG pos=0;
			
            // Reset to first frame of movie
            hr = this->mpMediaSeeking->SetPositions(&pos, AM_SEEKING_AbsolutePositioning ,
				NULL, AM_SEEKING_NoPositioning);
            if (FAILED(hr))
            {
                // Some filters (like MIDI) may not implement interfaces
                // for IMediaSeeking to allow seek to the start.  In that
                // case, just stop and restart for the same effect.
                JIF(mpMediaControl->Stop());				
                JIF(mpMediaControl->Run());
            }
        }
    }
	
	return hr;

}

BOOL CChannelMediaPlayer::PreProcessURL(const WCHAR *url)
{
	BOOL useDefaultChar = FALSE;

	char *ascurl=new char[(wcslen(url)+1)*2];
	WideCharToMultiByte(936,0,url,
			wcslen(url),ascurl,wcslen(url)*2,
			NULL,&useDefaultChar);

	this->playContentType = GetContentType(ascurl);
	
	WCHAR *p =(WCHAR *) url;
	while(*p!=TEXT(':')&&*p!=TEXT('\0')){
		p++;
	}
	wsprintfW(programURL,L"mms%s",p);
	//MessageBox(NULL,programURL,programURL,MB_OK);
	delete ascurl;
	return TRUE;
}

HRESULT CChannelMediaPlayer::WaitForCompletion()
{
	HRESULT hr;
	JIF(mpMediaEvent->WaitForCompletion(INFINITE, &evCode));
	return 0L;
}
#define ONE_SECOND 10000000
HRESULT CChannelMediaPlayer::Seek(long second)
{
	DWORD dwCap = 0;

	if(	this->mState!=PLAYING){
		return S_OK;
	}
	HRESULT hr = mpMediaSeeking->GetCapabilities(&dwCap);
	if ((AM_SEEKING_CanSeekForwards & dwCap) || (AM_SEEKING_CanSeekBackwards & dwCap))
	{
		__int64 total;
		__int64 currentPostion;

		hr = mpMediaSeeking->GetPositions(&currentPostion,&total);
		currentPostion = (__int64)second * ONE_SECOND;

		if(currentPostion <= 0) currentPostion = 0;
		hr = mpMediaSeeking->SetPositions(
			&currentPostion, AM_SEEKING_AbsolutePositioning | AM_SEEKING_SeekToKeyFrame, 
			NULL, AM_SEEKING_NoPositioning
			);
	}

	return S_OK;

}


HRESULT CChannelMediaPlayer::SetVolume(int percent)
{
	HRESULT hr=S_OK;

    if ((!mpGraphBuider) || (!mpBasicAudio))
        return S_OK;

	currentVolume = (percent >= 100) ? 100 : percent;
	currentVolume = (percent <= 0) ? 0 :percent;
	
	return mpBasicAudio->put_Volume(VOLUME_SILENCE + currentVolume * 100);
}

int CChannelMediaPlayer::GetTotalTime()
{
	HRESULT hr=S_OK;	
	__int64 total;
	__int64 currentPostion;
	hr = mpMediaSeeking->GetPositions(&currentPostion,&total);
	if(FAILED(hr)){
		return 0;
	}
	return (int)(total/(ONE_SECOND));

}

int CChannelMediaPlayer::NotifyOwnerMessage(HWND owner, DWORD message,DWORD wParam,DWORD lParam)
{
	HRESULT  hr = 0;
	
	if (mpVideoWindow){
		/*
		LONG lHeight, lWidth;
		RECT grc;
		JIF(this->mpBasicVideo->GetVideoSize(&lWidth, &lHeight));
		GetClientRect(owner, &grc);
		float scale = (grc.right - grc.left) / (float)lWidth;
		long videoHeight = long(lHeight * scale);
		long vOffset = (grc.bottom - grc.top) - videoHeight;
		JIF(mpVideoWindow->SetWindowPosition(grc.left,vOffset / 2, grc.right - grc.left, grc.bottom - vOffset));
		JIF(mpVideoWindow->SetWindowPosition(0, 0, grc.right, grc.bottom));
		JIF(mpVideoWindow->SetWindowForeground(-1));
		*/
	    mpVideoWindow->NotifyOwnerMessage((LONG_PTR) owner, message, wParam, lParam);

	}
	return 0;
}

BOOL CChannelMediaPlayer::IncreaseVolume(int percent)
{
	this->currentVolume+=percent;
	if(this->currentVolume > 100)  this->currentVolume=100;
	return this->SetVolume(this->currentVolume);
}

BOOL CChannelMediaPlayer::DecreaseVolume(int percent)
{
	this->currentVolume-=percent;
	if(this->currentVolume < 0)  this->currentVolume=0;
	return this->SetVolume(this->currentVolume);	
}

BOOL CChannelMediaPlayer::SetMute()
{
	return this->SetVolume(0);
}

int CChannelMediaPlayer::GetVolume()
{
	return this->currentVolume;
}

int CChannelMediaPlayer::GetPosition()
{
	HRESULT hr=S_OK;	
	__int64 total;
	__int64 currentPostion;
	int percent = 0;
	hr = mpMediaSeeking->GetPositions(&currentPostion,&total);
	if(FAILED(hr)){
		return 0;
	}
	double c=(double)currentPostion/(double)total;

	percent = (int)(c*100.0);
	return percent;
}

bool CChannelMediaPlayer::Forward(int seconds)
{
	//update current postion;
	HRESULT hr=S_OK;
	DWORD dwCap = 0;
	__int64 total;
	__int64 currentPostion;
	int percent = 0;
	hr = mpMediaSeeking->GetPositions(&currentPostion,&total);
	if(FAILED(hr)){
		return false;
	}

	hr = mpMediaSeeking->GetCapabilities(&dwCap);

	if ((AM_SEEKING_CanSeekForwards & dwCap) || (AM_SEEKING_CanSeekBackwards & dwCap))
	{
		__int64 total;
		__int64 currentPostion;

		hr = mpMediaSeeking->GetPositions(&currentPostion,&total);
		currentPostion += (__int64)seconds * ONE_SECOND;

		if(currentPostion <= 0) currentPostion = 0;
		hr = mpMediaSeeking->SetPositions(
			&currentPostion, AM_SEEKING_AbsolutePositioning | AM_SEEKING_SeekToKeyFrame, 
			NULL, AM_SEEKING_NoPositioning
			);
		return true;
	}else{
		return false;
	}

}

bool CChannelMediaPlayer::Backward(int seconds)
{
	HRESULT hr=S_OK;
	DWORD dwCap = 0;
	__int64 total;
	__int64 currentPostion;
	int percent = 0;
	hr = mpMediaSeeking->GetPositions(&currentPostion,&total);
	if(FAILED(hr)){
		return false;
	}

	hr = mpMediaSeeking->GetCapabilities(&dwCap);

	if ((AM_SEEKING_CanSeekForwards & dwCap) || (AM_SEEKING_CanSeekBackwards & dwCap))
	{
		__int64 total;
		__int64 currentPostion;

		hr = mpMediaSeeking->GetPositions(&currentPostion,&total);
		currentPostion -= (total/100)*percent;

		if(currentPostion <= 0) currentPostion = 0;
		hr = mpMediaSeeking->SetPositions(
			&currentPostion, AM_SEEKING_AbsolutePositioning | AM_SEEKING_SeekToKeyFrame, 
			NULL, AM_SEEKING_NoPositioning
			);
		return true;
	}else{
		return false;
	}
}

int CChannelMediaPlayer::ForwardPercent(int percent)
{
	//update current postion;
	HRESULT hr=S_OK;
	DWORD dwCap = 0;
	__int64 total;
	__int64 currentPostion;
	hr = mpMediaSeeking->GetPositions(&currentPostion,&total);
	if(FAILED(hr)){
		return false;
	}

	hr = mpMediaSeeking->GetCapabilities(&dwCap);

	if ((AM_SEEKING_CanSeekForwards & dwCap) || (AM_SEEKING_CanSeekBackwards & dwCap))
	{
		__int64 total;
		__int64 currentPostion;

		hr = mpMediaSeeking->GetPositions(&currentPostion,&total);
		currentPostion += (total/100)*percent;

		if(currentPostion <= 0) currentPostion = 0;
		hr = mpMediaSeeking->SetPositions(
			&currentPostion, AM_SEEKING_AbsolutePositioning | AM_SEEKING_SeekToKeyFrame, 
			NULL, AM_SEEKING_NoPositioning
			);
		return true;
	}else{
		return false;
	}
}

int CChannelMediaPlayer::BackwardPercent(int percent)
{
	HRESULT hr=S_OK;
	DWORD dwCap = 0;
	__int64 total;
	__int64 currentPostion;

	hr = mpMediaSeeking->GetPositions(&currentPostion,&total);
	if(FAILED(hr)){
		return false;
	}

	hr = mpMediaSeeking->GetCapabilities(&dwCap);

	if ((AM_SEEKING_CanSeekForwards & dwCap) || (AM_SEEKING_CanSeekBackwards & dwCap))
	{
		__int64 total;
		__int64 currentPostion;

		hr = mpMediaSeeking->GetPositions(&currentPostion,&total);
		currentPostion -= (total/100)*percent;

		if(currentPostion <= 0) currentPostion = 0;
		hr = mpMediaSeeking->SetPositions(
			&currentPostion, AM_SEEKING_AbsolutePositioning | AM_SEEKING_SeekToKeyFrame, 
			NULL, AM_SEEKING_NoPositioning
			);
		return true;
	}else{
		return false;
	}
}

void CChannelMediaPlayer::disableMouseCursor()
{
	//SetCursorPos(2000, 2000); 

}
