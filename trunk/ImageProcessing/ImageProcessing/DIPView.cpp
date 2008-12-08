// DIPView.cpp : CDIPView 类的实现
//

#include "stdafx.h"
#include "ImageProcessing.h"

#include "DIPDoc.h"
#include "DIPView.h"
#include "PicView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CDIPView

IMPLEMENT_DYNCREATE(CDIPView, CView)

BEGIN_MESSAGE_MAP(CDIPView, CView)
	ON_WM_CREATE()
END_MESSAGE_MAP()

// CDIPView 构造/析构

CDIPView::CDIPView()
{
	// TODO: 在此处添加构造代码

}

CDIPView::~CDIPView()
{
}

BOOL CDIPView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CDIPView 绘制

void CDIPView::OnDraw(CDC* /*pDC*/)
{
	CDIPDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
}


// CDIPView 诊断

#ifdef _DEBUG
void CDIPView::AssertValid() const
{
	CView::AssertValid();
}

void CDIPView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CDIPDoc* CDIPView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CDIPDoc)));
	return (CDIPDoc*)m_pDocument;
}
#endif //_DEBUG





int CDIPView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;



	return 0;
}
