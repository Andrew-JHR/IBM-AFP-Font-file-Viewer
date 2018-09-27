// DisplayAFP.h : main header file for the DISPLAYAFP application
//

#if !defined(AFX_DISPLAYAFP_H__C0B85B38_1275_11D7_88F9_00055D51214C__INCLUDED_)
#define AFX_DISPLAYAFP_H__C0B85B38_1275_11D7_88F9_00055D51214C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CDisplayAFPApp:
// See DisplayAFP.cpp for the implementation of this class
//

class CDisplayAFPApp : public CWinApp
{
public:
	CDisplayAFPApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDisplayAFPApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CDisplayAFPApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DISPLAYAFP_H__C0B85B38_1275_11D7_88F9_00055D51214C__INCLUDED_)
