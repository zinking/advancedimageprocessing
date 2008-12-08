// MainFrm.h : CMainFrame 类的接口
//


#pragma once
#include "highgui.h"
#include "Histogram.h"
class CvvImage;

class CMainFrame : public CFrameWnd
{
	
protected: // 仅从序列化创建
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)
// 属性
public:
	CSplitterWnd m_splitter;
	CSplitterWnd m_picSplitter;

// 操作
public:

// 重写
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// 实现
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // 控件条嵌入成员
	CStatusBar  m_wndStatusBar;
	CToolBar    m_wndToolBar;


// 生成的消息映射函数
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	DECLARE_MESSAGE_MAP()
	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
public:
	afx_msg void OnFileOpen();
	afx_msg void OnConvolutionGaussian();
	afx_msg void OnConvolutionSobel();
	afx_msg void OnMorphologyDialation();
	afx_msg void OnMorphologyErosion();
public:
	// 更新显示灰度图
	int IUpdateBinaryImage(void);
	bool LoadGrayImage( CString strPicPath );
	bool LoadResultImage( );
	int CreateBinaryImage(int threshHold);
	inline void RenderToWindow( IplImage* dst );
	inline void ReleaseAllImages();
public:
	Histogram hist;
	CvvImage loadImage;
	CvvImage binaryImage;
	// original cvimage
	CvvImage* srcImage;
	// filtered Image storage
	CvvImage filteredImage;
	CvvImage maskImage;
	// smooth parameter
	double gaussianDelta;
	CString maskfile_path;
public:
	void OnMorphologyOpen(void);
	void OnMorphologyClose(void);
	void OnMorphologyDistance(void);
	void OnMorphologySkeleton(void);
	void OnMorphologySkeletonRestore(void);
	void OnMorphologyGradient(void);
	void OnMorphologyEdgeDetection(void);
	void OnMorphologyConditionDialation(void);
	void OnMorphologyGrayScaleReconstruction(void);
	void OnMorphologyLoadMaskFile(void);
	void OnMorphologyCBR(void);
	void OnMorphologyOBR(void);
	afx_msg void OnApplresult();
};


