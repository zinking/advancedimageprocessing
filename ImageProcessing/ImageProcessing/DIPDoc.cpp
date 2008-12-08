// DIPDoc.cpp : CDIPDoc 类的实现
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


// CDIPDoc 构造/析构

CDIPDoc::CDIPDoc()
{
	// TODO: 在此添加一次性构造代码

}

CDIPDoc::~CDIPDoc()
{
}

BOOL CDIPDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 在此添加重新初始化代码
	// (SDI 文档将重用该文档)

	return TRUE;
}




// CDIPDoc 序列化

void CDIPDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: 在此添加存储代码
	}
	else
	{
		// TODO: 在此添加加载代码
	}
}


// CDIPDoc 诊断

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


//// 装载并将原RGB图像转化为灰度图
//
//bool CDIPDoc::LoadGrayImage(CString strPicPath)
//{
//	//TODO:出错处理
//	cvImage.Load( strPicPath,1) ;
//
//	////将RGB图像灰阶化
//	IplImage* src = cvImage.GetImage();
//	IplImage* dst = cvCreateImage( cvGetSize( src ), src->depth, 1 );
//	cvCvtColor( src, dst, CV_RGB2GRAY );
//	cvImage.CopyOf( dst , 1);//如果设置为0(单通道)，出现奇怪的错误
//	
//
//	//初始化HISTOGRAM数据
//	hist.IUpdate( dst );
//	cvReleaseImage(&dst );
//
//	return true;
//}

//// 创建二值化后的图形
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

