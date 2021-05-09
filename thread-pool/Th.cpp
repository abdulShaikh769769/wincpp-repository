// Th.cpp: implementation of the CTh class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ThreadpoolDemo.h"
#include "Th.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CCriticalSection CTh::m_thCS ;

CTh::CTh()
{
	m_pThread = AfxBeginThread ( ThreadFunction , 
								 this , 
								 THREAD_PRIORITY_NORMAL , 
								 0 , 
								 CREATE_SUSPENDED , 
								 NULL ) ;

	m_iCurrState = PASSIVE ;
	m_pool = NULL ;
	m_pTask = NULL ;
}

CTh::~CTh()
{
	TerminateThread (m_pThread , 0 ) ;
	CloseHandle ( m_pThread ) ;
}
/*
*This method resumes thread's execution.
*/
void CTh::Resume ( )
{
	m_pThread -> ResumeThread ( ) ;
	/*
	*
	*Setting threads state to ACTIVE
	*/
	m_iCurrState = ACTIVE ;	
}
/*
*Thie method suspends thread's execution.
*/
void CTh::Suspend ( )
{
	/*
	*
	*Setting threads state to PASSIVE
	*/
	m_iCurrState = PASSIVE ;
	m_pThread -> SuspendThread ( ) ;
}
/*
*This method sets given threadpool.
*/
CTp * CTh::GetThreadPool ( )
{
	return m_pool ; 
}
/*
*This method sets given threadpool.
*/
void CTh::SetThreadPool ( CTp * pPool )
{
	if ( !m_pool )
		m_pool = pPool ;
}
/*
*
*Sets the given task to thread.
*/
void CTh::SetTask ( CTk * pTask )
{
	m_pTask = pTask ;
}
UINT CTh::ThreadFunction ( LPVOID pParam )
{
	/*
	*
	*Initializing lock object.
	*/
	CSingleLock sLock ( &m_thCS ) ;
	/*
	*Type casting to CTh type.
	*/
	CTh * pTh = ( CTh * ) pParam ;
	/*
	*Declaration of the pointer to the CTk object,
	*We are retrieving the task from pending task list,
	*and executing it.
	*/
	CTk * pTask ;
	/*
	*
	*Pointer to the threadpool object.
	*/
	CTp * pPool ;
	/*
	*While-loop for executing task on 
	*demand or whenever new task is been allocated.
	*/Sleep ( 1 ) ;
	while ( SAYSTOP )
	{
		/*
		*Getting threadpool.
		*/
		pPool = NULL ;
		pPool = pTh -> GetThreadPool ( ) ;
		do
		{
			/*
			*
			*We have to grab the task from task list,
			*and then execute it.
			*/
			pTask = NULL ;
			pTask = pPool -> GetTask ( ) ;
			if ( pTask )
			{
				/*
				*This is the target method executed by 
				*thread when it wakes up.
				*/
				pTask -> Run ( ) ;

				/*
				*
				*Deleting CTk (Task) object, after its execution.
				*/
				delete pTask ;
			}
			
		} while ( pTask != NULL ) ;
		/*
		*Suspending thread, as it has finished task.
		*/
		pTh -> Suspend ( ) ;
	}

	return 0 ;
}
