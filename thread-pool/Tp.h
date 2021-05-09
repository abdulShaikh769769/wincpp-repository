// Tp.h: interface for the CTp class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TP_H__C97C4C79_FF3A_497B_8ABD_7A67819118A3__INCLUDED_)
#define AFX_TP_H__C97C4C79_FF3A_497B_8ABD_7A67819118A3__INCLUDED_

#include <list>
#include <afxmt.h>
#include "th.h"
#include "tk.h"

using namespace std ;

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000



class CTh;

class CTp  
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
	*
	*Threadpool minimum thread count.
	*/
	int m_ntpMin ;
	/*
	*
	*Threadpool maximum thread count.
	*/
	int m_ntpMax ;
	/*
	*
	*Threadpool active thread count.
	*/
	int m_ntpTotalActive ;
	/*
	*
	*Threadpool passive thread count.
	*/
	int m_ntpTotalPassive ;
	/*
	*
	*Threadpool thread list, this is container
	*for storing CTh objects.
	*/	
	list < CTh * > m_ThreadList ;
	/*
	*
	*Task list container.
	*/
	list < CTk * > m_TaskList ;
	/*
	*
	*Critical section for making this class thread-safe.
	*/
	static CCriticalSection m_tpCS ;

public:
	/*
	*
	*Constructor
	*/
	CTp ( int nMin , int nMax ) ;
	/*
	*
	*Destructor
	*/
	virtual ~CTp();
	/*
	*
	*Creates threadpool of specified number of thread.
	*/
	bool CreatePool ( int nMin , int nMax ) ;
	/*
	*
	*Adds thread to thread list.
	*/
	void AddThreadToThreadList ( CTh * pTh ) ;
	/*
	*
	*Add task to task list.
	*/
	void AddTaskToTaskList ( CTk * pTask ) ;
	/*
	*
	*Returns reference of CTh object from thread list container
	*for executing the given task.
	*/
	CTh * GetThread ( ) ;
	/*
	*
	*Returns the task from task list.
	*/
	CTk * GetTask ( ) ;
};

#endif // !defined(AFX_TP_H__C97C4C79_FF3A_497B_8ABD_7A67819118A3__INCLUDED_)
