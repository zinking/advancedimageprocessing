// DIPDoc.cpp : CDIPDoc ���ʵ��
//

#include "stdafx.h"
#include "ImageProcessing.h"

#include "DIPDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CDIPDoc

IMPLEMENT_DYNCREATE(CDIPDoc, CDocument)

BEGIN_MESSAGE_MAP(CDIPDoc, CDocument)
END_MESSAGE_MAP()


// CDIPDoc ����/����

CDIPDoc::CDIPDoc()
{
	// TODO: �ڴ����һ���Թ������

}

CDIPDoc::~CDIPDoc()
{
}

BOOL CDIPDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: �ڴ�������³�ʼ������
	// (SDI �ĵ������ø��ĵ�)

	return TRUE;
}




// CDIPDoc ���л�

void CDIPDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: �ڴ���Ӵ洢����
	}
	else
	{
		// TODO: �ڴ���Ӽ��ش���
	}
}


// CDIPDoc ���

#ifdef _DEBUG
void CDIPDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CDIPDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


//// װ�ز���ԭRGBͼ��ת��Ϊ�Ҷ�ͼ
//
//bool CDIPDoc::LoadGrayImage(CString strPicPath)
//{
//	//TODO:������
//	cvImage.Load( strPicPath,1) ;
//
//	////��RGBͼ��ҽ׻�
//	IplImage* src = cvImage.GetImage();
//	IplImage* dst = cvCreateImage( cvGetSize( src ), src->depth, 1 );
//	cvCvtColor( src, dst, CV_RGB2GRAY );
//	cvImage.CopyOf( dst , 1);//�������Ϊ0(��ͨ��)��������ֵĴ���
//	
//
//	//��ʼ��HISTOGRAM����
//	hist.IUpdate( dst );
//	cvReleaseImage(&dst );
//
//	return true;
//}

//// ������ֵ�����ͼ��
//int CDIPDoc::CreateBinaryImage(int threshHold)
//{
//
//	thImage.CopyOf( cvImage.GetImage() , 0 );
//
//	IplImage* src = thImage.GetImage();
//	IplImage* dst = cvCreateImage( cvGetSize( src ), src->depth, 1 );
//	cvThreshold(src,dst,(double)threshHold,255,CV_THRESH_BINARY);
//	thImage.CopyOf( dst, 1);
//
//	cvReleaseImage(&dst );
//
//	return 0;
//
//}

