#include "stdafx.h"
#include "CBTask.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//////////////////////////////////////////////////////////////////////////
// Task
CTask::CTask()
: m_pICallBack(NULL)
{
}

CTask::~CTask()
{
	m_pICallBack = NULL;
}

void CTask::SetCallBack(ITaskCB* pICallBack)
{
	CSingleLock l(&m_lockTask, TRUE);
	m_pICallBack = pICallBack;
}

BOOL CTask::Notify(WPARAM wParam, LPARAM lParam)
{
	CSingleLock l(&m_lockTask, TRUE);
	BOOL bNotiSuc(FALSE);
	if (m_pICallBack != NULL)
		bNotiSuc = m_pICallBack->OnTaskNotify(wParam, lParam);

	return bNotiSuc;
}
