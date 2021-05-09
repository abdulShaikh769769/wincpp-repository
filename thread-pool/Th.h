// Th.h: interface for the CTh class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TH_H__E1CA9510_219A_499C_9139_6091B4D9907A__INCLUDED_)
#define AFX_TH_H__E1CA9510_219A_499C_9139_6091B4D9907A__INCLUDED_

#include <afxmt.h>
#include "tp.h"
#include "tk.h"


#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CTp ;

class CTh  
{
private:
	/*
	*Thread state enum.
	*/
	enum
	{
		PASSIVE ,
		ACTIVE ,
		SAYSTOP
	} ;
	/*
	*Pointer to the window's thread 
	*object.
	*/
	CWinThread * m_pThread ;
	/*
	*
	*Indicates threadpool of the thread.
	*/
	CTp * m_pool ;
	/*
	*
	*indicates the task executed by thread.
	*/
	CTk * m_pTask ;
	/*
	*Critcal section to synchronize thread 
	*member's modification. 
	*/
	static CCriticalSection m_thCS ;

public:
	/*
	*Indicates thread's current state.
	*/
	int m_iCurrState ;
	/*
	*constructor
	*/
	CTh ( ) ;
	/*
	*Destructor
	*/
	virtual ~CTh();
	/*
	*This method resumes thread execution.
	*/
	void Resume ( ) ;
	/*
	*Thie method suspends thread execution.
	*/
	void Suspend ( ) ;
	/*
	*Returns threadpool object.
	*/
	CTp * GetThreadPool ( ) ;
	/*
	*This method sets given threadpool.
	*/
	void SetThreadPool ( CTp * pPool ) ;
	/*
	*
	*This method sets task to thread.
	*/
	void SetTask ( CTk * pTask ) ;
	/*
	*This is thread function.
	*/
	static UINT ThreadFunction ( LPVOID pParam ) ;

};

#endif // !defined(AFX_TH_H__E1CA9510_219A_499C_9139_6091B4D9907A__INCLUDED_)
