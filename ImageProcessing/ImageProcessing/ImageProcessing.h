// ImageProcessing.h : ImageProcessing Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"       // ������


// CDIPApp:
// �йش����ʵ�֣������ ImageProcessing.cpp
//

class CDIPApp : public CWinApp
{
public:
	CDIPApp();


// ��д
public:
	virtual BOOL InitInstance();

// ʵ��
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CDIPApp theApp;