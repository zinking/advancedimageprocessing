#pragma once
#include "barchart.h"


// CPicView ��ͼ
class CvvImage;
class Histogram;

class CPicView : public CView
{
	DECLARE_DYNCREATE(CPicView)

protected:
	CPicView();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~CPicView();

public:
	virtual void OnDraw(CDC* pDC);      // ��д�Ի��Ƹ���ͼ
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	DECLARE_MESSAGE_MAP()
public:
//	afx_msg void OnFileOpen();
public:
	// �ļ�·��
	CString strPicPath;
public:
	// ��ͼ�ؼ�
	CBarChart m_chart;
public:
	// ���BARCHART�Ļ���
	bool IUpdateBar(void);
public:
	// ��ʾָ����ͼ��
	bool display(  CvvImage* pImage );
public:
	virtual void OnInitialUpdate();
	// ���ض���ͼ������ͼ�������ػ�
	CvvImage* pImage;
	Histogram* pHist;
	afx_msg void OnPaint();
};


