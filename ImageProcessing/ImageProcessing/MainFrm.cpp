// MainFrm.cpp : CMainFrame 类的实现
//

#include "stdafx.h"
#include "ImageProcessing.h"

#include "MainFrm.h"
#include "PanelView.h"
#include "DIPView.h"
#include "PicView.h"
#include "DIPDoc.h"
#include "DIPClass.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_WM_CREATE()
	ON_COMMAND(ID_FILE_OPEN, &CMainFrame::OnFileOpen)
	ON_COMMAND(ID_CONVOLUTION_GAUSSIAN, &CMainFrame::OnConvolutionGaussian)
	ON_COMMAND(ID_CONVOLUTION_SOBEL, &CMainFrame::OnConvolutionSobel)
	ON_COMMAND(ID_MORPHOLOGY_DIALATION, &CMainFrame::OnMorphologyDialation)
	ON_COMMAND(ID_MORPHOLOGY_EROSION, &CMainFrame::OnMorphologyErosion)
	ON_COMMAND(IDM_APPLRESULT, &CMainFrame::OnApplresult)
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // 状态行指示器
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};


// CMainFrame 构造/析构

CMainFrame::CMainFrame()
: srcImage(NULL)
, gaussianDelta( 2.5 )
{
	// TODO: 在此添加成员初始化代码
	this->maskfile_path = "";

}

CMainFrame::~CMainFrame()
{
}


int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("未能创建工具栏\n");
		return -1;      // 未能创建
	}

	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("未能创建状态栏\n");
		return -1;      // 未能创建
	}

	// TODO: 如果不需要工具栏可停靠，则删除这三行
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return TRUE;
}


// CMainFrame 诊断

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}

#endif //_DEBUG


// CMainFrame 消息处理程序




BOOL CMainFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext)
{
	// TODO: 在此添加专用代码和/或调用基类
	CRect rect;
	GetClientRect( &rect );

	float coef = 0.3;
	int height = rect.Height();
	int leftwidth = coef*rect.Width();
	int rightwidth = (1-coef)*rect.Width();


	if ( m_splitter.CreateStatic(this,1,2) == NULL )
		return false;
	m_splitter.CreateView( 0, 0,RUNTIME_CLASS(CPanelView), CSize(leftwidth,rect.Height()),pContext );
	//m_splitter.CreateView( 0, 1,RUNTIME_CLASS(CDIPView), CSize(rightwidth,rect.Height()),pContext );

	if ( m_picSplitter.CreateStatic(&m_splitter,2,2,WS_VISIBLE|WS_CHILD,m_splitter.IdFromRowCol(0,1) ) == NULL )
		return false;
	CSize size( rightwidth/2,height/2);
	m_picSplitter.CreateView(0,0,RUNTIME_CLASS(CPicView),size,pContext);
	m_picSplitter.CreateView(0,1,RUNTIME_CLASS(CPicView),size,pContext);
	m_picSplitter.CreateView(1,0,RUNTIME_CLASS(CPicView),size,pContext);
	m_picSplitter.CreateView(1,1,RUNTIME_CLASS(CPicView),size,pContext);

	return true;
	//return CFrameWnd::OnCreateClient(lpcs, pContext);
}
void CMainFrame::ReleaseAllImages(){
	IplImage* pic = NULL;
	//clear image in mainframe 
	 pic = loadImage.GetImage();
	if ( pic != NULL ) cvReleaseImage( &pic );
	pic = NULL;
	pic = filteredImage.GetImage();
	if ( pic != NULL ) cvReleaseImage( &pic );
	pic = NULL;
	pic = binaryImage.GetImage();
	if ( pic != NULL ) cvReleaseImage( &pic );
	pic = NULL;

}

void CMainFrame::OnFileOpen()
{
	// TODO: 在此添加命令处理程序代码
	CFileDialog dlg(TRUE,NULL,NULL,OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,
		"图片文件(*.jpg;*.jpeg;*.gif;*.bmp)|*.jpg;*.jpeg;*.gif;*.bmp;*.png|位图文件(*.BMP)|*.BMP||");
	//ReleaseAllImages();

	CString strPicPath;

	if (IDOK==dlg.DoModal())
	{
		//显示图像部分
		strPicPath.Format(_T("%s"),dlg.GetPathName());

		CPicView* picView	= (CPicView*) m_picSplitter.GetPane(0,0);
		CPicView* histView	= (CPicView*) m_picSplitter.GetPane(1,0);
		//CDIPDoc*	pDoc	= (CDIPDoc* )picView->GetDocument();


		//显示到窗口
		//pDoc->LoadGrayImage( strPicPath );
		LoadGrayImage( strPicPath );
		picView->pImage = & loadImage;
		srcImage = & loadImage;
		picView->display( & loadImage );

		////////////////////////////我是华丽的分割线//////////////////////////////////////////////

		histView->IUpdateBar();
		IUpdateBinaryImage();

		////////////////////////////我是华丽的分割线//////////////////////////////////////////////

		CPanelView* pan = (CPanelView* )m_splitter.GetPane(0,0);
		pan->mSliderBar.EnableWindow( true);
		pan->m_cbAlgorithm.EnableWindow(true);
		pan->histogram = &hist;

	}
}

void CMainFrame::OnApplresult()
{
	LoadResultImage(  );
	CPicView* picView	= (CPicView*) m_picSplitter.GetPane(0,0);
	CPicView* histView	= (CPicView*) m_picSplitter.GetPane(1,0);
	picView->pImage = & loadImage;
	srcImage = & loadImage;
	picView->display( & loadImage );

	////////////////////////////我是华丽的分割线//////////////////////////////////////////////

	histView->IUpdateBar();
	IUpdateBinaryImage();

	////////////////////////////我是华丽的分割线//////////////////////////////////////////////

	CPanelView* pan = (CPanelView* )m_splitter.GetPane(0,0);
	pan->mSliderBar.EnableWindow( true);
	pan->m_cbAlgorithm.EnableWindow(true);
	pan->histogram = &hist;
	
}

bool  CMainFrame::LoadResultImage(  )
{
	CPicView* picView	= (CPicView*) m_picSplitter.GetPane(1,1);
	loadImage = *picView->pImage;
	////将RGB图像灰阶化
	IplImage* src = picView->pImage->GetImage();
	IplImage* dst = cvCreateImage( cvGetSize( src ), src->depth, 1 );
	cvCvtColor( src, dst, CV_RGB2GRAY );
	loadImage.CopyOf( dst , 1);//如果设置为0(单通道)，出现奇怪的错误

	//初始化HISTOGRAM数据
	hist.IUpdate( dst );
	cvReleaseImage(&dst );
	CPicView* histView	= (CPicView*) m_picSplitter.GetPane(1,0);
	histView->pHist = &hist;

	return true;

}

bool  CMainFrame::LoadGrayImage( CString strPicPath )
{
	loadImage.Load( strPicPath,1) ;

	////将RGB图像灰阶化
	IplImage* src = loadImage.GetImage();
	IplImage* dst = cvCreateImage( cvGetSize( src ), src->depth, 1 );
	cvCvtColor( src, dst, CV_RGB2GRAY );
	loadImage.CopyOf( dst , 1);//如果设置为0(单通道)，出现奇怪的错误


	//初始化HISTOGRAM数据
	hist.IUpdate( dst );
	cvReleaseImage(&dst );
	CPicView* histView	= (CPicView*) m_picSplitter.GetPane(1,0);
	histView->pHist = &hist;

	return true;

}

int CMainFrame::CreateBinaryImage(int threshHold){
	binaryImage.CopyOf( loadImage.GetImage() , 0 );

	IplImage* src = binaryImage.GetImage();
	IplImage* dst = cvCreateImage( cvGetSize( src ), src->depth, 1 );
	cvThreshold(src,dst,(double)threshHold,255,CV_THRESH_BINARY);
	binaryImage.CopyOf( dst, 1);
	cvReleaseImage(&dst );


	return 0;
}


// 更新显示灰度图
int CMainFrame::IUpdateBinaryImage( )
{
	CPanelView* panView = (CPanelView*) m_splitter.GetPane(0,0);

	int threshValue = panView->mSliderBar.GetPos();
	CreateBinaryImage( threshValue );

	CPicView* thPicView = (CPicView*) m_picSplitter.GetPane(0,1);
	thPicView->pImage = &binaryImage;
	thPicView->display(  &binaryImage );

	return 0;
}

void CMainFrame::RenderToWindow( IplImage* dst ){
	CPicView* kerPicView = (CPicView*) m_picSplitter.GetPane(1,1);
	IplImage* src = filteredImage.GetImage();
	if ( src != NULL ) cvReleaseImage( &src);
	//src = NULL;
	//if ( kerPicView->pImage != NULL ) src = kerPicView->pImage->GetImage();
	//if ( src != NULL ) cvReleaseImage( &src);

	filteredImage.Create(dst->width, dst->height , IPL_DEPTH_8U*3, 0);
	filteredImage.CopyOf( dst, 1 );

	kerPicView->pImage = &filteredImage;
	kerPicView->display( &filteredImage );
}

void CMainFrame::OnConvolutionGaussian()
{
	IplImage* src = NULL;
	IplImage* dst = NULL;

	src = srcImage->GetImage();
	dst = cvCloneImage(src);

	cvSmooth( src, dst, CV_GAUSSIAN, 0, 0, gaussianDelta );
	RenderToWindow( dst );
}

void CMainFrame::OnConvolutionSobel()
{
	// TODO: Add your command handler code here
	IplImage* src = NULL;
	IplImage* dst = NULL;
	CvMat* filter = NULL;
	int kerWid = 3, KerHei = 3;
	double kernel[] = {
		-1,0,1,
		-2,0,2,
		-1,0,1
	};
	filter = cvCreateMatHeader(kerWid,KerHei,CV_64FC1 );
	cvSetData( filter , kernel ,KerHei * 8 );
	src = srcImage->GetImage();
	dst = cvCloneImage(src);

	cvFilter2D( src,dst,filter );
	RenderToWindow( dst );

}
//morphology operations
 DIPClass dip;
void CMainFrame::OnMorphologyDialation()
{
	IplImage* src = NULL;
	IplImage* dst = NULL;

	src = srcImage->GetImage();
	dst = cvCloneImage(src);
	Kernel k(7,7);

	dip.Dialate(src,dst);
	RenderToWindow( dst );
}

void CMainFrame::OnMorphologyErosion()
{
	IplImage* src = NULL;
	IplImage* dst = NULL;

	src = srcImage->GetImage();
	dst = cvCloneImage(src);

	dip.Erode(src,dst);
	RenderToWindow( dst );
}

void CMainFrame::OnMorphologyOpen(void)
{
	IplImage* src = NULL;
	IplImage* dst = NULL;

	src = srcImage->GetImage();
	dst = cvCloneImage(src);

	dip.Open(src,dst);
	RenderToWindow( dst );
}

void CMainFrame::OnMorphologyClose(void)
{
	IplImage* src = srcImage->GetImage();
	IplImage* dst = cvCloneImage(src); 

	dip.Close(src,dst);
	RenderToWindow( dst );
}

void CMainFrame::OnMorphologyDistance(void)
{

	//GET BINARY IMAGE FOR EROSION
	CPanelView* panView = (CPanelView*) m_splitter.GetPane(0,0);
	CDIPDoc* pDoc = (CDIPDoc* )panView->GetDocument();
	IplImage* src = binaryImage.GetImage();
	IplImage* dst = cvCloneImage(src);

	dip.Distance(src,dst);
	RenderToWindow( dst );
}

void CMainFrame::OnMorphologySkeleton(void)
{
	//GET BINARY IMAGE FOR EROSION
	CPanelView* panView = (CPanelView*) m_splitter.GetPane(0,0);
	//CDIPDoc* pDoc = (CDIPDoc* )panView->GetDocument();

	IplImage* src = binaryImage.GetImage();
	IplImage* dst = cvCloneImage(src);

	dip.Skeleton(src,dst);
	RenderToWindow( dst );
}

void CMainFrame::OnMorphologySkeletonRestore(void)
{
	CPicView* kerPicView = (CPicView*) m_picSplitter.GetPane(1,1);
	//必须在SKELETON之后做
	IplImage* skeleton = kerPicView->pImage->GetImage();
	IplImage* dst = cvCloneImage(skeleton);

	dip.SkeletonRestore(skeleton,dst);
	RenderToWindow( dst );
}

void CMainFrame::OnMorphologyGradient(void)
{
	IplImage* src = srcImage->GetImage();
	IplImage* dst = cvCloneImage(src);

	CPanelView* panView = (CPanelView*) m_splitter.GetPane(0,0);
	GradientType type = (GradientType)panView->m_cbEdgeType.GetCurSel();

	dip.Gradient(src,dst,type);
	RenderToWindow( dst );
}

void CMainFrame::OnMorphologyEdgeDetection(void)
{
	//GET BINARY IMAGE FOR EROSION
	CPanelView* panView = (CPanelView*) m_splitter.GetPane(0,0);
	CDIPDoc* pDoc = (CDIPDoc* )panView->GetDocument();

	IplImage* src = binaryImage.GetImage();
	IplImage* dst = cvCloneImage(src);

	GradientType type = (GradientType)panView->m_cbEdgeType.GetCurSel();
	dip.EdgeDetection( src,dst,type );
	RenderToWindow( dst );
}

void CMainFrame::OnMorphologyConditionDialation(void){

	//GET BINARY IMAGE FOR EROSION
	CPanelView* panView = (CPanelView*) m_splitter.GetPane(0,0);
	//CDIPDoc* pDoc = (CDIPDoc* )panView->GetDocument();
	IplImage* binarizedNoiseSrc= binaryImage.GetImage();
	IplImage* marker = cvCloneImage(  srcImage->GetImage() );
	IplImage* mask;

	if ( maskfile_path != ""   ){
		 mask = maskImage.GetImage();
	}
	else{
	 mask = cvCloneImage( binarizedNoiseSrc );
	dip.Open( binarizedNoiseSrc,mask );//做好MASK
	}

	dip.ConditionalDialation( marker,mask );
	maskfile_path = "";

	RenderToWindow( marker );
}

void CMainFrame::OnMorphologyGrayScaleReconstruction(void){

	IplImage* prepare = cvCloneImage( srcImage->GetImage() );
	IplImage* marker = cvCloneImage(  srcImage->GetImage() );
	IplImage* mask ;


	if ( maskfile_path != ""   ){
		mask = maskImage.GetImage();
	}
	else{
		mask = loadImage.GetImage();
		Kernel k(30,1);
		dip.Open( prepare,marker,k );//做好MARKER
	}
	


	//Kernel dialation( 4 , 4 );
	dip.GrayScaleRestoration( marker,mask );
	cvReleaseImage( & prepare );
	maskfile_path = "";



	RenderToWindow( marker );
}

void CMainFrame::OnMorphologyLoadMaskFile(void){
	CFileDialog dlg(TRUE,NULL,NULL,OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,
		"图片文件(*.jpg;*.jpeg;*.gif;*.bmp)|*.jpg;*.jpeg;*.gif;*.bmp;*.png|位图文件(*.BMP)|*.BMP||");

	if (IDOK==dlg.DoModal()){
		maskfile_path.Format(_T("%s"),dlg.GetPathName());
		maskImage.Load( maskfile_path);
		cvNamedWindow( "MASKIMGE", 1 );//创建窗口
		cvShowImage( "MASKIMGE", maskImage.GetImage() );
	}
}


//CvvImage maskimg;
//CString path = "C:\\MASK.JPG";
//maskimg.Load( path,1);
//IplImage* mask = maskimg.GetImage();
//IplImage* marker = cvCloneImage(  srcImage->GetImage() );
//dip.GrayScaleRestoration( marker,mask );
