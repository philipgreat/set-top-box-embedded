// ChannelMediaPlayer.h: interface for the CChannelMediaPlayer class.
//
//////////////////////////////////////////////////////////////////////
/*===========================================================*\
  文件: ChannelMediaPlayer.h	
  版权: 青牛(北京)技术有限公司
  日期: 2005-09-05
  描述: 对于播放器的一个封装的类，该类可以处理视频请求，进行WMV或者MPEG4
		进行解码。另外，根据不同的服务，为机顶盒设置不同的状态， 进一步分别控制
  参考: 
  作者: zhangxl@channel.com
  修订记录:	

\*===========================================================*/
#if !defined(AFX_CHANNELMEDIAPLAYER_H__2A798E33_BC15_470C_84D6_EC5DB59075BD__INCLUDED_)
#define AFX_CHANNELMEDIAPLAYER_H__2A798E33_BC15_470C_84D6_EC5DB59075BD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include <windows.h>
//#include <mmsystem.h>
#include <streams.h>
#include <commctrl.h>
#include <commdlg.h>

#pragma comment(lib,"ole32")
#pragma comment(lib,"strmiids")
#pragma comment(lib,"strmbase")
#pragma comment(lib,"uuid")
#pragma comment(lib,"Quartz")

#define WM_GRAPHNOTIFY  WM_USER+13
#define A2W(W,A)     MultiByteToWideChar(936,0,(A),strlen((A))+1,(W),strlen((A))+1)
class CChannelMediaPlayer  
{
	// the lifecyle of the class is
	// 
private:
	WCHAR *programURL;

	DWORD playContentType ;
private:
	IGraphBuilder	*mpGraphBuider ;
	IMediaControl	*mpMediaControl ;
	IMediaEventEx	*mpMediaEvent ;
	IVideoWindow	*mpVideoWindow ;
	IBasicAudio		*mpBasicAudio ;
	IBasicVideo		*mpBasicVideo ;
	IMediaSeeking	*mpMediaSeeking ;
	/****************该段代码为重新构造graph来构建的*******************/
	IBaseFilter		*mpFilterSrc ;
	IBaseFilter		*mpFilterDest ;
	IBaseFilter		*mpDescFilter ;

	IPin			*mpPinSrcOut ;	
	IPin			*mpPinDestIn ;
	IPin			*mpPinDescOut ;	
	IPin			*mpPinDescIn ;
	IBaseFilter		*pReader;
	IFileSourceFilter *pFS;
	int				currentVolume;
	/******************该段代码为重新构造graph来构建的[完]**************/

	HWND			mhMainWindow;
	HINSTANCE		hInstance;
	int				mState;
	long			evCode;
	//__int64			currentPostion;
public:
	void disableMouseCursor();
	int BackwardPercent(int percent);
	int ForwardPercent(int percent);
	bool Backward(int seconds);
	bool Forward(int seconds);
	int GetPosition();
	int GetVolume();
	BOOL SetMute();
	BOOL DecreaseVolume(int percent);
	BOOL IncreaseVolume(int percent);
	int NotifyOwnerMessage(HWND hWnd, DWORD message,DWORD wParam,DWORD lParam);
	int GetTotalTime();
	HRESULT SetVolume(int percent);
	HRESULT Seek(long postion);
	HRESULT WaitForCompletion();
	BOOL PreProcessURL(const WCHAR *url);
	HRESULT PreProcGraphEvent(long *eventCode);
	enum MediaPlayState { INIT=0, PLAYING,RELEASED,DESTROYED,STOPED,PAUSED };
	HRESULT Pause();
	LRESULT PutOwner(HWND owner);
	HRESULT Stop();
	HRESULT Release();
	LRESULT UnInit();
	HRESULT RenderFile(const WCHAR *url,HWND owner);
	HRESULT Init();
	int CreateMainWindow(HINSTANCE   hInstance);
	CChannelMediaPlayer();
	virtual ~CChannelMediaPlayer();

};


#endif // !defined(AFX_CHANNELMEDIAPLAYER_H__2A798E33_BC15_470C_84D6_EC5DB59075BD__INCLUDED_)
