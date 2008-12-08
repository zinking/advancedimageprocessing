// DIPView.cpp : CDIPView ���ʵ��
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

// CDIPView ����/����

CDIPView::CDIPView()
{
	// TODO: �ڴ˴���ӹ������

}

CDIPView::~CDIPView()
{
}

BOOL CDIPView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// CDIPView ����

void CDIPView::OnDraw(CDC* /*pDC*/)
{
	CDIPDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���
}


// CDIPView ���

#ifdef _DEBUG
void CDIPView::AssertValid() const
{
	CView::AssertValid();
}

void CDIPView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CDIPDoc* CDIPView::GetDocument() const // �ǵ��԰汾��������
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
