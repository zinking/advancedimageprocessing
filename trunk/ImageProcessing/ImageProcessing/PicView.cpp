// PicView.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ImageProcessing.h"
#include "PicView.h"
#include "DIPDoc.h"
#include "MainFrm.h"


// CPicView

IMPLEMENT_DYNCREATE(CPicView, CView)

CPicView::CPicView()
: strPicPath(_T(""))
, pImage(NULL)
{


}

CPicView::~CPicView()
{
}

BEGIN_MESSAGE_MAP(CPicView, CView)
//	ON_COMMAND(ID_FILE_OPEN, &CPicView::OnFileOpen)
ON_WM_PAINT()
END_MESSAGE_MAP()


// CPicView ��ͼ

void CPicView::OnDraw(CDC* pDC)
{
	//CDIPDoc* pDoc = GetDocument();
	// TODO: �ڴ���ӻ��ƴ���

}


// CPicView ���

#ifdef _DEBUG
void CPicView::AssertValid() const
{
	CView::AssertValid();
}

#ifndef _WIN32_WCE
void CPicView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif
#endif //_DEBUG


bool CPicView::IUpdateBar(void)
{
	//��ʼ��Bar��������һ�������
	static bool created = false;
	CRect rect;
	GetClientRect(&rect);
	if ( !created )
	{
		if (!m_chart.Create(	rect, this, 0 ) )      
		{
			return false;
		}
	}

	//m_chart.SetTitle("A test chart, displaying some dummy data...");
	m_chart.SetBKColor(RGB(255, 255, 240));
	m_chart.ShowTooltip(TRUE);

	//CRect rect;
	//GetClientRect(&rect);
	int margin = 10;
	m_chart.SetWindowPos( 0, margin/2, 0,
		rect.Width()-margin,
		rect.Height() , SWP_NOMOVE);

	m_chart.RemoveAll();

	//CMainFrame* MainFrame=(CMainFrame*)this->GetParent()->GetParent(); 
	//Histogram* pHist = &(MainFrame->hist);

	CString tag;
	int val;
	COLORREF barColor = RGB(0,204,0);
	COLORREF minColor = RGB(255,0,0);
	COLORREF maxColor = RGB(0,0,255);

	for ( int i=0;i<256;i++)
	{
		val = (int)pHist->getHistValue( i );
		tag.Format( " %d",i );
		if ( i == pHist->min_index )
		{
			m_chart.AddBar( val, tag ,minColor );
			continue;
		}

		if ( i == pHist->max_index )
		{
			m_chart.AddBar( val, tag ,maxColor );
			continue;
		}
		
		m_chart.AddBar( val, tag ,barColor );
	}
	m_chart.ShowGrid(TRUE, TRUE);
	m_chart.SetGridLines(30,30,FALSE,70);

	m_chart.ShowBarText(1, FALSE, TRUE);      // Show/Hide values(top)
	m_chart.ShowLabel(FALSE, TRUE);          // Show/Hide labels(bottom)

	m_chart.SetAutoScale(TRUE);         // Set chart to be auto scaled
	m_chart.Refresh();     


	return true;
}

// ��ʾָ����ͼ��
bool CPicView::display( CvvImage* pImage )
{
	
	CRect rect;
	GetClientRect( &rect );
	CClientDC dc(this );
	HDC hdc = dc.GetSafeHdc();
	pImage->DrawToHDC( hdc, &rect );
	return true;
}

void CPicView::OnInitialUpdate()
{
	CView::OnInitialUpdate();
	// TODO: �ڴ����ר�ô����/����û���
}

void CPicView::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: Add your message handler code here
	// Do not call CView::OnPaint() for painting messages

	if ( pImage != NULL ) display( pImage );
}
