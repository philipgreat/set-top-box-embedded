// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__EFF8993A_D005_4D0B_B738_F268212531F9__INCLUDED_)
#define AFX_STDAFX_H__EFF8993A_D005_4D0B_B738_F268212531F9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define WIN32_LEAN_AND_MEAN		// Exclude rarely-used stuff from Windows headers
#pragma warning (disable:4146 4192 4786 4081)
#import   "MSO.dll"     rename_namespace("Office"),named_guids  
using   namespace   Office;   
#import "VBE6EXT.OLB" no_namespace,rename_namespace("VBE")
// TODO: reference additional headers your program requires here

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__EFF8993A_D005_4D0B_B738_F268212531F9__INCLUDED_)

