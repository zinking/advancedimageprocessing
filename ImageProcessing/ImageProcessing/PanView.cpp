// PanView.cpp : 实现文件
//

#include "stdafx.h"
#include "ImageProcessing.h"
#include "PanView.h"


// CPanView

IMPLEMENT_DYNCREATE(CPanView, CFormView)

CPanView::CPanView()
	: CFormView(CPanView::IDD)
{

}

CPanView::~CPanView()
{
}

void CPanView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CPanView, CFormView)
END_MESSAGE_MAP()


// CPanView 诊断

#ifdef _DEBUG
void CPanView::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CPanView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CPanView 消息处理程序
