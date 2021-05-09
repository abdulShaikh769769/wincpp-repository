// Tp.cpp: implementation of the CTp class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ThreadpoolDemo.h"
#include "Tp.h"


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CCriticalSection CTp::m_tpCS ;

CTp::CTp( int nMin , int nMax  )
{
	/*
	*
	*Validating thread nMin and nMax.
	*/
	if ( nMin <= 0 || nMax <= 0 || nMin > nMax || nMax > 1024 )
		return ;
	/*
	*
	*Initializing Threadpool's member
	*/
	m_ntpMin = nMin ;
	m_ntpMax = nMax ;
	m_ntpTotalActive = 0 ;
	m_ntpTotalPassive = 0 ;

	/*
	*
	*for-loop for creating nMin threads initially, 
	*in suspended mode.
	*/
	CTh * pThread ;
	for ( int i = 0 ; i < nMin ; i++ )
	{
		/*
		*
		*Creating CTh object.
		*/
		pThread = NULL ;
		pThread = new CTh ( ) ;
		/*
		*
		*Adding this CTh object to the threadpool's m_ThreadList
		*/
		if ( pThread )
		{
			AddThreadToThreadList ( pThread ) ;
			m_ntpTotalPassive++ ;
		}
	}
}

CTp::~CTp(  )
{
	/*
	*
	*Deleting Thread(CTh) objects.
	*/
	list < CTh * >::iterator iterTh ;
	for ( iterTh = m_ThreadList . begin ( ) ; iterTh != m_ThreadList . end ( ) ; iterTh++ )
	{
		delete ( * iterTh ) ;
	}

	/*
	*
	*Deleting Task(CTk) objects.
	*/
	list < CTk * >::iterator iterTk ;
	for ( iterTk = m_TaskList . begin ( ) ; iterTk != m_TaskList . end ( ) ; iterTk++ )
	{
		delete ( * iterTk ) ;
	}
}

bool CTp::CreatePool ( int nMin , int nMax )
{
	/*
	*
	*Validating thread nMin and nMax.
	*/
	if ( nMin <= 0 || nMax <= 0 || nMin > nMax || nMax > 1024 )
		return false ;
	/*
	*
	*for-loop for creating nMin threads initially, 
	*in suspended mode.
	*/
	CTh * pThread ;
	for ( int i = 0 ; i < nMin ; i++ )
	{
		/*
		*
		*Creating CTh object.
		*/
		pThread = NULL ;
		pThread = new CTh ( ) ;
		/*
		*
		*Adding this CTh object to the threadpool's m_ThreadList
		*/
		if ( pThread )
			AddThreadToThreadList ( pThread ) ;
	}
	return true ;
}
/*
*
*Adds thread to thread list.
*/
void CTp::AddThreadToThreadList ( CTh * pTh )
{
	m_ThreadList . push_back ( pTh ) ;
}
/*
*
*Add task to task list.
*/
void CTp::AddTaskToTaskList ( CTk * pTask )
{
	m_TaskList . push_back ( pTask ) ;
}
/*
*
*Returns reference of CTh object from thread list container
*for executing the given task.
*/
CTh * CTp::GetThread ( )
{
	/**
	*
	*Initializing locking object.
	*/
	CSingleLock sLock ( &m_tpCS ) ;
	/*
	*
	*Acquiring lock.
	*/
	sLock . Lock ( ) ;
	/**
	*
	*Checking, if lock is successful.
	*/
	if ( sLock . IsLocked ( ) )
	{
		/*
		*
		*Iterating Thread list for free thread,
		*if list has free thread then returning it for task execution.
		*/
		list < CTh * >::iterator iter ;
		for ( iter = m_ThreadList . begin ( ) ; iter != m_ThreadList . end ( ) ; iter++ )
		{
			if ( ( * iter ) -> m_iCurrState == PASSIVE )
			{
				/*
				*
				*Unlocking lock.
				*/
				sLock . Unlock ( ) ;
				/*
				*
				*Returning free thread for task execution.
				*/
				return * iter ;
			}
		}
		/*
		*
		*If thread list does not have free thread and 
		*total allowed thread count does not match to m_ntpMax then
		*we are creating new thread, pushing it to the total thread
		*list and returning it for executing the task.
		*/
		if ( m_ThreadList . size ( ) < m_ntpMax )
		{
			CTh * pThread =	NULL ;
			pThread = new CTh ( ) ;
			if ( pThread )
			{
				/*
				*
				*This is new thread so need to add it in Threadpool's
				*thread list.
				*/
				AddThreadToThreadList ( pThread ) ;
				/*
				*
				*Unlocking lock.
				*/
				sLock . Unlock ( ) ;
				/*
				*
				*Returning free thread for task execution.
				*/
				return pThread ;
			}
		}
	}
	/*
	*
	*Unlocking lock.
	*/
	sLock . Unlock ( ) ;
	/*
	*
	*We have reached at maximum threads that 
	*we allowed in threadpool and 
	*we don't have free thread for service, so returning NULL.
	*/
	return NULL ;
}
/*
*
*Returns the task from task list.
*/
CTk * CTp::GetTask ( )
{
	/**
	*
	*Initializing locking object.
	*/
	CSingleLock sLock ( &m_tpCS ) ;
	/*
	*
	*Acquiring lock.
	*/
	sLock . Lock ( ) ;
	/*
	*
	*Checking for the pending task to be allocated.
	*/
	if ( 0 == m_TaskList . size ( ) )
	{
		/*
		*
		*Unlocking lock.
		*/
		sLock . Unlock ( ) ;
		/*
		*
		*We have no pending task.
		*/
		return NULL ;
	}
	/*
	*
	*Iterating m_TaskList for pending task.
	*/
	list < CTk * >::iterator iter ;
	for ( iter = m_TaskList . begin ( ) ; iter != m_TaskList . end ( ) ; iter++ )
	{
		if ( ! ( * iter ) -> m_iAllocated ) 
		{
			( * iter ) -> m_iAllocated = 1 ;
			/*
			*
			*Unlocking lock.
			*/
			sLock . Unlock ( ) ;
			/*
			*
			*Returning task object.
			*/
			return ( *iter ) ;
		}
	}
	/*
	*
	*Unlocking lock.
	*/
	sLock . Unlock ( ) ;
	/*
	*
	*We have no pending task.
	*/
	return NULL ;
}
