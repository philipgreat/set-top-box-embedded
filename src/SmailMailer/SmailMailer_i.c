/* this file contains the actual definitions of */
/* the IIDs and CLSIDs */

/* link this file in with the server and any clients */


/* File created by MIDL compiler version 5.01.0164 */
/* at Sat Dec 09 18:38:20 2006
 */
/* Compiler settings for F:\suddy\xpe_stb\src\SmailMailer\SmailMailer.idl:
    Oicf (OptLev=i2), W1, Zp8, env=Win32, ms_ext, c_ext
    error checks: allocation ref bounds_check enum stub_data 
*/
//@@MIDL_FILE_HEADING(  )
#ifdef __cplusplus
extern "C"{
#endif 


#ifndef __IID_DEFINED__
#define __IID_DEFINED__

typedef struct _IID
{
    unsigned long x;
    unsigned short s1;
    unsigned short s2;
    unsigned char  c[8];
} IID;

#endif // __IID_DEFINED__

#ifndef CLSID_DEFINED
#define CLSID_DEFINED
typedef IID CLSID;
#endif // CLSID_DEFINED

const IID IID_IMailerClient = {0x1EE564AA,0xA096,0x4CFE,{0x90,0x7C,0xB1,0x49,0xBA,0xB0,0xB5,0x00}};


const IID LIBID_SMAILMAILERLib = {0xEC2B89A5,0xED78,0x4288,{0xB8,0x26,0xAF,0xC0,0x64,0x4D,0x43,0x98}};


const CLSID CLSID_MailerClient = {0x8A53E3DC,0xE1BC,0x4E4D,{0xB5,0xAE,0x3B,0x14,0x0B,0x8F,0x75,0x5A}};


#ifdef __cplusplus
}
#endif

