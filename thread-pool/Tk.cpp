// Tk.cpp: implementation of the CTk class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ThreadpoolDemo.h"
#include "Tk.h"
#include "ThreadpoolDemoDlg.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

extern CThreadpoolDemoApp theApp;
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
int CTk::s_Index ;

CTk::CTk()
{
	s_Index++ ;
	m_Index = s_Index ;
	m_iAllocated = 0 ;

}

CTk::~CTk()
{
	
}
void CTk::Run ( )
{
	CString strMsg ;

	strMsg . Format ( "Task[%d]Thread ID[%d] Executing..." , m_Index , GetCurrentThreadId ( ) ) ;

	if ( m_Index == 0 )
	{
		theApp.ptr->m_list.DeleteString ( m_Index ) ;
		theApp.ptr->m_list.InsertString ( m_Index , strMsg ) ;
	}
	else
	{
		theApp.ptr->m_list.DeleteString ( m_Index-1 ) ;
		theApp.ptr->m_list.InsertString ( m_Index-1 , strMsg ) ;
	}

	if ( m_Index % 2 == 0 )
		Sleep (7000 ) ;
	else
		Sleep ( 3000 ) ;

	
	strMsg . Format ( "Task[%d] Thread ID[%d] Finished." ,m_Index ,GetCurrentThreadId ( ) ) ;

	if ( m_Index == 0 )
	{
		theApp.ptr->m_list.DeleteString ( m_Index ) ;
		theApp.ptr->m_list.InsertString ( m_Index , strMsg ) ;
	}
	else
	{
		theApp.ptr->m_list.DeleteString ( m_Index -1) ;
		theApp.ptr->m_list.InsertString ( m_Index-1 , strMsg ) ;
	}
}