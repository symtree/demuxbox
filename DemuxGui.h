// DemuxGui.h : main header file for the DEMUXGUI application
//

#if !defined(AFX_DEMUXGUI_H__063A734E_19AF_467B_9AA8_A8789BFA5AC5__INCLUDED_)
#define AFX_DEMUXGUI_H__063A734E_19AF_467B_9AA8_A8789BFA5AC5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CDemuxGuiApp:
// See DemuxGui.cpp for the implementation of this class
//

class CDemuxGuiApp : public CWinApp
{
public:
	CDemuxGuiApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDemuxGuiApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CDemuxGuiApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DEMUXGUI_H__063A734E_19AF_467B_9AA8_A8789BFA5AC5__INCLUDED_)
