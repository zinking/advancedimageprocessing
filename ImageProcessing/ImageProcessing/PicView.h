#pragma once
#include "barchart.h"


// CPicView 视图
class CvvImage;
class Histogram;

class CPicView : public CView
{
	DECLARE_DYNCREATE(CPicView)

protected:
	CPicView();           // 动态创建所使用的受保护的构造函数
	virtual ~CPicView();

public:
	virtual void OnDraw(CDC* pDC);      // 重写以绘制该视图
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
	// 文件路径
	CString strPicPath;
public:
	// 绘图控件
	CBarChart m_chart;
public:
	// 完成BARCHART的绘制
	bool IUpdateBar(void);
public:
	// 显示指定的图像
	bool display(  CvvImage* pImage );
public:
	virtual void OnInitialUpdate();
	// 与特定视图关联的图像，用于重绘
	CvvImage* pImage;
	Histogram* pHist;
	afx_msg void OnPaint();
};


