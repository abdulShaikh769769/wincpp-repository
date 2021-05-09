// ThreadpoolDemoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ThreadpoolDemo.h"
#include "ThreadpoolDemoDlg.h"

#include "Tk.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern CThreadpoolDemoApp theApp;
/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About
CCriticalSection CThreadpoolDemoDlg::m_AppCS;
class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CThreadpoolDemoDlg dialog

CThreadpoolDemoDlg::CThreadpoolDemoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CThreadpoolDemoDlg::IDD, pParent)
{
	theApp.ptr=this;
	//{{AFX_DATA_INIT(CThreadpoolDemoDlg)
	m_nMin = 0;
	m_nMax = 0;
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	
}

void CThreadpoolDemoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CThreadpoolDemoDlg)
	DDX_Control(pDX, IDC_CLEAR, m_Clear);
	DDX_Control(pDX, IDC_LIST, m_list);
	DDX_Control(pDX, IDC_ASSIGNTASK, m_AssignTask);
	DDX_Control(pDX, IDC_CREATE, m_createpool);
	DDX_Text(pDX, IDC_MIN, m_nMin);
	DDV_MinMaxInt(pDX, m_nMin, 1, 1024);
	DDX_Text(pDX, IDC_MAX, m_nMax);
	DDV_MinMaxInt(pDX, m_nMax, 1, 1024);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CThreadpoolDemoDlg, CDialog)
	//{{AFX_MSG_MAP(CThreadpoolDemoDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_CREATE, OnCreate)
	ON_BN_CLICKED(IDC_ASSIGNTASK, OnAssigntask)
	ON_BN_CLICKED(IDC_CLEAR, OnClear)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CThreadpoolDemoDlg message handlers

BOOL CThreadpoolDemoDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	m_nMin = 1 ;
	m_nMax = 3 ;

	UpdateData ( FALSE ) ;

	m_AssignTask.EnableWindow ( 0 ) ;
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CThreadpoolDemoDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CThreadpoolDemoDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CThreadpoolDemoDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}
UINT ThreadProc ( LPVOID lpParam )
{
	CThreadpoolDemoDlg * pDlg = ( CThreadpoolDemoDlg * ) lpParam ;

	HANDLE hEvent ;
	hEvent = CreateEvent ( NULL , TRUE , FALSE , "eve" ) ;
	while ( 1 )
	{
		
		WaitForSingleObject ( hEvent , INFINITE ) ;
		pDlg->m_list.InsertString ( -1 , "finished" ) ;
		ResetEvent ( hEvent ) ;

	}
	return 0 ;
}
void CThreadpoolDemoDlg::OnCreate() 
{
	UpdateData ( TRUE ) ;
//	pThreadApp = ( CThreadpoolDemoApp * ) AfxGetApp ( ) ;
	m_pThreadPool = new CTp ( m_nMin , m_nMax ) ;

	m_createpool.EnableWindow ( 0 ) ;

	m_AssignTask.EnableWindow (1 ) ;


//	AfxBeginThread ( ThreadProc , this ) ;


}

void CThreadpoolDemoDlg::OnAssigntask() 
{
	CSingleLock sLock ( &m_AppCS ) ;
	sLock.Lock ( ) ;
	m_AssignTask.EnableWindow ( 0 ) ;
	
	CTk * pTask	= new CTk ( ) ;

	CString strMsg;
	strMsg.Format ( "Task[%d] is Pending..." , pTask -> m_Index ) ;
	if ( pTask->m_Index == 0 )
	{
		m_list.InsertString ( pTask->m_Index , strMsg ) ;
	}
	else
		m_list.InsertString ( pTask->m_Index-1 , strMsg ) ;


	m_pThreadPool -> AddTaskToTaskList ( pTask ) ;

	CTh * pThread = m_pThreadPool -> GetThread ( ) ;

	if ( pThread )
	{
		pThread -> SetThreadPool ( m_pThreadPool ) ;
		Sleep ( 1 ) ;
		pThread -> Resume ( ) ;
	}

	sLock.Unlock ( ) ;
	m_AssignTask.EnableWindow ( 1 ) ;
}

void CThreadpoolDemoDlg::OnClear() 
{
	//m_list.ResetContent();	
}
