// ThreadpoolDemo.h : main header file for the THREADPOOLDEMO application
//

#if !defined(AFX_THREADPOOLDEMO_H__A480E2C8_6C26_4CBB_8D3C_0FCAEE281FF8__INCLUDED_)
#define AFX_THREADPOOLDEMO_H__A480E2C8_6C26_4CBB_8D3C_0FCAEE281FF8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols
#include "Tp.h"
#include "ThreadpoolDemoDlg.h"
/////////////////////////////////////////////////////////////////////////////
// CThreadpoolDemoApp:
// See ThreadpoolDemo.cpp for the implementation of this class
//

class CThreadpoolDemoApp : public CWinApp
{
public:
	static CThreadpoolDemoDlg * ptr ;
	CThreadpoolDemoApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CThreadpoolDemoApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CThreadpoolDemoApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_THREADPOOLDEMO_H__A480E2C8_6C26_4CBB_8D3C_0FCAEE281FF8__INCLUDED_)
