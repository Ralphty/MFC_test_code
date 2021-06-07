// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__4C0F3D0E_292A_4E0B_BF1F_C02EE323570C__INCLUDED_)
#define AFX_STDAFX_H__4C0F3D0E_292A_4E0B_BF1F_C02EE323570C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
#include <afxdisp.h>        // MFC Automation classes
#include <afxdtctl.h>		// MFC support for Internet Explorer 4 Common Controls
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT

//#pragma comment(lib,"SkinPPWTL.lib")

// 引入常用帮助类
#define MAXPATHNUM 100
#define MAXFILENUMPERPATH 2000

// 全局变量定义
extern BOOL g_bSysSetChange;

extern int g_nChlNum;
extern int g_nPreChlNum;

extern int g_nProType;
extern int g_nPreProType;

extern int g_nZeroPtVal;
extern UINT g_unSendTimout;
extern UINT g_unSendTimes;
extern BOOL g_bAutoAchv_Filename;
extern int  g_nGainFactorIndex;

extern int **g_ppnDataBuf;
extern int g_nDataBufSize;
extern int **g_ppnPreDataBuf;
extern int g_nPreDataBufSize;

extern BYTE g_byComRecvBuf[4];
extern int g_nComRecvBufSize;
extern BYTE g_2byComRecvBuf[100];
extern int g_2nComRecvBufSize;

extern CString g_aaPathName_List[MAXPATHNUM][MAXFILENUMPERPATH];
extern int g_aFileNumber[MAXPATHNUM+1];
extern int g_nPathNumber;
extern int g_nPathNumber_CurIndex;
extern int g_nFileNumber_CurIndex;
//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__4C0F3D0E_292A_4E0B_BF1F_C02EE323570C__INCLUDED_)
