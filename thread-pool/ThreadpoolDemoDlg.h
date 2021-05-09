// ThreadpoolDemoDlg.h : header file
//

#if !defined(AFX_THREADPOOLDEMODLG_H__7EE80955_AF6D_4B2C_A458_630FA7B239F7__INCLUDED_)
#define AFX_THREADPOOLDEMODLG_H__7EE80955_AF6D_4B2C_A458_630FA7B239F7__INCLUDED_

#include <afxmt.h>

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CThreadpoolDemoDlg dialog

class CThreadpoolDemoDlg : public CDialog
{
// Construction
public:
	CTp* m_pThreadPool;
	//CThreadpoolDemoApp * pThreadApp ;
	static CCriticalSection m_AppCS ;
	CThreadpoolDemoDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CThreadpoolDemoDlg)
	enum { IDD = IDD_THREADPOOLDEMO_DIALOG };
	CButton	m_Clear;
	CListBox	m_list;
	CButton	m_AssignTask;
	CButton	m_createpool;
	int		m_nMin;
	int		m_nMax;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CThreadpoolDemoDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CThreadpoolDemoDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnCreate();
	afx_msg void OnAssigntask();
	afx_msg void OnClear();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_THREADPOOLDEMODLG_H__7EE80955_AF6D_4B2C_A458_630FA7B239F7__INCLUDED_)
