#pragma once

//////////////////////////////////////////////////////////////////////////
class IP_PUBLIC_EXP CIPEvent
{
public:
	CIPEvent();
	~CIPEvent();

	// Cast to HANDLE
	operator HANDLE() const { return m_hEvent; };

	void Set();
	void Reset();
	BOOL Wait(DWORD dwTimeout = INFINITE);
	BOOL Check();

private:
	HANDLE	m_hEvent;
};