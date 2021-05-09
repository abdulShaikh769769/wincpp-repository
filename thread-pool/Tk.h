// Tk.h: interface for the CTk class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TK_H__91FC38FF_1109_4389_9FD6_2B3673DC7F16__INCLUDED_)
#define AFX_TK_H__91FC38FF_1109_4389_9FD6_2B3673DC7F16__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CTk  
{
public:
	int m_iAllocated ;
	int m_Index ;
	static int s_Index ;
	CTk();
	void Run ( ) ;
	virtual ~CTk();

};

#endif // !defined(AFX_TK_H__91FC38FF_1109_4389_9FD6_2B3673DC7F16__INCLUDED_)
