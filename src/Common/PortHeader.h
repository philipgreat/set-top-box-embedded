/*===========================================================*\
  文件: cert_client.h	
  版权: 青牛(北京)技术有限公司
  日期: 2006-05-09
  描述: 用于实现纯的C的代码的解扰, 提供一个封装过的UDP客户端
  参考: 
  作者: zhangxl@channel.com
  修订记录:	

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
