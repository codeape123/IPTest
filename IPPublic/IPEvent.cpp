
#include "stdafx.h"
#include "IPEvent.h"
#include "PublicDefine.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////////
CIPEvent::CIPEvent()
:m_hEvent(NULL)
{
	m_hEvent = ::CreateEvent(NULL, TRUE, FALSE, NULL);
}

CIPEvent::~CIPEvent()
{
	SAFE_CLOSE_HANDLE(m_hEvent);
}

void CIPEvent::Set()
{
	::SetEvent(m_hEvent);
}

void CIPEvent::Reset()
{
	::ResetEvent(m_hEvent);
}

BOOL CIPEvent::Wait(DWORD dwTimeout /*= INFINITE*/)
{
	return (WAIT_OBJECT_0 == ::WaitForSingleObject(m_hEvent, dwTimeout));
}

BOOL CIPEvent::Check()
{
	return Wait(0);
}
