/*===========================================================*\
  �ļ�: cert_client.h	
  ��Ȩ: ��ţ(����)�������޹�˾
  ����: 2006-05-09
  ����: ����ʵ�ִ���C�Ĵ���Ľ���, �ṩһ����װ����UDP�ͻ���
  �ο�: 
  ����: zhangxl@channel.com
  �޶���¼:	

\*===========================================================*/

#ifndef CHANNEL_LINUX_HEADER
#define CHANNEL_LINUX_HEADER
#include <stdlib.h>
#include <stdio.h>

#ifdef __cplusplus
extern "C"{
#endif

#ifdef _WIN32
#define _WINDOWS_PLATFORM
#endif
#ifdef _WIN32_WINNT
#ifndef _WINDOWS_PLATFORM
#define _WINDOWS_PLATFORM
#endif
#endif


/*========================================================================*/
#ifndef _WIN32
typedef unsigned int DWORD;
typedef unsigned char BYTE;
typedef unsigned int BOOL;
#define TRUE  (1)
#define FALSE (0)
#else
#include <windows.h>
#endif

/*========================================================================*/

#ifdef __cplusplus
}
#endif
#endif
