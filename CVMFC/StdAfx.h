// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__1836CF0C_3704_4215_8745_F068486288D6__INCLUDED_)
#define AFX_STDAFX_H__1836CF0C_3704_4215_8745_F068486288D6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers
#include "targetver.h"

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
#include <afxdisp.h>        // MFC Automation classes
//#include <afxdtctl.h>		// MFC support for Internet Explorer 4 Common Controls
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.  


#include "CVMFC.h"                          //  窗口管理

#include <opencv/cv.h>                             //  OpenCV 文件头
#include <opencv/highgui.h>
 
#include "CameraDS.h"                       //  DirectShow(基于OpenCV)
#include "CVDSCap.h"                        //  视频采集接口

#include "Processing.h"                     //  附加辅助函数

#endif // !defined(AFX_STDAFX_H__1836CF0C_3704_4215_8745_F068486288D6__INCLUDED_)
