
// TestCtp01.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CTestCtp01App:
// �йش����ʵ�֣������ TestCtp01.cpp
//

class CTestCtp01App : public CWinApp
{
public:
	CTestCtp01App();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CTestCtp01App theApp;