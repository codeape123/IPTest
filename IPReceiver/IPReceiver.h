
// IPReceiver.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CIPReceiverApp: 
// �йش����ʵ�֣������ IPReceiver.cpp
//

class CIPReceiverApp : public CWinApp
{
public:
	CIPReceiverApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CIPReceiverApp theApp;