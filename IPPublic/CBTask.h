#pragma once

#include "afxmt.h"

//////////////////////////////////////////////////////////////////////////
// Task callback
class IP_PUBLIC_EXP ITaskCB
{
public:
	virtual BOOL OnTaskNotify(WPARAM wParam = NULL, LPARAM lParam = NULL) = 0;
};

// Task
class IP_PUBLIC_EXP ITask
{
public:
	virtual void SetCallBack(ITaskCB* pICallBack) = 0;
};

//////////////////////////////////////////////////////////////////////////
// CTask
class IP_PUBLIC_EXP CTask : public ITask
{
public:
	CTask();
	virtual ~CTask();

public:
	virtual void SetCallBack(ITaskCB* pICallBack);

public:
	BOOL Notify(WPARAM wParam = NULL, LPARAM lParam = NULL);

private:
	ITaskCB*			m_pICallBack;
	CCriticalSection	m_lockTask;
};
