// MainFrm.h : CMainFrame ��Ľӿ�
//


#pragma once
#include "highgui.h"
#include "Histogram.h"
class CvvImage;

class CMainFrame : public CFrameWnd
{
	
protected: // �������л�����
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)
// ����
public:
	CSplitterWnd m_splitter;
	CSplitterWnd m_picSplitter;

// ����
public:

// ��д
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// ʵ��
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // �ؼ���Ƕ���Ա
	CStatusBar  m_wndStatusBar;
	CToolBar    m_wndToolBar;


// ���ɵ���Ϣӳ�亯��
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
	// ������ʾ�Ҷ�ͼ
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


